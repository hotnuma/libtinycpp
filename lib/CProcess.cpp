#include "CProcess.h"
#include <wtypes.h>
#include "libconv.h"

//#include "print.h"

void closeHandlePtr(void **ptr)
{
    if (!ptr || !*ptr)
        return;

    ::CloseHandle(*ptr);
    *ptr = nullptr;
}

static int _readPipe(void *handle, CString &outBuff)
{
    if (!handle)
        return -1;

    DWORD avail;
    if (!::PeekNamedPipe(handle, 0, 0, 0, &avail, 0))
    {
        //print("peek broken");
        return 0;
    }

    if (!avail)
        return 1;

    //print("peek = %i", avail);

    int length = outBuff.size();
    outBuff.resize(length + avail + 1);

    char *buff = outBuff.data() + length;
    DWORD numRead;

    if (!::ReadFile(handle, buff, avail, &numRead, 0))
    {
        //print("read broken");
        return 0;
    }

    int num = (numRead < avail) ? numRead : avail;
    outBuff.terminate(length + num);

    //print("read = %i", numRead);

    return 1;
}

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

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = true;
    saAttr.lpSecurityDescriptor = nullptr;

    // Create a pipe for the child process's STDIN.
    if (_flags & PF_PIPEIN)
    {
        if (!::CreatePipe(&_inHandles[PH_READ], &_inHandles[PH_WRITE], &saAttr, 0)
            || !::SetHandleInformation(_inHandles[PH_WRITE], HANDLE_FLAG_INHERIT, 0))
            return false;
    }

    // Create a pipe for the child process's STDOUT.
    if (_flags & PF_PIPEOUT)
    {
        if (!::CreatePipe(&_outHandles[PH_READ], &_outHandles[PH_WRITE], &saAttr, 0)
            || !::SetHandleInformation(_outHandles[PH_READ], HANDLE_FLAG_INHERIT, 0))
            return false;
    }

    // Create a pipe for the child process's STDOUT.
    if ((_flags & PF_PIPEERR) && !(_flags & PF_MERGEERR))
    {
        if (!::CreatePipe(&_errHandles[PH_READ], &_errHandles[PH_WRITE], &saAttr, 0)
            || !::SetHandleInformation(_errHandles[PH_READ], HANDLE_FLAG_INHERIT, 0))
            return false;
    }

    PROCESS_INFORMATION pi;
    STARTUPINFOW siw;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siw, sizeof(STARTUPINFOW));

    siw.cb = sizeof(STARTUPINFOW);
    if (_flags & PF_PIPEIN)
        siw.hStdInput = _inHandles[PH_READ];

    if (_flags & PF_PIPEOUT)
        siw.hStdOutput = _outHandles[PH_WRITE];

    if (_flags & PF_MERGEERR)
        siw.hStdError = _outHandles[PH_WRITE];
    else if (_flags & PF_PIPEERR)
        siw.hStdError = _errHandles[PH_WRITE];

    siw.dwFlags |= STARTF_USESTDHANDLES;

    wchar_t *wbuff = utf8ToWchar(command);

    bool result = ::CreateProcessW(
                    0,              // application name
                    wbuff,          // command line
                    0,              // process security attributes
                    0,              // primary thread security attributes
                    true,           // handles are inherited
                    0,              // creation flags
                    0,              // use parent's environment
                    0,              // use parent's current directory
                    &siw,   // STARTUPINFO pointer
                    &pi);   // receives PROCESS_INFORMATION

    free(wbuff);

    closeHandlePtr(&_inHandles[PH_READ]);
    closeHandlePtr(&_outHandles[PH_WRITE]);
    closeHandlePtr(&_errHandles[PH_WRITE]);

    // If an error occurs, exit the application.
    if (!result)
    {
        closeHandlePtr(&_inHandles[PH_WRITE]);
        closeHandlePtr(&_outHandles[PH_READ]);
        closeHandlePtr(&_errHandles[PH_READ]);

        ::GetExitCodeProcess(pi.hProcess, &_exitCode);

        return false;
    }

    if (_inHandles[PH_WRITE])
        _writeToPipe();

    // Read from pipe that is the standard output for child process.
    _waitForFinished(pi.hProcess);

    closeHandlePtr(&_inHandles[PH_WRITE]);
    closeHandlePtr(&_outHandles[PH_READ]);
    closeHandlePtr(&_errHandles[PH_READ]);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
    //return (_exitCode == 0);
}

void CProcess::_writeToPipe()
{
    DWORD dwWritten;

    if (_instr)
    {
        //print("write");

        int len = strlen(_instr);
        ::WriteFile(_inHandles[PH_WRITE], _instr, len, &dwWritten, NULL);
    }

    closeHandlePtr(&_inHandles[PH_WRITE]);

    return;
}

void CProcess::_waitForFinished(void *handle)
{
    while (1)
    {
        Sleep(50);

        if (!_readAll())
        {
            ::WaitForSingleObject(handle, INFINITE);

            //print("end wait");

            _readAll();

            break;
        }
    }
}

bool CProcess::_readAll()
{
    int retout = 0;
    int reterr = 0;

    if (_outHandles[PH_READ])
        retout = _readPipe(_outHandles[PH_READ], outBuff);

    if (_errHandles[PH_READ])
        reterr = _readPipe(_errHandles[PH_READ], errBuff);

    if (retout == -1 || reterr == -1)
    {
        // error.
        return false;
    }

    if (retout == 0 && reterr == 0)
    {
        // finished.
        return false;
    }

    return true; // continue
}


