#include "lib/CProcess.h"

#include "print.h"

int main()
{
    CString cmd = "/home/hotnuma/testout";

    CProcess process;
    if (!process.start(cmd, CPF_PIPEOUT))
    {
        print("start failed");

        return -1;
    }

    int status = process.exitStatus();

    if (status != 0)
    {
        print("program returned : %d", status);

        return -1;
    }

    CString result = process.outBuff;

    print(result);

    return 0;
}


