#ifndef __CONVERT_BITSLICE__
#define __CONVERT_BITSLICE__


#if MaxCountMessage==256


#include <stdint.h>
#include <immintrin.h>


#define transpose8x8_4_macros(x) { \
x = _OR(_OR(_AND(x, c1), _SHIFTL64(_AND(x, c2), 7)), _AND(_SHIFTR64(x, 7), c2)); \
x = _OR(_OR(_AND(x, c3), _SHIFTL64(_AND(x, c4), 14)), _AND(_SHIFTR64(x, 14), c4)); \
x = _OR(_OR(_AND(x, c5), _SHIFTL64(_AND(x, c6), 28)), _AND(_SHIFTR64(x, 28), c6)); }


#define from_8x32_to_256(w256,p32,p0,p1,p2,p3,p4,p5,p6,p7) w256 = _mm256_set_epi64x( \
		(uint64_t)p32[p6]	|	(uint64_t)p32[p7]<<32, \
		(uint64_t)p32[p4]	|	(uint64_t)p32[p5]<<32, \
		(uint64_t)p32[p2]	|	(uint64_t)p32[p3]<<32, \
		(uint64_t)p32[p0]	|	(uint64_t)p32[p1]<<32);


#define value_8x32_to_256(w256,v0,v1,v2,v3,v4,v5,v6,v7) w256 = _mm256_set_epi64x( \
		(uint64_t)v6|(uint64_t)v7<<32, (uint64_t)v4|(uint64_t)v5<<32, (uint64_t)v2|(uint64_t)v3<<32,(uint64_t)v0|(uint64_t)v1<<32);


void ConvertBitslice_32x32(const __m256i w256[4], uint32_t* p32, const uint32_t offset);


#endif //MaxCountMessage==256


#endif //__CONVERT_BITSLICE__
