#ifndef PRINT_H
#define PRINT_H

#if defined(DEBUG)
#include "print.h"
#define dprint print
#else
#define dprint(fmt, ...) do {} while (0)
#endif

void print(const char *fmt, ...);

#endif // PRINT_H


