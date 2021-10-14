#ifndef CPROCESS_H
#define CPROCESS_H

#include "CString.h"

#define PF_NONE     0x00
#define PF_PIPEIN   0x01
#define PF_PIPEOUT  0x02
#define PF_PIPEERR  0x04
#define PF_MERGEERR 0x08

#define PH_READ     0
#define PH_WRITE    1

void closeHandlePtr(void **ptr);

class CProcess
{
public:

    CProcess();
    ~CProcess();

    void setInput(const char *instr);
    bool start(const char *command, int flags = PF_NONE);
    int exitStatus() {return _exitCode;}

    CString inBuff;
    CString outBuff;
    CString errBuff;

private:

    void _writeToPipe();
    void _waitForFinished(void *handle);
    bool _readAll();

    void *_inHandles[2] = {0, 0};
    void *_outHandles[2] = {0, 0};
    void *_errHandles[2] = {0, 0};

    int _flags = PF_NONE;
    const char *_instr = nullptr;
    long unsigned int _exitCode = 0;

};

#endif // CPROCESS_H


