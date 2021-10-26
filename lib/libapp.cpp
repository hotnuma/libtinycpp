#include "libapp.h"

#include "libpath.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <wordexp.h>

#include "print.h"

CString getApplicationPath()
{
    int dest_len = 256;

    CString result(dest_len);

    int ret = readlink("/proc/self/exe", result.data(), dest_len);

    if (ret == -1)
    {
        result.clear();
        return result;
    }

    result.terminate(ret);

    return result;
}

CString getApplicationDir()
{
    CString path = getApplicationPath();

    char *p = path.data();
    char *sep = nullptr;

    while (1)
    {
        if (*p == '/')
        {
            sep = p;
        }
        else if (*p == '\0')
        {
            if (sep)
                path.terminate(sep - path.data());
            else
                path.clear();

            return path;
        }

        ++p;
    }
}

CString getHomeDirectory()
{
    CString result(100);

    const char *homedir = getenv("HOME");

    if (homedir != nullptr)
        result = homedir;

    return result;
}

CString getUserName()
{
    CString result;

    uid_t uid = geteuid();

    struct passwd *pw = getpwuid(uid);

    if (pw)
    {
        result = pw->pw_name;
    }

    return result;
}

int pexec(const char *cmd)
{
    pid_t childpid = fork();

    if (childpid < 0)
    {
        perror("failed to fork.");
        return -1;
    }

    if (childpid == 0)
    {
        umask(0);
        setsid();

        if ((chdir("/")) < 0)
            exit(-1);

        // close out the standard file descriptors.
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        if (!cmd || !*cmd)
            exit(-1);

        wordexp_t p;
        wordexp(cmd, &p, 0);

        char **w = p.we_wordv;

        if (execve(w[0], (char**) w, __environ) == -1)
            perror("could not execve...");

        wordfree(&p);

        exit(0);
    }

    return 1;
}

CString argsToCString(int argc, char **argv)
{
    CString result(64);
    result.terminate(1);
    int size = 0;

    for (int i = 0; i < argc; ++i)
    {
        char *arg = argv[i];
        int len = strlen(arg);

        if (len < 1)
            continue;

        result.resize(size + len + 2);
        char *p = result.data() + size;
        strcpy(p, arg);
        size += len + 1;
    }

    if (size < 1)
        return result;

    result.resize(size + 1);
    result.terminate(size);

    return result;
}


#if 0

bool isFirstInstance(const wchar_t *guid)
{
    return true;
}

CString getWindowsDirectory()
{
    CString result(100);

    return result;
}

CStringList getLogicalDrives()
{
    CStringList result;

    return result;
}

#endif


