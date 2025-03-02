#ifndef __LPS_BITSLICE_SSE__
#define __LPS_BITSLICE_SSE__


#include "VectorTypeSSE.h"


#ifdef __cplusplus
extern "C" {
#endif


void LPS_bitslice_SSE(T *b, T *t); // t временный вспомогательный массив


#ifdef __cplusplus
}
#endif

#endif
