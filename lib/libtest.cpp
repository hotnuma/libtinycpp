#include "libtest.h"

#include <stdio.h>
#include "CString.h"

#define TT_LINE1 "============================================================\n"
#define TT_LINE2 "------------------------------------------------------------\n"
#define TT_COLOR_RED "[1;31m"
#define TT_COLOR_GREEN "[1;32m"

const char* g_current_expression = NULL;
const char* g_current_file = NULL;
int         g_current_line = 0;
int         g_current_result = 0;

int         g_passed = 0;
int         g_failed = 0;

void tt_execute(const char *name, void (*test_function)())
{
    if (g_current_result)
        return;

    printf(TT_LINE1);
    printf("         > %s\n", name);
    printf(TT_LINE2);

    g_current_result = 1;

    test_function();

    if (g_current_result == 0)
    {
        g_passed++;
    }
    else
    {
        g_failed++;
    }
}

int tt_assert(const char *expression,
              const char *file, int line, int result)
{
    g_current_expression = expression;
    g_current_file = file;
    g_current_line = line;
    g_current_result = result;

    if (result == 0)
    {
        printf("\x1b%s[passed]\x1b[0m | (%s)\n",
               TT_COLOR_GREEN,
               g_current_expression);
    }
    else
    {
        printf("\x1b%s[failed]\x1b[0m | (%s)\n",
               TT_COLOR_RED,
               g_current_expression);

        printf("         | %s:%d\n",
               g_current_file,
               g_current_line);
    }

    return result;
}

int tt_report(void)
{
    printf(TT_LINE1);

    if (g_failed)
    {
        printf("         | passed:%d, failed:%d, total:%d\n",
               g_passed, g_failed, (g_passed + g_failed));

        return -1;
    }
    else
    {
        printf("         | total:%d\n", g_passed);
        return 0;
    }

    printf(TT_LINE2);
}


