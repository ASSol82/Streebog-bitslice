#ifndef __FUNCTIONS_SSE__
#define __FUNCTIONS_SSE__


#include "VectorTypeSSE.h"
#include <stdint.h>
#include <stddef.h> // для определения size_t


#ifdef __cplusplus
extern "C" {
#endif


void *aligned_malloc(size_t size, uint32_t alignByte);
void aligned_free(void *ptr);

// T *dst - это, по сути, T dst[512];
void ConvertToBitSlice512Transpose8(uint32_t startNum, const uint8_t* src, T *dst);
// T *src - это T src[512];
void ConvertFromBitSlice512Transpose8(uint32_t startNum, const T* src, uint8_t* dst);

void SetByteInBitSliceSSE(int num, const uint8_t src, T *dst);

uint8_t GetBit_T(const T v, const int num);
void SetBit_T(T* v, int num, uint8_t b);


#ifdef __cplusplus
}
#endif


#endif
