

#ifndef __SETTINGS__
#define __SETTINGS__


#include "VectorTypeSSE.h"


#if MaxCountMessage==512

#define MALLOCALIGN 64
#define _ZERORIGHT _mm512_setzero_si512()
#define _ZERO(a) ((a) = _mm512_setzero_si512())
#define _XOR(a,b) _mm512_xor_si512((a), (b))
#define _NOT(a) _mm512_xor_si512((a), _mm512_set1_epi32(0xFFFFFFFF))
#define _OR(a,b) _mm512_or_si512((a), (b))
#define _AND(a,b) _mm512_and_si512((a), (b))
#define _ANDNOT(a,b) _mm512_andnot_si512((a), (b))
#define IsZero(av_) (_mm512_cmp_epi32_mask((av_), _ZERORIGHT, _CMP_EQ_OQ) == 0xFFFF) //  _mm512_cmp_ps_mask((av_), _ZERORIGHT, _CMP_EQ_OQ) // пробую так сравнить

#elif MaxCountMessage==256

#define MALLOCALIGN 64
#define _ZERORIGHT _mm256_setzero_si256() // _mm256_set1_epi32(0)
#define _ZERO(a) ((a) = _mm256_setzero_si256()) // _mm256_set1_epi32(0) // _mm256_setzero_si256()
#define _XOR(a,b) _mm256_xor_si256((a), (b))
#define _NOT(a) _mm256_xor_si256((a), _mm256_set1_epi32(0xFFFFFFFF))
#define _OR(a,b) _mm256_or_si256((a), (b))
#define _AND(a,b) _mm256_and_si256((a), (b))
#define _ANDNOT(a,b) _mm256_andnot_si256((a), (b))
#define IsZero(v) _mm256_testz_si256((v), (v))

#elif MaxCountMessage==128

#define MALLOCALIGN 16
#define _ZERORIGHT _mm_setzero_si128() //_mm_set1_epi32(0)
#define _ZERO(a) ((a) = _mm_setzero_si128())
#define _XOR(a,b) _mm_xor_si128((a), (b))
#define _NOT(a) _mm_xor_si128((a), _mm_set1_epi32(0xFFFFFFFF))
#define _OR(a,b) _mm_or_si128((a), (b))
#define _AND(a,b) _mm_and_si128((a), (b))
#define _ANDNOT(a,b) _mm_andnot_si128((a), (b))
#define IsZero(v) _mm_testz_si128((v), (v))

#elif (MaxCountMessage<128)

#define MALLOCALIGN 16
#define _ZERORIGHT 0
#define _ZERO(a) ((a) = 0)
#define _XOR(a,b) ((a) ^ (b))
#define _NOT(a) (~(a))
#define _OR(a,b) ((a) | (b))
#define _AND(a,b) ((a) & (b))
#define _ANDNOT(a,b) (~(a) & (b))
#define IsZero(a) ((a)==0)

#endif


#endif
