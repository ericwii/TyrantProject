#pragma once

#define MIN(a,b) (a) < (b) ? a : b
#define MAX(a,b) (a) > (b) ? a : b

#define ABS(x) (x) < 0 ? -(x) : (x)

#define SAFE_DELETE(x) delete x; x = nullptr;

#define LERP(start, end, lerpValue) (start) + (((end) - (start)) * lerpValue)

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

#define PI 3.14159265359f
#define PI_2 1.57079632679f
#define PI_4 0.78539816339f

#define SWAP_VALUE(a,b)\
auto x = a;\
a = b;\
b = x;