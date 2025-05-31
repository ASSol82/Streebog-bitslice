

#include "Streebog_convert.h"
#include "Convert_bitslice.h"
#include "Streebog_bitslice.h"
#include "LogicalOperations.h"


#define transpose8x8_macros(x) \
x = (x & 0xAA55AA55AA55AA55LL) | ((x & 0x00AA00AA00AA00AALL) << 7) | ((x >> 7) & 0x00AA00AA00AA00AALL);\
x = (x & 0xCCCC3333CCCC3333LL) | ((x & 0x0000CCCC0000CCCCLL) << 14) | ((x >> 14) & 0x0000CCCC0000CCCCLL);\
x = (x & 0xF0F0F0F00F0F0F0FLL) | ((x & 0x00000000F0F0F0F0LL) << 28) | ((x >> 28) & 0x00000000F0F0F0F0LL);


// num - позиция в bitslice векторах dst[0],dst[1],...,dst[7] в которую записывается байт src
void SetByteInBitSliceSSE(const uint32_t num, const uint8_t src, T *dst)
{
	SetBit_T_macros(dst[0], num, (src >> 0) & 1);
	SetBit_T_macros(dst[1], num, (src >> 1) & 1);
	SetBit_T_macros(dst[2], num, (src >> 2) & 1);
	SetBit_T_macros(dst[3], num, (src >> 3) & 1);
	SetBit_T_macros(dst[4], num, (src >> 4) & 1);
	SetBit_T_macros(dst[5], num, (src >> 5) & 1);
	SetBit_T_macros(dst[6], num, (src >> 6) & 1);
	SetBit_T_macros(dst[7], num, (src >> 7) & 1);
}


// в dst битах num будет установлен вектор 512 бит из src
void SetArrayByteToBitSlice(int num, const uint8_t src[64], T* dst)
{
	for (int i = 0; i < 64; ++i)
	{
		SetByteInBitSliceSSE(num, src[i], (dst + i * 8));
	}
}


#if MaxCountMessage==256


<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 6980916 (CTCrypt 2025 20250601_1)
/*
// __m256i x
//#define transpose8x8_4_macros(x) { \
//x = _OR(_OR(_AND(x, c1), _SHIFTL64(_AND(x, c2), 7)), _AND(_SHIFTR64(x, 7), c2)); \
//x = _OR(_OR(_AND(x, c3), _SHIFTL64(_AND(x, c4), 14)), _AND(_SHIFTR64(x, 14), c4)); \
//x = _OR(_OR(_AND(x, c5), _SHIFTL64(_AND(x, c6), 28)), _AND(_SHIFTR64(x, 28), c6)); }
//
//
//#define from_8x32_to_256(w256,p32,p0,p1,p2,p3,p4,p5,p6,p7) w256 = _mm256_set_epi64x( \
//		(uint64_t)p32[p6]	|	(uint64_t)p32[p7]<<32, \
//		(uint64_t)p32[p4]	|	(uint64_t)p32[p5]<<32, \
//		(uint64_t)p32[p2]	|	(uint64_t)p32[p3]<<32, \
//		(uint64_t)p32[p0]	|	(uint64_t)p32[p1]<<32);
//
//
//#define value_8x32_to_256(w256,v0,v1,v2,v3,v4,v5,v6,v7) w256 = _mm256_set_epi64x( \
//		(uint64_t)v6|(uint64_t)v7<<32, (uint64_t)v4|(uint64_t)v5<<32, (uint64_t)v2|(uint64_t)v3<<32,(uint64_t)v0|(uint64_t)v1<<32);
*/


=======
>>>>>>> 5d91de8 (CTCrypt 2025 20250601_1)
// функция транспонирования, в src предварительно подготовленные блоки
//void ConvertToBitSlice_32x32(__m256i w256[4], uint32_t* p32)
//{
//	_ALIGN(32) const __m256i c1 = _mm256_set1_epi64x(0xAA55AA55AA55AA55LL);
//	_ALIGN(32) const __m256i c2 = _mm256_set1_epi64x(0x00AA00AA00AA00AALL);
//	_ALIGN(32) const __m256i c3 = _mm256_set1_epi64x(0xCCCC3333CCCC3333LL);
//	_ALIGN(32) const __m256i c4 = _mm256_set1_epi64x(0x0000CCCC0000CCCCLL);
//	_ALIGN(32) const __m256i c5 = _mm256_set1_epi64x(0xF0F0F0F00F0F0F0FLL);
//	_ALIGN(32) const __m256i c6 = _mm256_set1_epi64x(0x00000000F0F0F0F0LL);
//
//	_ALIGN(32) const __m256i perm = _mm256_set_epi8(15, 14, 11, 10, 7, 6, 3, 2, 13, 12, 9, 8, 5, 4, 1, 0, 15, 14, 11, 10, 7, 6, 3, 2, 13, 12, 9, 8, 5, 4, 1, 0);
//	_ALIGN(32) const __m256i perm8x32 = _mm256_set_epi32(7, 6, 3, 2, 5, 4, 1, 0);
//	_ALIGN(32) const __m256i perm_final = _mm256_set_epi8(15, 13, 11, 9, 7, 5, 3, 1, 14, 12, 10, 8, 6, 4, 2, 0, 15, 13, 11, 9, 7, 5, 3, 1, 14, 12, 10, 8, 6, 4, 2, 0);
//
//	w256[0] = _mm256_shuffle_epi8(w256[0], perm); // собираю по 2 байта
//	w256[0] = _mm256_permutevar8x32_epi32(w256[0], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
//	w256[0] = _mm256_shuffle_epi8(w256[0], perm_final); // после этой перестановки - байты 1..8 вектора w256 будут являться первыми байтами сообщений 1..8, байты 9..16 будут являться вторыми байтами сообщений 1..8, байты 17..24 будут являться третьими байтами сообщений 1..8, ...
//	w256[1] = _mm256_shuffle_epi8(w256[1], perm); // собираю по 2 байта
//	w256[1] = _mm256_permutevar8x32_epi32(w256[1], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
//	w256[1] = _mm256_shuffle_epi8(w256[1], perm_final); // после этой перестановки - байты 1..8 вектора w256 будут являться первыми байтами сообщений 1..8, байты 9..16 будут являться вторыми байтами сообщений 1..8, байты 17..24 будут являться третьими байтами сообщений 1..8, ...
//	w256[2] = _mm256_shuffle_epi8(w256[2], perm); // собираю по 2 байта
//	w256[2] = _mm256_permutevar8x32_epi32(w256[2], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
//	w256[2] = _mm256_shuffle_epi8(w256[2], perm_final); // после этой перестановки - байты 1..8 вектора w256 будут являться первыми байтами сообщений 1..8, байты 9..16 будут являться вторыми байтами сообщений 1..8, байты 17..24 будут являться третьими байтами сообщений 1..8, ...
//	w256[3] = _mm256_shuffle_epi8(w256[3], perm); // собираю по 2 байта
//	w256[3] = _mm256_permutevar8x32_epi32(w256[3], perm8x32); // делаю перестановку среди 32-х битовых переменных, чтобы байты сообщений 1..4 оказались в левом 128-битовом векторе, а байты сообщений 5..8 в правом 128-битовом векторе
//	w256[3] = _mm256_shuffle_epi8(w256[3], perm_final); // после этой перестановки - байты 1..8 вектора w256 будут являться первыми байтами сообщений 1..8, байты 9..16 будут являться вторыми байтами сообщений 1..8, байты 17..24 будут являться третьими байтами сообщений 1..8, ...
//
//	transpose8x8_4_macros(w256[0]);
//	transpose8x8_4_macros(w256[1]);
//	transpose8x8_4_macros(w256[2]);
//	transpose8x8_4_macros(w256[3]);
//
//	_ALIGN(32) __m256i t1, t2, t3;
//	t1 = _mm256_unpacklo_epi8(w256[0], w256[1]); //t1 содержит word из битов в младших 64-х битовых половинках
//	t2 = _mm256_unpacklo_epi8(w256[2], w256[3]);
//	t3 = _mm256_unpacklo_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
//	p32[0 * 8] = _mm256_extract_epi32(t3, 0);
//	p32[1 * 8] = _mm256_extract_epi32(t3, 1);
//	p32[2 * 8] = _mm256_extract_epi32(t3, 2);
//	p32[3 * 8] = _mm256_extract_epi32(t3, 3);
//	p32[16 * 8] = _mm256_extract_epi32(t3, 4);
//	p32[17 * 8] = _mm256_extract_epi32(t3, 5);
//	p32[18 * 8] = _mm256_extract_epi32(t3, 6);
//	p32[19 * 8] = _mm256_extract_epi32(t3, 7);
//	t3 = _mm256_unpackhi_epi16(t1, t2); // t3 содержит dword из word в старших половинах каждой 128-битовых линий
//	p32[4 * 8] = _mm256_extract_epi32(t3, 0);
//	p32[5 * 8] = _mm256_extract_epi32(t3, 1);
//	p32[6 * 8] = _mm256_extract_epi32(t3, 2);
//	p32[7 * 8] = _mm256_extract_epi32(t3, 3);
//	p32[20 * 8] = _mm256_extract_epi32(t3, 4);
//	p32[21 * 8] = _mm256_extract_epi32(t3, 5);
//	p32[22 * 8] = _mm256_extract_epi32(t3, 6);
//	p32[23 * 8] = _mm256_extract_epi32(t3, 7);
//	t1 = _mm256_unpackhi_epi8(w256[0], w256[1]); //t1 содержит word из битов в младших 64-х битовых половинках
//	t2 = _mm256_unpackhi_epi8(w256[2], w256[3]);
//	t3 = _mm256_unpacklo_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
//	p32[8 * 8] = _mm256_extract_epi32(t3, 0);
//	p32[9 * 8] = _mm256_extract_epi32(t3, 1);
//	p32[10 * 8] = _mm256_extract_epi32(t3, 2);
//	p32[11 * 8] = _mm256_extract_epi32(t3, 3);
//	p32[24 * 8] = _mm256_extract_epi32(t3, 4);
//	p32[25 * 8] = _mm256_extract_epi32(t3, 5);
//	p32[26 * 8] = _mm256_extract_epi32(t3, 6);
//	p32[27 * 8] = _mm256_extract_epi32(t3, 7);
//	t3 = _mm256_unpackhi_epi16(t1, t2); // t3 содержит dword из word в младших половинах 128-битовых линий
//	p32[12 * 8] = _mm256_extract_epi32(t3, 0);
//	p32[13 * 8] = _mm256_extract_epi32(t3, 1);
//	p32[14 * 8] = _mm256_extract_epi32(t3, 2);
//	p32[15 * 8] = _mm256_extract_epi32(t3, 3);
//	p32[28 * 8] = _mm256_extract_epi32(t3, 4);
//	p32[29 * 8] = _mm256_extract_epi32(t3, 5);
//	p32[30 * 8] = _mm256_extract_epi32(t3, 6);
//	p32[31 * 8] = _mm256_extract_epi32(t3, 7);
//}


//макросы для конвертации на 2-м этапе Стрибог, некоторые макросы используются и на 3-м этапе
#define GetPtr8(i,pos) (msg[i].M + (pos))
#define GetU8(i,pos) (*GetPtr8(i,pos))
#define GetPtr32(i,pos) ((uint32_t*)(msg[i].M + (pos))) // pos определяет смещение в байтах, т.е. также как GetPtr8
#define GetU32(i,pos) (*GetPtr32(i,pos))
//условие (i) < countMessage) можно не добавлять, т.к. на 2-м этапе в векторе v биты установлены на актуальных сообщениях
//#define Ins32_Stage2(i) (GetBit_T_macros(v,i) && ((i)<countMessage) ? GetU32(i,cb+n) : 0) // T v здесь биты установлены на сообщениях для которых требуется этап 2
#define Ins32_Stage2(i) (GetBit_T_macros(v,i) ? GetU32(i,cb+n) : 0) // T v здесь биты установлены на сообщениях для которых требуется этап 2
void ConvertMsgToBitSlice_Stage2(const struct message_context* msg, const uint32_t countMessage, const T v, const uint64_t cb, T* dst)
{
	for (uint32_t j = 0; j < countMessage; j += 32)
	{
		uint32_t* p = ((uint32_t*)dst) + (j >> 5);
		for (uint32_t n = 0; n < 64; n += 4)
		{
			__m256i w256[4];
			value_8x32_to_256(w256[0], Ins32_Stage2(j), Ins32_Stage2(j + 1), Ins32_Stage2(j + 2), Ins32_Stage2(j + 3), Ins32_Stage2(j + 4), Ins32_Stage2(j + 5), Ins32_Stage2(j + 6), Ins32_Stage2(j + 7));
			value_8x32_to_256(w256[1], Ins32_Stage2(j + 8), Ins32_Stage2(j + 9), Ins32_Stage2(j + 10), Ins32_Stage2(j + 11), Ins32_Stage2(j + 12), Ins32_Stage2(j + 13), Ins32_Stage2(j + 14), Ins32_Stage2(j + 15));
			value_8x32_to_256(w256[2], Ins32_Stage2(j + 16), Ins32_Stage2(j + 17), Ins32_Stage2(j + 18), Ins32_Stage2(j + 19), Ins32_Stage2(j + 20), Ins32_Stage2(j + 21), Ins32_Stage2(j + 22), Ins32_Stage2(j + 23));
			value_8x32_to_256(w256[3], Ins32_Stage2(j + 24), Ins32_Stage2(j + 25), Ins32_Stage2(j + 26), Ins32_Stage2(j + 27), Ins32_Stage2(j + 28), Ins32_Stage2(j + 29), Ins32_Stage2(j + 30), Ins32_Stage2(j + 31));
			ConvertBitslice_32x32(w256, p, 8);
			p += 256;
		}
	}
}


//макросы для 3-го этапа Стрибог
#define CompletedBytes(i) ((msg[i].lengthInBits & ~0x1FFULL) >> 3) // обработано байт сообщения j
#define CB(i) CompletedBytes(i)
#define RemainedBytes(i) ((msg[i].lengthInBits & 0x1FFULL) >> 3) // осталось полных байт в сообщении j, это значение 0..63, и не может равняться 64, т.к. иначе нужно 2-й этап для этого сообщения
#define RB(i) RemainedBytes(i)
#define RemainedBits(i) (msg[i].lengthInBits & 7)
// ниже pos является значением от 0..63, т.к. это лишь для 3-го раунда
#define GetU8_Stage3(i,pos) ( \
			(pos) > RB(i) ? 0 : (pos) < RB(i) ? GetU8(i,CB(i)+(pos)) : \
			(GetU8(i,CB(i)+(pos)) & (0xFFU>>(8-RemainedBits(i)))) | (0x1U<<(RemainedBits(i))) \
		) // формируется корректное 8-битовое значение для 3-го раунда
#define GetU32_Stage3_(i,pos) ((i)<countMessage?(pos)+4>RB(i)?((uint32_t)GetU8_Stage3(i,pos) | (uint32_t)GetU8_Stage3(i,pos+1)<<8 | \
							(uint32_t)GetU8_Stage3(i,pos+2)<<16 | (uint32_t)GetU8_Stage3(i,pos+3)<<24):GetU32(i,CB(i)+pos):0)
#define GetU32_Stage3(i) GetU32_Stage3_(i,n)
void ConvertMsgToBitSlice_Stage3(const struct message_context* msg, const uint32_t countMessage, T* dst)
{
	for (uint32_t j = 0; j < countMessage; j += 32)
	{
		uint32_t* p = ((uint32_t*)dst) + (j >> 5);
		for (uint32_t n = 0; n < 64; n += 4)
		{
			__m256i w256[4];
			value_8x32_to_256(w256[0], GetU32_Stage3(j), GetU32_Stage3(j + 1), GetU32_Stage3(j + 2), GetU32_Stage3(j + 3), GetU32_Stage3(j + 4), GetU32_Stage3(j + 5), GetU32_Stage3(j + 6), GetU32_Stage3(j + 7));
			value_8x32_to_256(w256[1], GetU32_Stage3(j + 8), GetU32_Stage3(j + 9), GetU32_Stage3(j + 10), GetU32_Stage3(j + 11), GetU32_Stage3(j + 12), GetU32_Stage3(j + 13), GetU32_Stage3(j + 14), GetU32_Stage3(j + 15));
			value_8x32_to_256(w256[2], GetU32_Stage3(j + 16), GetU32_Stage3(j + 17), GetU32_Stage3(j + 18), GetU32_Stage3(j + 19), GetU32_Stage3(j + 20), GetU32_Stage3(j + 21), GetU32_Stage3(j + 22), GetU32_Stage3(j + 23));
			value_8x32_to_256(w256[3], GetU32_Stage3(j + 24), GetU32_Stage3(j + 25), GetU32_Stage3(j + 26), GetU32_Stage3(j + 27), GetU32_Stage3(j + 28), GetU32_Stage3(j + 29), GetU32_Stage3(j + 30), GetU32_Stage3(j + 31));
			ConvertBitslice_32x32(w256, p, 8);
			p += 256;
		}
	}
}


// 20250531
void ConvertHashFromBitSlice_all(const T h[512], const uint32_t countMessage, const uint32_t hashLength, uint8_t(*hash_value)[64])
{
	const uint32_t shift = (hashLength == 256 ? 256 : 0);
	const uint32_t countByte = (hashLength == 256 ? 32 : 64); // количество байт в хеш-значении

	for (uint32_t j = 0; j < countMessage; j += 32) // обрабатываем результат по порциям в 32 хеш-значений
	{
		uint32_t* p_src32 = ((uint32_t*)h) + ((sizeof(T) * shift) >> 2) + (j >> 5); // указатель на начало массива T h[512] смещенного по номеру сообщения кратного 32 и смещенного в зависимости от длины хеш-значения
		uint32_t* p_dst32 = (uint32_t*)(hash_value + j);
		for (uint32_t nb = 0; nb < countByte; nb += 4) //по номерам байтов хеш-значений
		{
			_ALIGN(32) __m256i w256[4];
			from_8x32_to_256(w256[0],p_src32,0,8,16,24,32,40,48,56);
			from_8x32_to_256(w256[1],p_src32,64,72,80,88,96,104,112,120);
			from_8x32_to_256(w256[2],p_src32,128,136,144,152,160,168,176,184);
			from_8x32_to_256(w256[3],p_src32,192,200,208,216,224,232,240,248);

			ConvertBitslice_32x32(w256, p_dst32, 16);
			
			p_src32 += (sizeof(T) << 3); // переходим к следующей четверке байтов среди bitslice векторов, поэтому смещаемся на 32 вектора T
			p_dst32 += 1;
		}
	}
}


#else //!!! MaxCountMessage!=256


void ConvertMsgToBitSlice_Stage2(const struct message_context* msg, const uint32_t countMessage, const T v2, const uint64_t cb, T* dst)
{
	for (int j = 0; j < (countMessage & (~7ul)); j += 8)
	{
		uint8_t* p = ((uint8_t*)dst) + (j >> 3); // указатель на начало массива T m[512] смещенного по номеру сообщения кратного 8, который готовится для работы bitslice
		const uint8_t b = GetByte_T_macros(v2, (j >> 3));
		for (uint32_t numByte = 0; numByte < 64; ++numByte)
		{
			uint64_t w = (b & 1 ? (uint64_t)msg[j].M[cb + numByte] : 0) |
				((b >> 1) & 1 ? (((uint64_t)msg[j + 1].M[cb + numByte]) << 8) : 0) |
				((b >> 2) & 1 ? (((uint64_t)msg[j + 2].M[cb + numByte]) << 16) : 0) |
				((b >> 3) & 1 ? (((uint64_t)msg[j + 3].M[cb + numByte]) << 24) : 0) |
				((b >> 4) & 1 ? (((uint64_t)msg[j + 4].M[cb + numByte]) << 32) : 0) |
				((b >> 5) & 1 ? (((uint64_t)msg[j + 5].M[cb + numByte]) << 40) : 0) |
				((b >> 6) & 1 ? (((uint64_t)msg[j + 6].M[cb + numByte]) << 48) : 0) |
				((b >> 7) & 1 ? (((uint64_t)msg[j + 7].M[cb + numByte]) << 56) : 0);

			transpose8x8_macros(w);

			p[0] = w; p[sizeof(T)] = (w >> 8); p[sizeof(T) * 2] = (w >> 16); p[sizeof(T) * 3] = (w >> 24);
			p[sizeof(T) * 4] = (w >> 32); p[sizeof(T) * 5] = (w >> 40); p[sizeof(T) * 6] = (w >> 48); p[sizeof(T) * 7] = (w >> 56);

			p += (sizeof(T) << 3);
		}
	}
	for (uint32_t j = (countMessage & ~7ul); j < countMessage; ++j) // имеется остаток при делении на 8, значит надо доконвертировать биты сообщения в вектора T для bitslice
	{
		if (GetBit_T_macros(v2, j)) // если бит на данной позиции, значит сообщение длинное, поэтому считываем в m
		{
			SetArrayByteToBitSlice(j, &msg[j].M[cb], dst);
		}
	}
}


void ConvertMsgToBitSlice_Stage3(const struct message_context* msg, const uint32_t countMessage, T* dst)
{
	for (uint32_t j = 0; j < countMessage; j += 8)
	{
		uint8_t* p = ((uint8_t*)dst) + (j >> 3); // указатель на начало массива T m[512] смещенного по номеру сообщения кратного 8, который готовится для работы bitslice
		for (uint32_t numByte = 0; numByte < 64; ++numByte)
		{
			uint64_t w = 0;
			for (uint32_t k = 0; k < (j + 8 <= countMessage ? 8 : (countMessage & 7)); ++k)
			{
				const uint64_t cb = ((msg[j + k].lengthInBits & ~((uint64_t)0x1FF)) >> 3); // обработано байт сообщения j
				// ((msg[j].lengthInBits & ((uint64_t)0x1FF)) >> 3) - осталость полных байт в сообщении j
				w |= (numByte < ((msg[j + k].lengthInBits& ((uint64_t)0x1FF)) >> 3) ? (((uint64_t)msg[j + k].M[cb + numByte]) << (k * 8)) : 0);
			}
			transpose8x8_macros(w);
			p[0] = w; p[sizeof(T)] = (w >> 8); p[sizeof(T) * 2] = (w >> 16); p[sizeof(T) * 3] = (w >> 24);
			p[sizeof(T) * 4] = (w >> 32); p[sizeof(T) * 5] = (w >> 40); p[sizeof(T) * 6] = (w >> 48); p[sizeof(T) * 7] = (w >> 56);

			p += (sizeof(T) << 3);
		}
	}
	for (uint32_t j = 0; j < countMessage; ++j)
	{
		const uint64_t cb = msg[j].lengthInBits >> 3; // полных байт сообщения j
		for (uint32_t i = 0; i < (msg[j].lengthInBits & (uint64_t)7); ++i) // хвостик оставшихся бит сообщения
		{
			SetBit_T_macros(dst[(msg[j].lengthInBits & (uint64_t)0x1F8) + i], j, GetBit(msg[j].M, (cb << 3) + i));
		}
		SetBit_T_macros(dst[(msg[j].lengthInBits & (uint64_t)0x1FF)], j, 1); /* после сообщения должна дописываться единица, как в стандарте */
	}
}


void ConvertHashFromBitSlice_all(const T h[512], const uint32_t countMessage, const uint32_t hashLength, uint8_t(*hash_value)[64])
{
	const uint32_t shift = (hashLength == 256 ? 256 : 0);
	const uint32_t countByte = (hashLength == 256 ? 32 : 64); // количество байт в хеш-значении
	for (uint32_t j = 0; j < countMessage; j += 8) // обрабатываем результат по порциям в 8 хеш-значений
	{
		uint8_t* p = ((uint8_t*)h) + (sizeof(T) * shift) + (j >> 3); // указатель на начало массива T h[512] смещенного по номеру сообщения кратного 8 и смещенного в зависимости от длины хеш-значения
		for (uint32_t i = 0; i < countByte; ++i)
		{
			uint64_t w = (uint64_t)p[0] | (uint64_t)p[sizeof(T)] << 8 |
				(uint64_t)p[sizeof(T) * 2] << 16 | (uint64_t)p[sizeof(T) * 3] << 24 |
				(uint64_t)p[sizeof(T) * 4] << 32 | (uint64_t)p[sizeof(T) * 5] << 40 |
				(uint64_t)p[sizeof(T) * 6] << 48 | (uint64_t)p[sizeof(T) * 7] << 56;
			transpose8x8_macros(w);
			for (uint32_t k = 0; k < (j + 8 <= countMessage ? 8 : (countMessage & 7)); ++k)
			{
				hash_value[j + k][i] = (w >> (k << 3));
			}
			p += (sizeof(T) << 3); // переходим к следующему байту среди bitslice векторов, поэтому смещаемся на 8 векторов T
		}
	}
}


#endif
