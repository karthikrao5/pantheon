//
// Created by Karthik Rao on 9/6/20.
//

#include "debugBreak.h"

#ifndef PANTHEON_UTILS_H
#define PANTHEON_UTILS_H
#define ASSERT(x) if (!(x)) debug_break();
#define GLCall(x) GLClearError(); \
    x;                             \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif //PANTHEON_UTILS_H
