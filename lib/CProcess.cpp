#include "CProcess.h"

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

void CProcess::setInput(const char *instr)
{
    _instr = instr;
}

bool CProcess::start(const char *command, int flags)
{
    _flags = flags;
    _exitCode = -1;

//    FILE *fp = popen("ls -la", "r");

//    if (!fp)
//    {
//        print("can't find program");

//        exit(1);
//    }

//    int size = 1023;
//    char readbuf[size + 1];

//    while (fgets(readbuf, size, fp))
//    {
//        print("line = %s", readbuf);
//    }

//    pclose(fp);

    return true;
}

void CProcess::_writeToPipe()
{
}

void CProcess::_waitForFinished(void *handle)
{
}

bool CProcess::_readAll()
{
    return true;
}


