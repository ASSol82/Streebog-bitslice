

#ifndef __VECTOR_TYPE_SSE__
#define __VECTOR_TYPE_SSE__


#include <stdint.h>
#include <immintrin.h> // AVX2 __m256i. для AVX-512 включить -mavx512f -mavx512cd -mavx512vl -mavx512bw -mavx512dq -mavx512ifma -mavx512vbmi


#define MaxCountMessage 256


#ifndef MaxCountMessage
#define MaxCountMessage 256
#endif


#if MaxCountMessage!=512 && MaxCountMessage!=256 && MaxCountMessage!=128 && MaxCountMessage!=64 && MaxCountMessage!=32 && MaxCountMessage!=16 && MaxCountMessage!=8
#error MaxCountMessage = 512,256,128,64,32,16,8
#endif


#if MaxCountMessage==512
typedef __m512i T;
#elif MaxCountMessage==256
typedef __m256i T;
#elif MaxCountMessage==128
typedef __m128i T;
#elif MaxCountMessage==64
typedef uint64_t T;
#elif MaxCountMessage==32
typedef uint32_t T;
#elif MaxCountMessage==16
typedef uint16_t T;
#elif MaxCountMessage==8
typedef uint8_t T;
#endif


#if defined _MSC_VER
#define _ALIGN(x) __declspec(align(x))
#else
#define _ALIGN(x) __attribute__ ((__aligned__(x)))
#endif


#endif // !__VECTOR_TYPE_SSE__
