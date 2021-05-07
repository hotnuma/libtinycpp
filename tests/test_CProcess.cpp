#include "CProcess.h"
#include "libtest.h"
#include "CString.h"
#include "libapp.h"

#include "print.h"

extern char g_testroot[];

void test_CProcess()
{
    uchdir(g_testroot);

    CProcess process;
    process.start("cmd /c dir", PF_PIPEOUT);
    ASSERT(process.outBuff.contains("strconv.txt"));

}


