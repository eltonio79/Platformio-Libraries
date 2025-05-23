#ifndef RAVEN_ARH_H_
#define RAVEN_ARH_H_
 
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "mozzi_pgmspace.h"
 
#define RAVEN_ARH_NUM_CELLS 8192
#define RAVEN_ARH_SAMPLERATE 8192
 
CONSTTABLE_STORAGE(int8_t) RAVEN_ARH_DATA [] = {-1, 0, 3, 6, 7, 7,
5, 0, -6, -8, -7, -4, 0, 3, 4, 4, 1, -3, -8, -10, -10, -7, -5, -3, 0, 3, 5, 5,
5, 4, 3, 0, -2, -4, -3, -1, 1, 2, 3, 4, 4, 5, 4, 2, 1, -1, -2, -3, -4, -3, -2,
0, 0, -1, -2, -5, -6, -6, -3, -1, 1, 1, 1, 1, 0, 0, 0, -1, -2, -3, -4, -4, -3,
-2, -1, 0, 0, 0, 0, 0, 2, 3, 5, 7, 7, 6, 3, 2, 0, -1, -1, -1, -1, 0, 1, 2, 2,
-1, -6, -14, -22, -22, -13, -1, 8, 14, 15, 12, 6, 0, -5, -6, -3, -1, -1, -2, -2,
0, 3, 5, 5, 6, 2, -4, -10, -11, -7, -2, 3, 4, 4, 2, -1, -2, -3, -1, 3, 4, 0, -4,
-5, -4, 0, 3, 5, 5, 3, 0, -3, -5, -3, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, -1, -5,
-6, -6, -3, -1, -1, 0, -1, -3, -4, -4, -2, 0, 1, 2, 1, 0, -1, -2, -3, -4, -2, 0,
3, 4, 6, 6, 3, 0, -3, -5, -4, -1, 4, 7, 9, 8, 5, 1, 0, 2, 4, 4, 1, -8, -22, -33,
-32, -18, 0, 15, 24, 24, 15, 2, -11, -18, -17, -9, -3, 0, 0, 1, 2, 6, 9, 11, 12,
9, 2, -5, -8, -6, -1, 3, 5, 6, 5, 2, -2, -4, -4, -1, 0, -2, -4, -5, -2, 1, 1,
-1, -4, -7, -10, -12, -10, -6, -1, 2, 3, 4, 5, 5, 5, 4, 3, 2, 0, -2, -5, -6, -4,
-1, 3, 6, 8, 6, 2, -2, -4, -5, -4, -2, 1, 3, 4, 3, 1, -3, -5, -6, -5, -3, -1, 3,
5, 5, 3, 2, 0, 1, 3, 6, 7, 3, -8, -23, -36, -35, -17, 3, 18, 27, 25, 15, 4, -7,
-15, -15, -9, -3, -2, -1, 1, 5, 11, 14, 13, 10, 4, -5, -13, -13, -7, 1, 7, 8, 6,
3, 0, -2, -4, -2, 4, 8, 6, 0, -6, -10, -10, -7, -4, -3, -5, -8, -10, -10, -5, 0,
2, 0, -2, -4, -3, 1, 4, 7, 9, 6, 1, -4, -7, -3, 3, 9, 11, 10, 5, -1, -4, -3, 3,
9, 12, 10, 6, 3, 2, 5, 6, 1, -12, -30, -48, -48, -27, -1, 20, 32, 29, 16, 1,
-12, -18, -15, -7, -1, 0, 0, 2, 7, 13, 14, 12, 7, -2, -12, -17, -11, 2, 14, 21,
19, 12, 2, -7, -12, -14, -10, -3, 1, 0, -5, -7, -6, -2, 4, 6, 4, 0, -5, -8, -8,
-3, 1, 2, 0, -1, -1, -1, 2, 4, 6, 5, 1, -4, -8, -8, -5, 0, 4, 4, 2, -2, -4, -2,
4, 10, 10, 6, 1, 0, 5, 9, 8, -4, -24, -42, -39, -19, 6, 28, 40, 34, 18, -1, -21,
-31, -26, -13, -5, -2, 3, 6, 12, 19, 21, 14, 8, -2, -17, -25, -22, -11, 1, 8,
10, 10, 9, 7, 0, -8, -11, -7, -4, -5, -3, 0, 4, 7, 7, 3, 1, -1, -4, -5, -3, 3,
7, 6, 1, -2, -4, -2, 1, 2, 5, 5, -1, -9, -17, -18, -10, 3, 11, 11, 5, -6, -13,
-11, -1, 11, 18, 18, 16, 14, 10, 2, -12, -32, -51, -51, -28, 3, 29, 45, 44, 27,
9, -9, -21, -21, -12, -5, -5, -1, 2, 7, 16, 21, 17, 6, -7, -22, -30, -24, -8, 7,
13, 13, 10, 5, 2, -1, -7, -9, -5, -4, -8, -11, -9, -3, 4, 8, 6, 5, 3, -2, -7,
-9, -4, 5, 10, 10, 8, 4, 2, 2, 3, 6, 8, 4, -7, -18, -23, -18, -6, 10, 20, 16, 5,
-10, -18, -16, -4, 7, 13, 15, 15, 16, 11, -2, -24, -49, -58, -41, -10, 20, 42,
47, 33, 12, -7, -23, -23, -11, -2, -1, 0, 3, 7, 19, 28, 25, 15, -1, -21, -34,
-27, -8, 12, 23, 20, 9, -1, -7, -10, -13, -14, -10, -7, -10, -12, -9, -2, 8, 14,
12, 8, 4, -2, -10, -13, -10, -2, 5, 7, 7, 4, 0, -3, -6, -3, 3, 8, 5, -3, -11,
-13, -5, 7, 16, 18, 12, 0, -10, -10, -4, 4, 11, 13, 12, 11, 7, -4, -28, -52,
-55, -33, -4, 22, 41, 43, 31, 12, -9, -25, -25, -13, -8, -6, -3, 1, 7, 20, 25,
20, 10, -6, -25, -33, -22, -1, 20, 28, 19, 4, -5, -8, -9, -6, -1, 5, 4, -6, -18,
-23, -16, -1, 11, 15, 16, 13, 4, -8, -15, -13, -5, 3, 7, 8, 5, 3, 2, -3, -4, -1,
1, -3, -9, -15, -15, -5, 10, 23, 29, 23, 8, -8, -18, -16, -4, 10, 15, 8, -14,
-42, -57, -43, -8, 27, 45, 39, 17, -2, -11, -13, -10, -4, -1, -4, -6, -5, 1, 17,
33, 31, 16, 1, -19, -33, -31, -19, -3, 15, 24, 19, 9, 1, -3, -5, -4, -5, -6,
-10, -14, -14, -14, -6, 5, 9, 6, 1, -7, -10, -6, -2, 2, 5, 3, 0, 4, 9, 17, 20,
15, 5, -7, -15, -12, -2, 9, 18, 18, 9, 3, 4, 10, 15, 10, -13, -48, -82, -84,
-44, 11, 54, 70, 51, 16, -12, -31, -34, -22, -7, -4, -5, -8, -6, 6, 24, 36, 34,
25, 5, -21, -33, -26, -8, 12, 25, 20, 9, -1, -11, -15, -13, -3, 9, 15, 12, 2,
-5, -6, -6, -9, -13, -13, -12, -9, -5, -2, 2, 6, 2, -4, -4, -3, 3, 10, 11, 8, 4,
0, -1, 3, 8, 12, 11, 6, 6, 9, 10, 2, -18, -46, -64, -49, -12, 24, 47, 50, 27, 0,
-20, -33, -33, -15, 1, 3, 3, 5, 10, 27, 41, 28, 6, -14, -37, -45, -32, -7, 19,
39, 39, 19, -1, -13, -17, -17, -14, -6, 2, 7, 5, -3, -7, 0, 9, 7, 0, -9, -18,
-19, -13, -2, 10, 18, 13, 0, -10, -10, -4, 4, 8, 8, 4, -1, -1, 4, 10, 16, 17,
11, 3, -3, -7, -14, -28, -48, -58, -41, 0, 38, 60, 58, 28, -7, -29, -41, -35,
-13, 4, 9, 11, 12, 12, 18, 24, 15, -1, -13, -22, -22, -7, 14, 29, 33, 20, 0,
-17, -25, -24, -20, -12, -3, 2, 3, 0, -1, -1, 2, 3, 1, -3, -5, -10, -16, -14,
-4, 8, 14, 10, 2, 1, 5, 7, 8, 7, 5, 3, -1, -4, 0, 8, 17, 17, 12, 6, 5, 5, 1,
-14, -39, -66, -78, -54, -6, 38, 62, 56, 26, -4, -23, -30, -23, -5, 7, 13, 12,
7, 5, 9, 16, 16, 11, 4, -6, -12, -8, 4, 14, 18, 10, -10, -23, -26, -22, -12, -3,
4, 7, 8, 4, -4, -2, 1, 2, -2, -4, -11, -18, -16, -11, -2, 11, 16, 8, 3, 1, -4,
-2, 4, 7, 11, 14, 8, 4, 4, 6, 8, 9, 8, 8, 8, 8, 5, -8, -25, -46, -61, -47, -10,
25, 42, 36, 13, -8, -17, -19, -14, -6, -2, 2, 0, 0, 6, 14, 20, 18, 10, 3, -5,
-13, -12, -4, 7, 13, 7, -6, -14, -15, -9, -1, 7, 12, 13, 5, -8, -15, -14, -5, 6,
11, 7, 1, -8, -17, -18, -14, -3, 5, 5, 3, 3, 1, 4, 10, 12, 14, 12, 1, -9, -11,
-6, 5, 12, 18, 20, 17, 11, 2, -11, -28, -47, -64, -59, -25, 17, 46, 53, 35, 6,
-18, -34, -36, -23, -3, 14, 18, 15, 13, 15, 21, 20, 13, 7, -4, -17, -18, -8, 6,
21, 24, 10, -6, -17, -25, -23, -12, 1, 13, 15, 3, -7, -11, -9, -5, -4, -7, -13,
-19, -19, -9, 7, 22, 29, 16, -2, -14, -21, -16, 0, 15, 26, 27, 15, 4, -2, 1, 8,
11, 11, 13, 16, 12, 1, -17, -41, -65, -68, -40, 7, 44, 58, 42, 11, -15, -30,
-32, -23, -9, -1, -1, -3, -3, 7, 23, 29, 23, 13, 1, -12, -21, -21, -10, 5, 18,
19, 9, 1, -2, -4, -2, 2, 5, 7, 2, -9, -16, -13, -2, 9, 9, 0, -13, -27, -28, -16,
4, 19, 18, 2, -13, -16, -12, 1, 15, 20, 16, 9, 0, -2, 4, 8, 12, 14, 19, 25, 25,
8, -24, -62, -89, -78, -28, 30, 72, 80, 49, 3, -33, -50, -46, -23, 1, 13, 12,
11, 11, 15, 26, 23, 3, -14, -28, -33, -15, 10, 26, 31, 18, -6, -23, -26, -15,
-1, 8, 12, 10, 4, -1, -4, -4, 1, 5, 2, -5, -14, -25, -30, -23, -3, 20, 30, 20,
-2, -18, -18, -5, 9, 18, 21, 15, 9, 7, 9, 11, 13, 12, 7, 2, -8, -25, -48, -67,
-60, -26, 13, 42, 56, 45, 24, -1, -25, -40, -39, -25, -11, 4, 20, 35, 44, 42,
24, -8, -31, -39, -36, -15, 15, 36, 43, 31, 4, -17, -23, -22, -16, -7, -1, 4, 4,
-1, -8, -11, -5, 2, 7, 7, 0, -8, -15, -18, -13, -3, 10, 15, 12, 6, 0, 0, 5, 8,
8, 7, 2, -5, -8, -5, 8, 24, 32, 21, -12, -51, -77, -67, -18, 37, 62, 53, 21,
-12, -28, -27, -19, -7, -3, -7, -9, -2, 14, 36, 53, 46, 17, -22, -57, -67, -46,
-5, 34, 53, 46, 20, -8, -23, -24, -15, -6, -4, -5, -3, 1, 4, 6, 10, 13, 11, 2,
-10, -24, -30, -26, -17, -4, 4, 4, 4, 4, 6, 10, 15, 19, 20, 16, 9, 5, 3, 5, 10,
17, 20, 11, -15, -51, -80, -75, -32, 23, 61, 66, 40, 3, -24, -38, -40, -31, -22,
-15, -6, 7, 24, 47, 64, 52, 13, -30, -62, -66, -36, 4, 36, 50, 39, 14, -8, -16,
-6, 6, 9, 1, -12, -20, -17, -6, 7, 16, 19, 16, 8, -3, -15, -26, -29, -25, -19,
-11, -7, -7, -5, 1, 7, 16, 20, 18, 14, 11, 7, 3, 1, 2, 10, 20, 23, 12, -15, -52,
-80, -69, -20, 31, 62, 63, 37, 9, -7, -16, -17, -15, -18, -26, -28, -18, 7, 41,
60, 47, 12, -30, -63, -65, -36, 5, 39, 50, 32, -1, -23, -21, -3, 21, 30, 19, 0,
-20, -38, -40, -23, 5, 31, 41, 33, 10, -15, -32, -34, -22, -2, 12, 13, 5, -5,
-9, -3, 9, 16, 15, 9, 1, -3, 2, 10, 19, 22, 17, 7, -6, -24, -45, -68, -71, -42,
4, 44, 61, 51, 26, 2, -16, -24, -24, -19, -12, -6, 0, 15, 32, 41, 32, 3, -32,
-51, -46, -20, 15, 42, 49, 33, 1, -24, -27, -14, 7, 18, 12, -1, -15, -27, -30,
-22, -4, 13, 25, 23, 9, -7, -19, -22, -14, 0, 12, 14, 4, -7, -11, -6, 6, 16, 15,
9, 2, 0, 9, 22, 28, 25, 14, 2, -7, -16, -28, -48, -69, -69, -38, 6, 43, 63, 58,
33, 3, -21, -36, -36, -23, -9, 3, 16, 27, 34, 33, 14, -17, -40, -43, -29, -3,
23, 39, 36, 15, -9, -22, -17, -3, 8, 9, 4, -1, -4, -7, -6, -1, 9, 18, 17, 3,
-16, -29, -36, -28, -8, 13, 24, 15, -5, -21, -22, -9, 11, 22, 22, 14, 3, -4, -1,
7, 16, 21, 20, 16, 8, -3, -19, -40, -62, -70, -51, -12, 29, 59, 63, 43, 12, -20,
-42, -44, -27, -1, 20, 30, 28, 17, 5, -5, -16, -15, -7, -2, 1, 5, 10, 18, 21,
16, 5, -5, -12, -17, -19, -11, 0, 8, 9, 2, -2, 2, 6, 5, -5, -20, -31, -34, -24,
-6, 14, 27, 23, 4, -13, -19, -11, 6, 21, 29, 28, 17, 2, -6, -2, 6, 13, 13, 7, 2,
0, -2, -13, -36, -65, -76, -49, 3, 54, 82, 70, 25, -23, -57, -65, -43, -5, 24,
30, 22, 9, -1, 0, 4, 3, 4, 0, -9, -10, 1, 20, 38, 36, 17, -8, -29, -37, -31,
-16, 3, 18, 21, 15, 2, -5, -4, -3, -2, -3, -9, -17, -24, -25, -15, 3, 16, 14, 0,
-16, -20, -10, 8, 27, 39, 37, 21, 1, -12, -15, -8, 2, 7, 15, 23, 20, 7, -19,
-57, -79, -68, -22, 34, 70, 68, 34, -9, -42, -54, -41, -13, 13, 24, 22, 17, 17,
23, 25, 11, -11, -25, -32, -24, -1, 26, 43, 40, 15, -14, -34, -40, -32, -16, 0,
13, 17, 9, -5, -15, -15, -5, 11, 17, 9, -6, -25, -36, -26, -3, 21, 26, 7, -17,
-27, -16, 10, 35, 48, 43, 22, -3, -18, -18, -8, 0, 7, 13, 20, 20, 9, -14, -45,
-70, -67, -30, 20, 58, 68, 42, -1, -37, -57, -52, -26, 5, 24, 26, 21, 19, 22,
23, 11, -11, -30, -38, -28, 0, 34, 57, 54, 24, -14, -38, -45, -35, -14, 4, 13,
9, -6, -19, -19, -2, 18, 30, 25, 4, -20, -38, -39, -19, 8, 28, 28, 7, -15, -21,
-7, 17, 36, 40, 29, 8, -13, -19, -11, 4, 14, 16, 14, 12, 4, -12, -34, -61, -73,
-54, -15, 27, 55, 55, 31, -2, -33, -51, -48, -27, -1, 17, 26, 31, 35, 36, 29, 6,
-19, -34, -37, -22, 7, 39, 59, 53, 20, -18, -39, -42, -31, -14, 2, 10, 5, -8,
-17, -12, 6, 23, 29, 20, -2, -28, -45, -45, -26, 1, 22, 26, 12, -6, -18, -15, 4,
24, 37, 36, 19, -3, -15, -12, 1, 15, 24, 24, 12, -8, -32, -55, -68, -55, -14,
29, 56, 58, 36, 6, -21, -40, -44, -32, -14, 4, 16, 24, 30, 32, 28, 10, -15, -33,
-38, -33, -14, 14, 39, 51, 42, 14, -14, -27, -30, -25, -15, -3, 7, 6, -5, -13,
-10, 4, 20, 27, 22, 6, -18, -37, -39, -26, -4, 13, 15, 6, -3, -9, -5, 11, 27,
34, 27, 4, -19, -25, -16, 4, 25, 37, 36, 19, -10, -41, -69, -77, -52, -5, 38,
63, 60, 32, 0, -28, -46, -48, -36, -17, 4, 22, 35, 42, 40, 26, -2, -28, -38,
-35, -23, -3, 16, 30, 35, 26, 9, -4, -10, -14, -18, -18, -11, 2, 9, 6, 2, 0, 3,
10, 12, 8, -3, -20, -29, -25, -14, -2, 5, 2, -6, -10, -11, -2, 13, 27, 33, 25,
6, -10, -16, -11, 2, 20, 32, 33, 17, -10, -40, -66, -75, -55, -12, 30, 57, 58,
37, 10, -16, -37, -44, -35, -15, 7, 25, 36, 40, 34, 19, -7, -27, -29, -22, -12,
0, 10, 18, 21, 13, 4, 0, -2, -8, -17, -24, -20, -7, 4, 7, 4, 4, 6, 8, 5, -2,
-12, -23, -26, -20, -7, 8, 17, 14, 6, -1, -4, 1, 11, 22, 29, 22, 5, -12, -17,
-14, -1, 15, 27, 30, 20, -3, -30, -58, -76, -65, -26, 21, 55, 63, 43, 9, -23,
-45, -49, -33, -7, 14, 22, 23, 21, 20, 18, 4, -10, -14, -15, -14, -6, 7, 23, 32,
25, 10, 0, -5, -9, -14, -19, -16, -9, -4, -3, -2, 5, 12, 16, 13, 4, -10, -25,
-32, -29, -16, 3, 14, 11, 1, -8, -11, -2, 9, 21, 29, 23, 6, -9, -14, -10, 1, 15,
22, 24, 16, 0, -18, -41, -64, -72, -48, 3, 53, 77, 64, 22, -22, -51, -55, -32,
7, 37, 41, 26, 8, -1, 2, 5, -3, -12, -17, -24, -23, -7, 16, 36, 33, 9, -14, -25,
-26, -17, -4, 9, 18, 15, 3, -11, -13, -4, 3, 11, 9, -4, -19, -30, -29, -12, 10,
25, 23, 5, -12, -17, -9, 8, 27, 40, 37, 17, -6, -20, -21, -10, 4, 12, 16, 15, 6,
0, -10, -31, -61, -83, -64, -6, 51, 81, 69, 24, -20, -49, -55, -29, 7, 28, 22,
3, -5, -2, 12, 23, 16, 7, -5, -20, -20, -2, 23, 39, 27, -1, -23, -33, -28, -10,
10, 22, 18, 0, -22, -30, -15, 5, 24, 32, 17, -8, -33, -46, -37, -9, 19, 31, 20,
-6, -23, -19, -3, 17, 33, 37, 23, 0, -18, -21, -9, 4, 13, 12, 6, 2, -1, 4, 7,
-2, -27, -58, -73, -44, 12, 56, 70, 45, 1, -33, -43, -29, 1, 25, 27, 13, -5,
-13, -9, 4, 12, 9, 2, -5, -10, -1, 12, 16, 9, -5, -19, -26, -13, 11, 29, 30, 10,
-15, -30, -28, -15, 4, 21, 24, 14, -7, -25, -29, -21, -5, 13, 19, 10, -8, -22,
-20, -3, 15, 24, 23, 14, 2, -6, -10, -12, -8, -4, -1, 6, 13, 20, 25, 22, 11, -7,
-28, -51, -69, -59, -19, 27, 56, 56, 33, 3, -19, -31, -28, -13, 3, 12, 9, 0, -3,
-4, 2, 16, 25, 32, 26, 1, -25, -35, -30, -11, 5, 14, 19, 18, 3, -11, -17, -14,
0, 7, 5, 1, -3, -6, -6, -3, -6, -8, -9, -10, -3, 5, 5, 1, -3, -8, -5, 1, 8, 17,
25, 25, 14, -3, -19, -27, -24, -9, 15, 36, 45, 36, 14, -6, -20, -28, -32, -41,
-59, -68, -45, 4, 50, 72, 59, 21, -12, -35, -40, -23, 2, 17, 12, -5, -12, -2,
25, 53, 51, 27, -11, -52, -67, -48, -6, 42, 63, 45, 11, -19, -30, -19, -2, 14,
18, 5, -15, -28, -21, -4, 12, 16, 2, -15, -27, -30, -15, 8, 20, 16, -3, -24,
-29, -14, 13, 37, 43, 29, 1, -22, -31, -21, 1, 18, 28, 31, 27, 17, 0, -16, -23,
-18, -5, 0, -12, -36, -55, -38, 5, 42, 59, 46, 14, -16, -37, -39, -21, 3, 21,
20, 6, -4, -3, 15, 30, 23, 5, -18, -36, -33, -16, 7, 28, 26, 4, -16, -20, -8,
10, 20, 15, 1, -18, -32, -28, -9, 12, 19, 13, 1, -9, -10, -8, -2, 4, 5, -4, -19,
-25, -14, 5, 24, 32, 29, 22, 14, 2, -7, -12, -12, -6, 2, 12, 22, 20, 2, -19,
-27, -17, 4, 16, 4, -28, -68, -84, -52, 11, 67, 91, 66, 12, -32, -58, -53, -16,
17, 27, 15, -6, -12, 6, 35, 49, 40, 15, -17, -38, -39, -15, 17, 36, 25, 2, -13,
-13, -2, 2, -4, -12, -19, -22, -19, -12, 0, 9, 9, 4, -3, -6, -5, -2, 1, -3, -17,
-30, -31, -17, 12, 38, 46, 38, 24, 11, -2, -11, -17, -20, -15, -2, 15, 33, 43,
32, 4, -19, -27, -12, 10, 14, -5, -42, -79, -86, -44, 25, 79, 86, 44, -16, -55,
-66, -48, -10, 21, 30, 20, 2, -1, 16, 37, 43, 26, 2, -19, -34, -32, -12, 12, 27,
27, 10, -3, -3, -5, -7, -10, -15, -16, -13, -9, -4, 4, 6, 3, 1, -2, -4, -6, -9,
-12, -13, -11, -6, 3, 10, 15, 19, 18, 16, 13, 11, 6, -3, -15, -25, -27, -20, -2,
23, 41, 42, 24, -2, -20, -20, -6, 5, 5, -12, -39, -61, -66, -30, 29, 65, 64, 30,
-17, -44, -47, -31, 1, 30, 38, 22, 1, -3, 5, 18, 28, 23, 5, -19, -45, -46, -21,
12, 39, 41, 21, 0, -16, -21, -16, -7, -1, -1, -8, -18, -23, -16, 1, 21, 32, 24,
7, -11, -20, -15, -2, 4, -3, -16, -26, -18, 7, 33, 52, 48, 22, -14, -42, -50,
-38, -11, 16, 38, 46, 40, 26, 6, -12, -26, -34, -30, -16, -1, 7, -2, -20, -40,
-45, -16, 20, 39, 38, 10, -17, -26, -18, 6, 32, 40, 26, -6, -27, -21, 7, 40, 50,
22, -17, -53, -64, -37, 6, 45, 58, 35, -6, -41, -49, -31, -2, 20, 22, 6, -16,
-26, -15, 11, 34, 37, 18, -14, -35, -37, -22, 4, 20, 18, 2, -15, -16, 5, 26, 32,
25, 1, -20, -28, -26, -11, 5, 14, 19, 20, 17, 10, 1, -10, -19, -24, -18, -3, 13,
20, 13, -8, -38, -61, -57, -19, 32, 60, 54, 25, -7, -26, -24, -6, 17, 29, 16,
-10, -22, -19, 2, 25, 27, 14, -4, -22, -30, -20, 2, 19, 23, 9, -14, -23, -19,
-7, 8, 12, 5, -2, -11, -16, -10, 0, 12, 18, 16, 7, -4, -13, -17, -18, -15, -11,
-7, 0, 10, 23, 33, 34, 28, 12, -8, -26, -41, -41, -26, -1, 26, 44, 43, 28, 4,
-20, -29, -20, -3, 12, 15, 4, -14, -29, -35, -36, -24, 6, 29, 31, 17, -5, -16,
-8, 5, 17, 19, 3, -23, -41, -31, -3, 31, 53, 40, 10, -20, -42, -38, -8, 23, 43,
40, 10, -22, -39, -33, -7, 19, 27, 17, 0, -15, -22, -15, 1, 12, 11, 1, -12, -15,
-9, -6, -6, -9, -12, -12, -4, 10, 26, 33, 27, 11, -7, -20, -28, -26, -19, -4,
15, 31, 40, 34, 18, -2, -19, -22, -16, -5, 3, 1, -6, -9, -10, -11, -17, -28,
-25, -4, 13, 19, 18, 12, 4, -2, -6, -6, -6, -10, -15, -7, 8, 24, 34, 26, 9, -9,
-21, -16, -1, 13, 22, 19, 1, -17, -23, -13, 6, 18, 15, -1, -19, -30, -23, -3,
15, 24, 19, 4, -10, -20, -22, -20, -17, -12, -8, -4, 4, 12, 16, 20, 21, 17, 8,
-5, -16, -22, -21, -12, 5, 24, 32, 24, 8, -7, -12, -4, 5, 9, 7, -5, -17, -15,
-1, 19, 25, 3, -41, -78, -76, -39, 14, 57, 70, 54, 19, -21, -39, -27, -4, 13,
12, -1, -11, -14, 0, 19, 29, 31, 19, -5, -22, -26, -20, -6, 2, 4, 5, 4, 4, 8,
13, 15, 10, -5, -23, -33, -27, -11, 9, 24, 23, 8, -11, -28, -33, -21, -5, 11,
20, 17, 17, 16, 12, 10, 2, -10, -22, -29, -24, -6, 16, 28, 26, 13, 1, -3, -2, 4,
5, -1, -11, -21, -18, 2, 27, 41, 28, -13, -63, -95, -74, -8, 58, 90, 70, 17,
-33, -62, -52, -15, 18, 30, 11, -18, -24, -8, 26, 53, 49, 25, -12, -44, -54,
-37, 1, 36, 47, 33, 6, -15, -17, -6, 10, 13, -4, -29, -48, -41, -10, 23, 44, 39,
14, -17, -38, -37, -18, 6, 20, 17, 5, -8, -8, 2, 9, 15, 11, 2, -2, -6, -4, 1,
-1, -4, -3, 1, 11, 20, 17, 6, -9, -19, -19, -9, 3, 9, 10, 7, 4, 3, -3, -18, -36,
-35, -15, 8, 19, 15, 2, -12, -23, -23, -11, 10, 24, 21, 12, 4, 1, 0, -1, 1, 6,
12, 7, 0, 0, 2, 4, 6, 3, 1, 0, -4, -4, -2, -5, -9, -12, -12, -9, -6, 1, 10, 17,
16, 2, -13, -22, -23, -16, -6, 2, 0, -5, -7, -2, 11, 23, 25, 20, 3, -21, -36,
-35, -19, 5, 27, 38, 39, 28, 8, -11, -20, -19, -11, -6, -3, 3, 13, 26, 41, 46,
27, -18, -75, -106, -88, -34, 20, 55, 60, 39, 7, -17, -18, 2, 15, 6, -16, -36,
-36, -12, 22, 53, 65, 42, -3, -45, -57, -38, -6, 23, 30, 17, -1, -12, -4, 16,
26, 17, -11, -41, -52, -41, -9, 29, 48, 40, 11, -23, -39, -33, -13, 8, 15, 7,
-5, -11, 0, 20, 34, 33, 11, -19, -42, -41, -20, 4, 24, 32, 25, 14, 8, 5, 1, -6,
-15, -23, -21, -13, 1, 21, 35, 42, 36, 9, -29, -69, -98, -91, -45, 14, 57, 67,
48, 14, -13, -20, -8, 6, 7, -7, -24, -25, -1, 31, 54, 60, 39, 6, -25, -43, -34,
-10, 14, 26, 17, 1, -10, -11, -1, 6, 1, -13, -32, -41, -30, -4, 27, 41, 32, 10,
-17, -30, -26, -13, 3, 7, -3, -16, -19, -10, 5, 21, 28, 21, 6, -7, -12, -6, -1,
-1, -1, -1, 7, 20, 31, 33, 17, -8, -29, -34, -21, -2, 15, 23, 23, 23, 17, 4,
-16, -46, -78, -86, -52, 3, 45, 62, 48, 21, -1, -10, -5, 1, -2, -16, -34, -37,
-13, 21, 52, 64, 43, 7, -31, -52, -46, -20, 11, 31, 33, 21, 6, -1, 0, 2, -2,
-19, -37, -43, -32, -3, 30, 47, 44, 20, -11, -30, -32, -21, -5, 5, 6, 0, -3, 1,
10, 23, 25, 16, 3, -12, -22, -23, -19, -14, -7, 0, 11, 24, 32, 28, 6, -20, -40,
-44, -30, -11, 11, 27, 34, 39, 39, 30, 11, -24, -63, -86, -70, -21, 27, 56, 58,
37, 12, -6, -14, -12, -16, -25, -36, -36, -13, 19, 50, 68, 57, 25, -15, -48,
-58, -43, -9, 22, 36, 31, 14, 2, 1, 3, 3, -8, -26, -37, -36, -20, 6, 27, 31, 21,
1, -16, -24, -23, -16, -6, 2, 8, 8, 8, 10, 16, 18, 13, 1, -13, -20, -24, -22,
-17, -9, 1, 12, 22, 26, 24, 8, -11, -22, -21, -7, 10, 27, 40, 41, 34, 24, 10,
-10, -36, -66, -85, -74, -34, 8, 36, 48, 41, 28, 16, 0, -12, -24, -34, -37, -31,
-4, 28, 51, 59, 42, 13, -17, -38, -41, -27, -2, 14, 15, 8, 1, 2, 11, 15, 9, -7,
-29, -43, -36, -14, 15, 36, 38, 27, 12, -2, -10, -15, -21, -24, -25, -21, -7,
10, 23, 30, 26, 13, -3, -14, -19, -19, -13, -7, -2, 3, 10, 21, 29, 23, 3, -22,
-37, -37, -23, -2, 19, 33, 34, 30, 28, 22, 4, -26, -62, -89, -80, -34, 24, 67,
80, 63, 28, -8, -32, -41, -37, -27, -17, -8, 5, 21, 33, 41, 36, 18, -7, -30,
-42, -36, -9, 18, 33, 35, 20, 3, -6, -10, -11, -14, -22, -28, -26, -13, 6, 22,
30, 28, 14, -7, -25, -31, -26, -10, 8, 20, 26, 23, 13, 8, 4, -2, -8, -17, -23,
-24, -18, -11, -5, 2, 9, 15, 17, 11, -3, -16, -21, -18, -6, 7, 16, 22, 26, 33,
40, 35, 9, -31, -74, -97, -77, -20, 35, 67, 66, 40, 11, -8, -17, -19, -19, -24,
-26, -18, 3, 29, 44, 46, 28, 1, -21, -36, -34, -18, 2, 11, 10, 4, -3, -4, 2, 4,
-4, -19, -36, -39, -21, 5, 27, 37, 33, 19, 1, -11, -13, -8, 0, 6, 7, 6, 7, 9,
14, 21, 20, 9, -9, -25, -31, -27, -13, -1, 8, 10, 6, 6, 4, 2, -4, -15, -22, -26,
-25, -17, -3, 18, 35, 46, 45, 23, -15, -57, -89, -86, -40, 19, 61, 78, 68, 44,
20, 3, -11, -21, -30, -40, -35, -13, 16, 41, 48, 38, 13, -11, -27, -37, -32,
-20, -9, -1, 5, 9, 8, 6, 5, -2, -14, -26, -33, -30, -15, 2, 17, 26, 28, 20, 7,
-2, -9, -12, -8, -1, 6, 10, 12, 15, 21, 28, 23, 8, -12, -29, -35, -29, -15, 0,
10, 10, 8, 9, 9, 7, -4, -19, -29, -32, -24, -7, 18, 42, 54, 54, 36, 1, -41, -81,
-100, -78, -23, 29, 64, 75, 60, 33, 7, -13, -26, -35, -40, -38, -19, 13, 44, 57,
50, 25, -6, -28, -36, -31, -17, -5, 1, 3, 5, 8, 13, 18, 16, 0, -22, -38, -40,
-27, -4, 14, 26, 27, 17, 3, -9, -13, -12, -8, 0, 6, 10, 11, 14, 20, 24, 20, 9,
-10, -27, -37, -34, -20, -6, 6, 10, 8, 9, 10, 13, 8, -5, -20, -30, -28, -17, 4,
30, 48, 54, 43, 14, -25, -66, -96, -97, -57, 1, 49, 78, 78, 57, 26, -2, -19,
-27, -29, -29, -23, -4, 21, 36, 39, 33, 15, -3, -18, -27, -27, -23, -14, -6, 5,
14, 18, 18, 12, -4, -21, -32, -33, -23, -10, 1, 12, 19, 20, 14, 4, -4, -13, -19,
-17, -6, 9, 20, 24, 23, 19, 13, 6, 0, -7, -16, -23, -23, -17, -6, 5, 12, 15, 14,
10, 1, -11, -22, -30, -27, -16, 0, 23, 45, 57, 53, 25, -20, -68, -100, -93, -52,
2, 51, 78, 75, 51, 16, -13, -28, -31, -29, -30, -22, -3, 17, 36, 41, 34, 17, -3,
-17, -26, -23, -15, -7, 1, 4, 4, 4, 5, 7, 3, -5, -12, -20, -21, -16, -7, 6, 15,
17, 8, -3, -11, -13, -7, 0, 6, 10, 11, 11, 12, 11, 7, 2, -3, -8, -10, -11, -7,
-4, 1, 5, 7, 7, 4, 4, 2, -1, -5, -13, -16, -11, -1, 18, 36, 43, 31, 0, -44, -81,
-88, -62, -23, 18, 52, 66, 57, 29, -4, -28, -32, -23, -14, -3, 8, 15, 20, 23,
22, 15, 13, 9, 2, -5, -11, -13, -11, -7, -3, 1, 2, 2, 2, 0, -3, -9, -19, -24,
-21, -14, -3, 7, 10, 6, -2, -10, -8, -1, 6, 9, 6, 0, -2, 7, 13, 14, 10, 3, -4,
-11, -11, -7, 0, 5, 4, 6, 5, 4, 2, -1, 1, -1, -4, -6, -3, 9, 23, 34, 33, 13,
-20, -60, -84, -70, -33, 9, 41, 58, 56, 33, 0, -28, -39, -29, -16, -8, 2, 11,
12, 10, 12, 11, 8, 7, 3, 0, -2, -5, -7, -5, 1, 3, 5, 8, 10, 9, 4, -2, -7, -10,
-15, -16, -13, -5, 1, 0, -2, -4, -5, -3, 1, 5, 5, -3, -11, -10, 0, 8, 11, 10, 8,
2, -4, -7, -5, -1, -2, 0, 3, 7, 10, 5, 1, -1, -4, -5, -4, 4, 16, 27, 29, 19, -2,
-35, -69, -80, -54, -12, 22, 45, 52, 43, 19, -12, -31, -30, -15, -6, 0, 11, 16,
13, 7, 4, 3, 4, 4, 3, 6, 9, 3, -4, -7, -8, -8, -5, 3, 10, 13, 6, -3, -12, -16,
-21, -21, -12, -3, 0, -2, -1, 2, 6, 12, 12, 12, 5, -9, -16, -11, 1, 8, 13, 15,
11, 6, -2, -3, -1, -5, -10, -14, -10, -2, 3, 6, 7, 4, -2, -6, -6, 2, 15, 26, 28,
18, -7, -42, -71, -69, -35, 5, 36, 53, 53, 38, 9, -20, -35, -29, -14, -7, 3, 12,
14, 8, -1, -3, 0, 8, 11, 7, 1, -8, -16, -19, -13, -3, 5, 9, 11, 13, 9, 1, -8,
-12, -12, -13, -7, 2, 9, 9, 3, 1, -1, 1, 4, 7, 8, 2, -9, -13, -7, 0, 7, 11, 11,
10, 3, -3, -4, -6, -9, -14, -15, -10, -3, 2, 3, 5, 3, 0, -1, -2, 4, 14, 20, 23,
13, -10, -41, -68, -63, -29, 10, 44, 61, 60, 37, 2, -33, -47, -33, -14, 2, 14,
21, 19, 7, -1, -3, 4, 16, 18, 8, -5, -15, -22, -17, -5, 8, 15, 13, 7, 0, -8,
-14, -19, -17, -12, -10, -4, 1, 4, 1, -4, -6, -8, -6, -3, 2, 8, 7, 2, -2, -1, 1,
4, 7, 10, 12, 10, 7, 3, -2, -6, -10, -9, -3, 4, 8, 10, 7, 0, -2, -3, -3, 0, 4,
9, 13, 11, 2, -17, -37, -54, -57, -32, 3, 33, 49, 42, 22, -7, -27, -31, -20, 2,
17, 20, 17, 8, -3, -2, 9, 22, 30, 20, -3, -26, -34, -28, -13, 6, 15, 14, 8, -2,
-8, -14, -17, -15, -13, -8, -4, 1, 7, 10, 10, 4, 1, 0, -2, -1, 3, 3, 2, -2, -9,
-11, -6, 0, 7, 13, 15, 15, 7, -5, -15, -19, -17, -10, 1, 14, 22, 17, 6, -4, -12,
-14, -11, -5, 4, 10, 15, 15, 9, 0, -17, -34, -47, -39, -9, 19, 37, 37, 25, 8,
-14, -30, -30, -18, -1, 7, 8, 8, 3, 1, 7, 20, 29, 24, 3, -19, -29, -25, -8, 13,
29, 28, 14, -6, -19, -21, -21, -17, -7, 1, 2, -2, -3, 0, 3, 4, 3, 4, 3, -1, -2,
0, 3, 3, -3, -8, -4, 3, 8, 14, 17, 16, 7, -10, -23, -29, -27, -16, 1, 18, 28,
22, 6, -13, -26, -26, -15, 4, 21, 30, 28, 16, 3, -6, -11, -18, -27, -36, -29,
-8, 11, 27, 32, 26, 10, -13, -28, -30, -15, 4, 13, 15, 9, 1, -3, 1, 9, 13, 10,
-5, -18, -19, -9, 8, 17, 16, 7, -8, -16, -16, -10, 0, 7, 11, 9, 3, -3, -9, -10,
-4, 2, 10, 12, 6, 1, -3, -5, -6, -7, -8, -10, -7, -3, 3, 10, 14, 12, 4, -13,
-29, -32, -24, -5, 17, 29, 29, 12, -10, -24, -21, -3, 15, 30, 32, 22, 11, 2, -1,
0, -3, -17, -37, -43, -26, 0, 23, 36, 31, 16, -11, -33, -36, -20, 9, 24, 23, 11,
-6, -19, -22, -10, 7, 19, 16, -1, -11, -11, -5, 4, 7, 3, -7, -15, -14, -6, 5,
11, 11, 6, -4, -13, -16, -11, 3, 13, 16, 15, 6, -2, -5, -5, -3, -2, -5, -10, -8,
-1, 10, 21, 26, 24, 11, -6, -25, -33, -28, -14, 7, 20, 23, 14, -4, -16, -23,
-16, -2, 6, 11, 9, 8, 8, 5, 1, -8, -25, -41, -39, -14, 14, 32, 34, 20, 4, -11,
-23, -19, -2, 20, 30, 22, 10, -6, -14, -12, -7, 9, 21, 19, 7, -9, -12, -10, -5,
-3, -6, -5, -6, -7, -5, -3, 0, -1, -4, -7, -9, -7, -5, 0, 7, 12, 14, 9, 4, 2,
-3, -6, -11, -15, -16, -8, 2, 12, 19, 20, 15, 4, -11, -26, -32, -26, -11, 8, 23,
29, 23, 9, -5, -11, -9, -4, 3, 8, 14, 19, 18, 7, -14, -40, -58, -51, -19, 20,
46, 47, 26, -1, -24, -33, -28, -10, 17, 32, 28, 11, -7, -16, -16, -8, 1, 15, 17,
6, -6, -16, -11, -6, -2, 3, 5, 11, 10, 1, -3, -8, -9, -8, -9, -4, 3, 7, 8, 6, 3,
0, -4, -4, -3, 0, 2, -4, -11, -14, -9, 4, 15, 20, 19, 12, 3, -10, -22, -25, -22,
-10, 2, 12, 21, 21, 12, 2, -6, -10, -12, -10, -1, 11, 24, 26, 8, -22, -54, -64,
-40, 3, 41, 58, 45, 11, -26, -48, -47, -26, 8, 38, 44, 30, 7, -14, -19, -14, -4,
11, 20, 17, 5, -9, -16, -16, -12, -6, 3, 13, 15, 11, 1, -9, -12, -14, -12, -7,
0, 8, 12, 11, 6, 0, -9, -15, -13, -5, 4, 7, 3, -3, -3, 0, 8, 14, 16, 14, 2, -12,
-27, -33, -28, -14, 9, 25, 31, 26, 11, -4, -15, -17, -13, -6, 2, 11, 19, 26, 22,
2, -29, -59, -62, -34, 6, 40, 53, 40, 12, -20, -40, -39, -16, 18, 40, 39, 23,
-1, -20, -23, -16, -1, 18, 27, 17, -2, -21, -30, -27, -17, -2, 13, 21, 17, 6,
-8, -15, -18, -16, -8, -5, 2, 8, 8, 11, 10, 4, 0, -3, -6, -5, -2, 1, 2, 4, 6, 7,
9, 10, 11, 11, 9, 0, -17, -33, -38, -28, -6, 16, 33, 32, 15, -7, -23, -27, -21,
-3, 15, 26, 29, 18, -5, -33, -55, -50, -17, 22, 51, 55, 36, 3, -27, -44, -44,
-21, 14, 41, 47, 30, 3, -19, -26, -22, -12, 3, 18, 19, 10, -7, -20, -20, -14,
-3, 11, 19, 19, 8, -10, -18, -21, -20, -14, -9, 1, 13, 18, 16, 12, 3, -9, -14,
-15, -9, -1, 1, 3, 6, 12, 16, 13, 10, 5, -3, -7, -10, -14, -17, -18, -16, -6, 9,
22, 26, 21, 6, -12, -24, -27, -18, 2, 23, 33, 26, 1, -33, -56, -47, -15, 23, 50,
51, 29, -1, -32, -47, -44, -24, 12, 39, 48, 37, 10, -11, -23, -25, -13, 2, 15,
21, 17, 3, -10, -17, -16, -3, 8, 13, 14, 2, -14, -21, -25, -22, -14, -6, 5, 18,
20, 17, 13, -1, -11, -16, -19, -12, -6, -3, 2, 8, 16, 23, 23, 17, 9, -5, -18,
-23, -19, -11, 0, 11, 17, 21, 20, 11, 2, -12, -23, -26, -25, -15, 0, 11, 10, -5,
-26, -30, -11, 12, 32, 39, 26, 6, -14, -30, -34, -24, -8, 10, 23, 27, 25, 14, 3,
-6, -14, -11, -7, -4, 2, 7, 6, 2, -4, -7, -3, 2, 3, 2, -1, -6, -5, -8, -14, -13,
-13, -4, 12, 20, 23, 19, 2, -14, -21, -21, -15, -5, 0, 5, 11, 15, 21, 24, 18, 9,
-1, -16, -28, -30, -23, -4, 15, 26, 32, 26, 10, -8, -20, -25, -19, -12, -16,
-22, -32, -31, -7, 21, 43, 55, 47, 25, 0, -27, -42, -42, -29, -10, 5, 17, 25,
28, 29, 22, 4, -10, -24, -34, -34, -24, -6, 12, 25, 28, 23, 15, 5, -7, -15, -17,
-14, -12, -12, -13, -12, -8, 8, 22, 26, 25, 9, -9, -20, -27, -26, -15, -4, 6,
15, 14, 14, 17, 17, 14, 10, -2, -20, -31, -34, -16, 15, 37, 48, 40, 15, -8, -21,
-25, -21, -24, -39, -55, -51, -17, 27, 59, 67, 47, 13, -19, -43, -48, -30, -4,
16, 24, 18, 5, -4, 4, 18, 32, 39, 25, -6, -36, -56, -55, -30, 2, 30, 45, 42, 28,
7, -11, -22, -25, -24, -22, -18, -10, -1, 8, 14, 18, 18, 12, 0, -18, -31, -40,
-37, -21, 0, 22, 37, 38, 31, 22, 11, -3, -15, -27, -30, -24, -12, 11, 30, 38,
34, 17, 0, -7, -6, -3, -9, -32, -60, -66, -40, 4, 47, 70, 64, 40, 10, -22, -45,
-50, -36, -13, 6, 14, 16, 16, 24, 32, 29, 22, 5, -24, -48, -55, -46, -21, 8, 24,
28, 26, 16, 8, 0, -5, -5, -8, -17, -21, -21, -15, 3, 20, 29, 31, 21, 4, -11,
-22, -26, -21, -12, -3, 8, 13, 18, 26, 30, 28, 20, 1, -24, -39, -46, -37, -13,
11, 30, 36, 29, 19, 7, -1, -10, -28, -51, -73, -68, -29, 18, 59, 77, 60, 28, -2,
-26, -37, -32, -17, -2, 4, 3, 0, 2, 16, 30, 32, 29, 17, -6, -27, -40, -40, -25,
-2, 13, 19, 19, 15, 9, 1, -3, -7, -15, -24, -30, -27, -15, 7, 25, 33, 30, 20, 5,
-6, -14, -23, -24, -21, -17, -4, 12, 24, 33, 35, 26, 13, -7, -28, -36, -33, -16,
8, 25, 30, 22, 6, -8, -12, -5, 5, 1, -21, -56, -74, -53, -9, 42, 76, 73, 48, 15,
-19, -39, -42, -28, -10, 0, 0, -3, -1, 13, 29, 32, 28, 17, -3, -22, -35, -34,
-20, 1, 16, 19, 13, 8, 4, 2, 2, 2, -4, -14, -20, -23, -19, -2, 15, 24, 26, 15,
-2, -7, -11, -14, -12, -11, -12, -5, 5, 8, 15, 22, 18, 11, -2, -21, -30, -27,
-19, -2, 14, 24, 28, 23, 12, 3, -1, 1, 0, -12, -36, -59, -64, -35, 13, 49, 65,
53, 22, -6, -24, -30, -21, -4, 5, 2, -8, -15, -11, 9, 29, 35, 30, 16, -4, -23,
-31, -29, -18, -2, 7, 6, 5, 8, 9, 11, 9, 0, -8, -10, -12, -13, -13, -7, 2, 14,
21, 17, 9, -5, -19, -27, -28, -20, -3, 15, 23, 22, 20, 14, 7, 1, -11, -22, -23,
-20, -10, 5, 14, 24, 25, 16, 5, -7, -14, -12, -8, -10, -20, -33, -43, -29, 2,
33, 53, 51, 30, 9, -10, -22, -23, -15, -5, 2, 1, -3, -3, 5, 19, 26, 21, 10, -4,
-17, -21, -18, -13, -5, -1, -3, -3, 0, 5, 7, 0, -10, -15, -14, -10, -6, -3, 6,
17, 20, 18, 8, -7, -16, -19, -20, -16, -7, 3, 19, 29, 28, 23, 13, -1, -12, -21,
-28, -21, -10, -1, 10, 22, 29, 31, 22, -2, -21, -29, -25, -11, 4, 8, -2, -21,
-42, -37, -5, 30, 52, 51, 28, 0, -16, -22, -20, -13, -9, -10, -16, -14, -3, 15,
34, 39, 22, -2, -20, -30, -29, -19, -9, 2, 11, 15, 12, 9, 8, 2, -7, -10, -11,
-10, -8, -8, -8, -2, 11, 23, 25, 13, -5, -21, -27, -20, -7, 9, 21, 25, 21, 10,
-1, -7, -7, -9, -9, -11, -15, -16, -9, 4, 19, 31, 33, 20, 0, -17, -27, -22, -8,
3, 8, 0, -20, -41, -47, -27, 7, 35, 48, 40, 21, 5, -6, -16, -23, -21, -20, -16,
-4, 13, 25, 35, 35, 19, 2, -9, -17, -19, -18, -17, -12, -3, 4, 8, 11, 14, 10, 1,
-7, -11, -12, -6, -3, -3, 0, 5, 6, 3, -4, -14, -16, -9, 2, 11, 9, 3, -1, 1, 7,
13, 10, 3, -7, -18, -23, -22, -13, 1, 16, 24, 23, 18, 8, -1, -4, -3, 1, 5, 8, 5,
-2, -11, -27, -45, -49, -27, 8, 40, 56, 47, 26, 7, -13, -32, -42, -39, -27, -9,
11, 21, 23, 22, 14, 5, 0, 0, 0, -1, -10, -25, -29, -23, -9, 10, 23, 27, 23, 12,
0, -6, -10, -9, -7, -6, -5, 2, 8, 9, 9, 2, -2, 0, 1, -2, -8, -14, -14, -4, 7,
11, 11, 4, -8, -14, -18, -19, -9, 3, 11, 16, 12, 6, 5, 5, 7, 5, -2, -6, -2, 6,
12, 13, 1, -24, -50, -56, -31, 10, 47, 66, 52, 21, -10, -34, -46, -41, -24, -7,
11, 18, 15, 9, 9, 15, 20, 23, 15, -5, -27, -43, -46, -34, -11, 8, 22, 31, 33,
28, 16, 5, -4, -14, -21, -22, -18, -7, 11, 20, 20, 13, 1, -9, -14, -17, -16,
-11, -7, 0, 7, 8, 7, 4, 1, -2, -2, -3, -2, 0, 0, 0, -1, 2, 8, 10, 6, -1, -5, -9,
-7, 3, 11, 18, 18, 3, -29, -60, -61, -29, 19, 57, 69, 47, 17, -9, -32, -40, -37,
-25, -8, 7, 13, 8, 4, 9, 19, 27, 30, 16, -11, -33, -45, -44, -24, 0, 20, 32, 34,
26, 12, -1, -5, -8, -13, -19, -26, -29, -16, 7, 24, 36, 31, 10, -12, -26, -26,
-13, 3, 8, 5, -5, -15, -14, -2, 11, 21, 24, 12, -4, -17, -22, -13, 5, 19, 25,
15, -2, -17, -24, -19, -4, 14, 25, 31, 24, 3, -30, -62, -74, -53, -3, 44, 70,
64, 34, 4, -18, -27, -26, -22, -19, -13, -13, -11, 1, 17, 37, 47, 39, 18, -8,
-29, -39, -37, -27, -10, 4, 14, 20, 23, 23, 20, 14, 2, -14, -28, -39, -35, -17,
5, 22, 25, 12, -8, -18, -19, -8, 9, 14, 5, -9, -20, -19, -2, 18, 29, 31, 17, -1,
-15, -20, -13, 2, 15, 18, 12, -3, -18, -21, -11, 3, 19, 27, 21, 8, -1, -7, -6,
-5, -17, -41, -63, -59, -24, 25, 63, 72, 50, 16, -15, -35, -44, -39, -27, -13,
0, 7, 15, 28, 42, 49, 42, 21, -7, -33, -49, -49, -37, -16, 7, 23, 29, 30, 29,
22, 11, -7, -31, -47, -47, -32, -5, 25, 41, 40, 26, 1, -19, -27, -21, -9, 0, -2,
-11, -15, -10, 4, 22, 35, 36, 25, 6, -15, -32, -38, -30, -10, 10, 27, 34, 21, 0,
-18, -26, -19, -2, 13, 17, 14, 4, -2, -4, 1, 9, 13, 6, -15, -41, -55, -37, -2,
30, 47, 36, 6, -18, -27, -27, -14, 1, 9, 13, 10, 3, 3, 12, 21, 22, 17, 3, -15,
-27, -31, -27, -12, 11, 26, 30, 23, 6, -15, -31, -37, -31, -15, 4, 19, 23, 22,
18, 10, 1, -7, -19, -25, -22, -11, 3, 13, 21, 25, 26, 22, 9, -5, -17, -23, -21,
-20, -17, -8, 3, 17, 26, 22, 10, -4, -19, -27, -22, -12, 3, 17, 21, 14, 5, 3, 3,
3, -1, -9, -14, -10, -4, -8, -21, -39, -41, -16, 21, 50, 60, 50, 25, 0, -20,
-33, -33, -16, 0, 11, 10, -3, -12, -7, 6, 16, 23, 18, -1, -20, -37, -40, -23, 2,
23, 30, 22, 8, 0, -1, 0, 0, -4, -13, -20, -22, -17, -2, 15, 28, 26, 10, -10,
-21, -19, -8, 2, 8, 11, 12, 10, 6, 0, -4, -5, -4, -6, -10, -12, -13, -9, 1, 10,
17, 16, 10, 0, -9, -11, -9, -2, 1, 2, 1, -2, -4, -2, 3, 7, 10, 14, 12, 5, -6,
-21, -36, -45, -36, -12, 18, 43, 49, 36, 18, 1, -10, -15, -17, -20, -23, -26,
-26, -14, 8, 31, 45, 40, 24, 5, -11, -19, -22, -24, -23, -14, -2, 12, 27, 34,
29, 15, -9, -30, -38, -34, -19, -2, 9, 15, 16, 9, -1, -10, -14, -4, 10, 14, 8,
-7, -19, -18, -8, 6, 18, 22, 14, 2, -14, -27, -26, -12, 8, 24, 30, 23, 7, -9,
-16, -16, -5, 9, 19, 19, 6, -11, -26, -27, -17, -2, 12, 19, 17, 10, 4, -1, -6,
-10, -22, -39, -49, -38, -4, 31, 56, 59, 41, 18, -2, -16, -27, -30, -27, -21,
-11, 0, 7, 18, 33, 36, 32, 19, -4, -27, -44, -51, -45, -24, 4, 30, 45, 46, 33,
10, -11, -26, -30, -25, -15, -8, -1, 7, 13, 17, 17, 10, 4, 0, -5, -11, -17, -21,
-16, -2, 13, 22, 22, 15, 7, 0, -8, -15, -20, -22, -17, -6, 6, 13, 12, 6, 0, -5,
-7, -4, -2, -2, -2, -5, -8, -8, -6, -1, 8, 16, 17, 17, 11, 7, 9, 10, 8, -5, -29,
-53, -61, -41, -1, 40, 65, 63, 42, 18, -6, -25, -39, -45, -38, -23, -5, 8, 13,
18, 27, 31, 28, 18, -3, -26, -43, -50, -41, -17, 14, 41, 51, 41, 19, -4, -19,
-20, -15, -11, -9, -9, -9, -3, 5, 13, 17, 15, 7, -1, -9, -16, -18, -14, -8, 1,
8, 13, 14, 11, 3, -5, -13, -18, -18, -14, -9, 1, 10, 15, 17, 12, 5, 2, 1, 4, 8,
7, 2, -4, -12, -17, -18, -14, -5, 7, 18, 23, 23, 14, -2, -18, -28, -28, -18, -1,
14, 14, -3, -28, -45, -34, 0, 41, 64, 57, 28, -4, -26, -31, -26, -16, -6, 0, 5,
6, 8, 12, 18, 17, 9, -5, -20, -27, -27, -17, -2, 9, 16, 17, 13, 5, -3, -10, -11,
-5, 1, 4, 0, -8, -9, -3, 4, 9, 6, -3, -9, -9, -5, 0, 4, 7, 11, 14, 12, 5, -2,
-7, -8, -8, -11, -16, -16, -12, -2, 10, 19, 25, 22, 11, -4, -21, -29, -25, -11,
3, 13, 15, 10, 6, 0, -5, -5, -5, -4, -2, -3, -2, 2, 6, 6, 6, 2, -4, -4, -4, -6,
-4, 0, 7, 18, 21, 11, -7, -31, -47, -39, -16, 8, 27, 34, 28, 18, 8, -3, -14,
-23, -27, -27, -19, -6, 7, 21, 32, 31, 20, 8, -4, -13, -15, -15, -14, -8, 1, 8,
11, 12, 9, 5, 1, -3, -9, -14, -14, -8, -2, 4, 6, 2, -1, -2, -2, -3, -3, -5, -6,
-2, 5, 11, 14, 11, 1, -10, -17, -17, -9, 1, 9, 11, 6, 1, -1, 2, 5, 4, -2, -10,
-16, -15, -5, 10, 21, 25, 20, 8, -3, -10, -14, -16, -14, -11, -7, -3, 1, 4, 4,
2, -2, -4, 0, 4, 7, 4, -4, -10, -11, -5, 4, 13, 13, 7, -1, -9, -12, -7, 2, 10,
14, 11, 1, -12, -25, -35, -33, -16, 11, 37, 49, 41, 19, -9, -30, -36, -33, -19,
-4, 6, 8, 8, 5, 6, 13, 18, 18, 14, 1, -15, -26, -28, -19, -1, 17, 28, 27, 14,
-2, -18, -27, -27, -17, -2, 11, 18, 15, 9, 2, -3, -5, -7, -7, -4, 2, 5, 4, -2,
-8, -9, -4, 2, 5, 5, 0, -6, -10, -12, -10, -4, 4, 15, 24, 25, 17, 2, -16, -26,
-24, -13, 1, 12, 12, 8, 0, -6, -7, -1, 5, 12, 11, 4, -7, -17, -21, -18, -9, 0,
6, 10, 11, 10, 8, 3, -3, -7, -6, -4, -1, 1, -1, -3, -3, -1, 2, 4, 3, -1, -4, -6,
-5, -2, 3, 5, 5, 4, 3, 1, -1, -2, -3, -3, -4, -6, -9, -8, -3, 4, 11, 14, 13, 7,
-1, -8, -12, -10, -5, 0, 0, -5, -11, -10, -4, 5, 12, 15, 12, 7, 2, -4, -9, -11,
-11, -8, -5, -3, -3, 0, 5, 11, 16, 18, 13, 1, -13, -24, -24, -13, 4, 19, 23, 17,
5, -6, -10, -8, -4, -4, -7, -11, -12, -9, -3, 4, 8, 8, 4, -2, -4, -3, 0, 2, 0,
-3, -4, -2, 4, 9, 10, 7, 2, -4, -9, -9, -5, 1, 5, 6, 3, -1, -4, -7, -6, -3, 0,
1, 1, -2, -4, -4, -3, 0, 3, 3, 1, 0, -2, -4, -4, -4, -1, 4, 6, 6, 3, 0, -1, 0,
2, 4, 4, 2, -1, -4, -4, -2, 1, 1, -2, -8, -11, -9, -4, 1, 4, 5, 3, 0, -4, -5,
-4, -1, 3, 5, 5, 3, 0, -2, -4, -4, -3, 1, 4, 6, 6, 2, -2, -4, -3, -1, 3, 5, 5,
3, 0, -3, -6, -8, -8, -8, -5, -1, 2, 4, 4, 2, 1, 1, 2, 1, -1, -4, -5, -7, -6,
-2, 2, 5, 2, };

#endif /* RAVEN_ARH_H_ */
