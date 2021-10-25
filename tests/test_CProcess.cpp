#include "CProcess.h"
#include "libtest.h"
#include "CString.h"
#include "libapp.h"

#include "print.h"

//extern char _testroot[];

void test_CProcess()
{
    //uchdir(_testroot);

    CProcess process;
    process.start("cmd /c dir", CPF_PIPEOUT);
    ASSERT(process.outBuff.contains("strconv.txt"));

}


