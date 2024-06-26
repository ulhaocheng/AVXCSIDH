/**
 *******************************************************************************
 * @version 0.1
 * @date 2021-08-22
 * @copyright Copyright © 2021 by University of Luxembourg.
 * @author Developed at SnT APSIA by: Hao Cheng.
 *******************************************************************************
 */

#ifndef _ACTION_H_
#define _ACTION_H_

#include "gfparith.h"
#include "tedcurve.h"
#include "rng.h"

// exponent bound 
static int8_t B[N] =	{
  2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
  5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 9, 
  9, 9, 10, 10, 10, 10, 9, 8, 8, 8, 7, 7, 7, 7, 7, 6, 5, 1, 2, 2, 2, 2 };

// base Montgomery curve A = 0, therefore twsited Edwards curve a = A+2C = 2, d = 4C = 4
static uint64_t E[2][LL_NWORDS] = {
  { 0x65FD1E15990, 0x16DECECEEC5, 0x4F15D0E9268, 0x01B263BA219, 
    0x756DB68FC0C, 0x73543C49F07, 0x07C81483BEE, 0x2A15A1C8A08, 
    0x7B1ED6D95B1, 0x7D251910514, 0x493D00452A2, 0x01BC9B995DD },
  { 0x3BA6FFBEAA5, 0x546D3366D54, 0x2D8F1AD5371, 0x7D03CF19CA0, 
    0x778665CE1A4, 0x31B31FBB33F, 0x1C75DC7C56A, 0x6FE52263C30, 
    0x4AFADD2F074, 0x18A775A40A0, 0x0E97908B31B, 0x004B92BE401 },
};

// -----------------------------------------------------------------------------
// SIMBA-3-8 parameters 

#define NUMBA 3
#define ROUND 8
#define MAXSIZEBA 25

static uint8_t SIZEBA[NUMBA] = { 25, 25, 24 };
static uint8_t BATCHES[NUMBA][MAXSIZEBA] = { 
  {  0,  3,  6,  9, 12, 15, 18, 21, 24, 27, 30, 33, 
    36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72 },
  {  1,  4,  7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 
    37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73 },
  {  2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 
    38, 41, 44, 47, 50, 53, 56, 59, 62, 65, 68, 71 }, };

static uint8_t LASTISO[NUMBA] = { 72, 73, 71 };
static uint16_t NUMISO = 404;

static uint8_t SICOBA[NUMBA] = { 49, 49, 50 };
static uint8_t COMPBA[NUMBA][N] = {
  {  1,  2,  4,  5,  7,  8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 
    29, 31, 32, 34, 35, 37, 38, 40, 41, 43, 44, 46, 47, 49, 50, 52, 53, 55, 56, 
    58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 74, 74, 74, 74, 74, 74, 74, 
    74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
  {  0,  2,  3,  5,  6,  8,  9, 11, 12, 14, 15, 17, 18, 20, 21, 23, 24, 26, 27, 
    29, 30, 32, 33, 35, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51, 53, 54, 56,
    57, 59, 60, 62, 63, 65, 66, 68, 69, 71, 72, 74, 74, 74, 74, 74, 74, 74, 74,
    74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
  {  0,  1,  3,  4,  6,  7,  9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24, 25, 27,
    28, 30, 31, 33, 34, 36, 37, 39, 40, 42, 43, 45, 46, 48, 49, 51, 52, 54, 55,
    57, 58, 60, 61, 63, 64, 66, 67, 69, 70, 72, 73, 74, 74, 74, 74, 74, 74, 74,
    74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74 } };

// -----------------------------------------------------------------------------

void action_2x4w(llpoint_t C, const uint8_t *sk, const llpoint_t A);
void random_sk(uint8_t *sk);

#endif
