#include "lib/CProcess.h"

#include "print.h"

int main()
{
    CString cmd = "ls -la";

    CProcess process;
    if (!process.start(cmd, CPF_PIPEOUT))
    {
        print("start failed");

        return 1;
    }

    //if (process.exitStatus() != 0)
    //    return 1;

    CString result = process.outBuff;

    print(result);

    return 0;
}


