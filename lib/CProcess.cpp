#include "CProcess.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <wordexp.h>

#include <print.h>

#define CHUNCK 1024

int _readPipe(int fd, CString &buffer)
{
    if (fd < 0)
        return -1;

    char *ptr = getPtr(buffer, CHUNCK);
    int nb_read = read(fd, ptr, CHUNCK - 1);

    if (nb_read < 1)
    {
        print("nothing to read");

        return 0;
    }

    print("%d bytes read", nb_read);
    buffer.terminate(buffer.size() + nb_read);

    return nb_read;
}

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

bool CProcess::start(const char *cmd, int flags)
{
    if (!cmd || !*cmd)
        return false;

    bool outpipe = flags & CPF_PIPEOUT;

    _exitStatus = -1;

    // Create a pipe for the child process's STDOUT.
    if (outpipe)
    {
        if (pipe(_outPipe) == -1)
        {
            perror("pipe failed\n");

            return false;
        }
    }

    wordexp_t we;
    wordexp(cmd, &we, 0);

    int pid = fork();

    if (pid < 0)
    {
        perror("fork failed\n");

        wordfree(&we);
        return 2;
    }
    else if (pid == 0)
    {
        if (outpipe)
        {
            dup2(_outPipe[CPH_IN], STDOUT_FILENO);
            close(_outPipe[CPH_OUT]);
        }

        char **w = we.we_wordv;

        if (execvp(w[0], (char**) w) == -1)
            perror("exec failed...");

        exit(EXIT_FAILURE);
    }

    fd_set readfds;
    struct timeval timeout;

    if (outpipe)
    {
        close(_outPipe[CPH_IN]);

        outBuff.resize(CHUNCK * 2);
    }

    int status = -1;

    while (waitpid(pid, &status, WNOHANG) != pid)
    {
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        FD_ZERO(&readfds);

        if (outpipe)
            FD_SET(_outPipe[CPH_OUT], &readfds);

        select(FD_SETSIZE, &readfds, nullptr, nullptr, &timeout);

        if (outpipe && FD_ISSET(_outPipe[CPH_OUT], &readfds))
        {
            _readPipe(_outPipe[CPH_OUT], outBuff);
        }
    }

    if (outpipe)
        close(_outPipe[CPH_OUT]);

    wordfree(&we);

    if (WIFEXITED(status))
        _exitStatus = WEXITSTATUS(status);

    //print("status = %d", _exitCode);

    return true;
}


