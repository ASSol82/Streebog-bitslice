#ifndef __CONVERT_BITSLICE__
#define __CONVERT_BITSLICE__


#if MaxCountMessage==256


#include <stdint.h>
#include <immintrin.h>


void ConvertBitslice_32x32(const __m256i w256[4], uint32_t* p32, const uint32_t offset);


#endif //MaxCountMessage==256


#endif //__CONVERT_BITSLICE__
