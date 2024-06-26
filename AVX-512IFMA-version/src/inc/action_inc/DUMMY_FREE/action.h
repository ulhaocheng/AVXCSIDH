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
  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
  8,  8,  8,  8,  8,  8,  8,  11, 11, 11, 11, 11, 11, 11, 11, 11,
  11, 11, 11, 11, 11, 11, 11, 11, 11, 13, 13, 13, 13, 13, 13, 13, 
  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 
  13, 13, 13, 13, 13, 5,  7,  7,  7,  7   };

// base Montgomery curve A = 0, therefore twsited Edwards curve a = A+2C = 2, d = 4C = 4
static uint64_t E[2][HT_NWORDS] = {
  { 0x51DD37FDF5528, 0xA6E351B4CD9B5, 0xF19CA05B1E35A, 0x332E70D27D03C,
    0xC6CC7EECCFFBC, 0x3038EBB8F8AD4, 0x783A6FE52263C, 0xD69028257D6E9,
    0x2F2116636629D, 0x004B92BE4011D, },
  { 0x882A1CBF7E1D5, 0x596EF6C1661B2, 0xF2844E5A15499, 0x1155903DC93B7,
    0xB31E516D49785, 0x647510DECE90C, 0x6CC6034180A1D, 0x4EE2040046B02,
    0x65A62CFE2146A, 0x003170EDF0AF9, },
};

// -----------------------------------------------------------------------------
// SIMBA-5-11 parameters 

#define NUMBA 5
#define ROUND 11
#define MAXSIZEBA 15

static uint8_t SIZEBA[NUMBA] = { 15, 15, 15, 15, 14 };
static uint8_t BATCHES[NUMBA][MAXSIZEBA] = { 
  { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70 },
  { 1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71 },
  { 2, 7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72 },
  { 3, 8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58, 63, 68, 73 },
  { 4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69 }, };

static uint8_t LASTISO[NUMBA] = { 70, 71, 72, 73, 69 };
static uint16_t NUMISO = 763;

static uint8_t SICOBA[NUMBA] = { 59, 59, 59, 59, 60 };
static uint8_t COMPBA[NUMBA][N] = {
{  1,  2,  3,  4,  6,  7,  8,  9, 11, 12, 13, 14, 16, 17, 18, 19,
  21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 36, 37, 38, 39,
  41, 42, 43, 44, 46, 47, 48, 49, 51, 52, 53, 54, 56, 57, 58, 59,
  61, 62, 63, 64, 66, 67, 68, 69, 71, 72, 73, 74, 74, 74, 74, 74, 
  74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
{  0,  2,  3,  4,  5,  7,  8,  9, 10, 12, 13, 14, 15, 17, 18, 19,
  20, 22, 23, 24, 25, 27, 28, 29, 30, 32, 33, 34, 35, 37, 38, 39,
  40, 42, 43, 44, 45, 47, 48, 49, 50, 52, 53, 54, 55, 57, 58, 59,
  60, 62, 63, 64, 65, 67, 68, 69, 70, 72, 73, 74, 74, 74, 74, 74, 
  74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
{  0,  1,  3,  4,  5,  6,  8,  9, 10, 11, 13, 14, 15, 16, 18, 19,
  20, 21, 23, 24, 25, 26, 28, 29, 30, 31, 33, 34, 35, 36, 38, 39,
  40, 41, 43, 44, 45, 46, 48, 49, 50, 51, 53, 54, 55, 56, 58, 59,
  60, 61, 63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 74, 74, 74, 74, 
  74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
{  0,  1,  2,  4,  5,  6,  7,  9, 10, 11, 12, 14, 15, 16, 17, 19,
  20, 21, 22, 24, 25, 26, 27, 29, 30, 31, 32, 34, 35, 36, 37, 39,
  40, 41, 42, 44, 45, 46, 47, 49, 50, 51, 52, 54, 55, 56, 57, 59,
  60, 61, 62, 64, 65, 66, 67, 69, 70, 71, 72, 74, 74, 74, 74, 74, 
  74, 74, 74, 74, 74, 74, 74, 74, 74, 74 },
{  0,  1,  2,  3,  5,  6,  7,  8, 10, 11, 12, 13, 15, 16, 17, 18,
  20, 21, 22, 23, 25, 26, 27, 28, 30, 31, 32, 33, 35, 36, 37, 38,
  40, 41, 42, 43, 45, 46, 47, 48, 50, 51, 52, 53, 55, 56, 57, 58,
  60, 61, 62, 63, 65, 66, 67, 68, 70, 71, 72, 73, 74, 74, 74, 74,
  74, 74, 74, 74, 74, 74, 74, 74, 74, 74 } };

// parameters for hybrid-extra-infinity 
// HT_NUMISO + LL_NUMISO = NUMISO
static int HT_NUMISO = 646;
static int LL_NUMISO = 117;

#define LL_NUMIDX 9 
static uint8_t ll_idx[LL_NUMIDX] = { 60, 61, 62, 63, 64, 65, 66, 67, 68 };

// -----------------------------------------------------------------------------

void action(htpoint_t C, const __m512i *sk, const htpoint_t A);
void random_sk(uint8_t *sk);

#endif