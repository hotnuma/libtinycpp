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

    _exitCode = -1;

    // Create a pipe for the child process's STDIN.
    //if (_flags & CPF_PIPEIN)
    //{
    //    if (!::CreatePipe(&_inHandles[CPH_OUT], &_inHandles[CPH_IN], &saAttr, 0)
    //        || !::SetHandleInformation(_inHandles[CPH_IN], HANDLE_FLAG_INHERIT, 0))
    //        return false;
    //}

    // Create a pipe for the child process's STDOUT.
    if (outpipe)
    {
        outBuff.resize(CHUNCK * 2);

        if (pipe(_outPipe) == -1)
        {
            perror("pipe failed\n");

            return false;
        }
    }

    // Create a pipe for the child process's STDOUT.
    //if ((_flags & CPF_PIPEERR) && !(_flags & CPF_MERGEERR))
    //{
    //    if (!::CreatePipe(&_errHandles[CPH_OUT], &_errHandles[CPH_IN], &saAttr, 0)
    //        || !::SetHandleInformation(_errHandles[CPH_OUT], HANDLE_FLAG_INHERIT, 0))
    //        return false;
    //}

    wordexp_t we;
    wordexp(cmd, &we, 0);

    int pid;
    if ((pid = fork()) == -1)
    {
        perror("fork failed\n");

        wordfree(&we);
        return 2;
    }

    if (pid == 0)
    {
        //if (_flags & CPF_PIPEIN)
        //    siw.hStdInput = _inHandles[CPH_OUT];

        if (outpipe)
        {
            dup2(_outPipe[CPH_IN], STDOUT_FILENO);
            close(_outPipe[CPH_OUT]);
        }

        //if (_flags & CPF_MERGEERR)
        //    siw.hStdError = _outHandles[CPH_IN];
        //else if (_flags & CPF_PIPEERR)
        //    siw.hStdError = _errHandles[CPH_IN];

        char **w = we.we_wordv;

        if (execvp(w[0], (char**) w) == -1)
            perror("exec failed...");

        exit(EXIT_FAILURE);
    }
    else
    {
        fd_set readfds;
        struct timeval timeout;

        if (outpipe)
            close(_outPipe[CPH_IN]);

        while (waitpid(pid, nullptr, WNOHANG) != pid)
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
    }

    if (outpipe)
        close(_outPipe[CPH_OUT]);

    wordfree(&we);

    return true;
}


