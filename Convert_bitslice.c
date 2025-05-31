

#include "VectorType.h"
#include "Convert_bitslice.h"
#include "LogicalOperations.h"


#if MaxCountMessage==256


// __m256i x
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


// функция транспонирования, в w256 предварительно подготовленные блоки
// функция работает как в прямую так и в обратную конвертацию, т.е. p32 может указывать на тип T, т.е. просто переопределен указатель
void ConvertBitslice_32x32(const __m256i w256_[4], uint32_t* p32, const uint32_t offset)
{
	_ALIGN(32) const __m256i c1 = _mm256_set1_epi64x(0xAA55AA55AA55AA55LL);
	_ALIGN(32) const __m256i c2 = _mm256_set1_epi64x(0x00AA00AA00AA00AALL);
	_ALIGN(32) const __m256i c3 = _mm256_set1_epi64x(0xCCCC3333CCCC3333LL);
	_ALIGN(32) const __m256i c4 = _mm256_set1_epi64x(0x0000CCCC0000CCCCLL);
	_ALIGN(32) const __m256i c5 = _mm256_set1_epi64x(0xF0F0F0F00F0F0F0FLL);
	_ALIGN(32) const __m256i c6 = _mm256_set1_epi64x(0x00000000F0F0F0F0LL);
	_ALIGN(32) const __m256i perm = _mm256_set_epi8(15, 11, 7, 3, 14, 10, 6, 2, 13, 9, 5, 1, 12, 8, 4, 0, 15, 11, 7, 3, 14, 10, 6, 2, 13, 9, 5, 1, 12, 8, 4, 0);
	_ALIGN(32) const __m256i perm8x32 = _mm256_set_epi32(7, 3, 6, 2, 5, 1, 4, 0);
	_ALIGN(32) __m256i w256[4], t1, t2, t3;

	w256[0] = _mm256_shuffle_epi8(w256_[0], perm); // собираю по 2 байта
	w256[0] = _mm256_permutevar8x32_epi32(w256[0], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
	w256[1] = _mm256_shuffle_epi8(w256_[1], perm); // собираю по 2 байта
	w256[1] = _mm256_permutevar8x32_epi32(w256[1], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
	w256[2] = _mm256_shuffle_epi8(w256_[2], perm); // собираю по 2 байта
	w256[2] = _mm256_permutevar8x32_epi32(w256[2], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
	w256[3] = _mm256_shuffle_epi8(w256_[3], perm); // собираю по 2 байта
	w256[3] = _mm256_permutevar8x32_epi32(w256[3], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе

	transpose8x8_4_macros(w256[0]);
	transpose8x8_4_macros(w256[1]);
	transpose8x8_4_macros(w256[2]);
	transpose8x8_4_macros(w256[3]);
	
	t1 = _mm256_unpacklo_epi8(w256[0], w256[1]); //t1 содержит word из битов в младших 64-х битовых половинках
	t2 = _mm256_unpacklo_epi8(w256[2], w256[3]);
	t3 = _mm256_unpacklo_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
	p32[0 * offset] = _mm256_extract_epi32(t3, 0);
	p32[1 * offset] = _mm256_extract_epi32(t3, 1);
	p32[2 * offset] = _mm256_extract_epi32(t3, 2);
	p32[3 * offset] = _mm256_extract_epi32(t3, 3);
	p32[16 * offset] = _mm256_extract_epi32(t3, 4);
	p32[17 * offset] = _mm256_extract_epi32(t3, 5);
	p32[18 * offset] = _mm256_extract_epi32(t3, 6);
	p32[19 * offset] = _mm256_extract_epi32(t3, 7);
	t3 = _mm256_unpackhi_epi16(t1, t2); // t3 содержит dword из word в старших половинах каждой 128-битовых линий
	p32[4 * offset] = _mm256_extract_epi32(t3, 0);
	p32[5 * offset] = _mm256_extract_epi32(t3, 1);
	p32[6 * offset] = _mm256_extract_epi32(t3, 2);
	p32[7 * offset] = _mm256_extract_epi32(t3, 3);
	p32[20 * offset] = _mm256_extract_epi32(t3, 4);
	p32[21 * offset] = _mm256_extract_epi32(t3, 5);
	p32[22 * offset] = _mm256_extract_epi32(t3, 6);
	p32[23 * offset] = _mm256_extract_epi32(t3, 7);
	t1 = _mm256_unpackhi_epi8(w256[0], w256[1]); //t1 содержит word из битов в младших 64-х битовых половинках
	t2 = _mm256_unpackhi_epi8(w256[2], w256[3]);
	t3 = _mm256_unpacklo_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
	p32[8 * offset] = _mm256_extract_epi32(t3, 0);
	p32[9 * offset] = _mm256_extract_epi32(t3, 1);
	p32[10 * offset] = _mm256_extract_epi32(t3, 2);
	p32[11 * offset] = _mm256_extract_epi32(t3, 3);
	p32[24 * offset] = _mm256_extract_epi32(t3, 4);
	p32[25 * offset] = _mm256_extract_epi32(t3, 5);
	p32[26 * offset] = _mm256_extract_epi32(t3, 6);
	p32[27 * offset] = _mm256_extract_epi32(t3, 7);
	t3 = _mm256_unpackhi_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
	p32[12 * offset] = _mm256_extract_epi32(t3, 0);
	p32[13 * offset] = _mm256_extract_epi32(t3, 1);
	p32[14 * offset] = _mm256_extract_epi32(t3, 2);
	p32[15 * offset] = _mm256_extract_epi32(t3, 3);
	p32[28 * offset] = _mm256_extract_epi32(t3, 4);
	p32[29 * offset] = _mm256_extract_epi32(t3, 5);
	p32[30 * offset] = _mm256_extract_epi32(t3, 6);
	p32[31 * offset] = _mm256_extract_epi32(t3, 7);
}


#else
//
#endif
