

#ifndef __STREEBOG_BITSLICE_SSE_TEST__
#define __STREEBOG_BITSLICE_SSE_TEST__


#include "VectorType.h"


int Streebog_bitslice_SSE_test();
int Streebog_bitslice_SSE_array_test(uint32_t hashLength);
void Streebog_bitslice_test_ControlValue(uint32_t countTestMessage, uint64_t messageLength, uint32_t hashLength);


#endif
