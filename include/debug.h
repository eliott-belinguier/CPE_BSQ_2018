#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG

#include <stdio.h>

#define LOG(format, ...) printf(format, __VA_ARGS__)

#else

#define LOG(format, ...) ((void) 0)

#endif

#endif
