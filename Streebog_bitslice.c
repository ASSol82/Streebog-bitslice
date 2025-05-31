

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "LPS_bitslice.h"
#include "Streebog_bitslice.h"
#include "Streebog_convert.h"
#include "LogicalOperations.h"
#include "Functions.h"


// можно раскомментировать этот участок
static const uint32_t constC[12][8][2] = {
{ { 0xF2A64507, 0xDD806559 }, { 0xCC744D23, 0x05767436 }, { 0xA460D315, 0xA2422A08 }, { 0x92676901, 0x4B7CE091 }, { 0x7585C4FC, 0x714EB88D }, { 0x2E45D016, 0x2F6A7643 }, { 0xC0657C1F, 0xEBCB2F81 }, { 0x1ECADAE9, 0xB1085BDA } },
{ { 0x21B19BB7, 0xE6790470 }, { 0xD7CBCD56, 0x55DDA21B }, { 0xDB0AA7CA, 0x5CB561C2 }, { 0x12D69958, 0x9AB5176B }, { 0x16B50131, 0x61D55E0F }, { 0x0A232B98, 0xF3FEEA72 }, { 0x0F70B5D7, 0x4FE39D46 }, { 0xA99D2F1A, 0x6FA3B58A } },
{ { 0x0ABA0AB2, 0x991E96F5 }, { 0x867ADB31, 0xC2B6F443 }, { 0x6062DB09, 0xC1C93A37 }, { 0x90359EB1, 0xD3E20FE4 }, { 0xB1297B7B, 0xF2EA7514 }, { 0x529C1F8B, 0x06F15E5F }, { 0x6A3D8435, 0x0A39FC28 }, { 0x2BCE2FC7, 0xF574DCAC } },
{ { 0x84E3D12E, 0x220CBEBC }, { 0x93E837F1, 0x3453EAA1 }, { 0x935203BE, 0xD8B71333 }, { 0xED03D675, 0xA9D72C82 }, { 0x685E353F, 0x9D721CAD }, { 0x335C3C7D, 0x488E857E }, { 0x5D71E4DD, 0xF948E1A0 }, { 0xE81566D2, 0xEF1FDFB3 } },
{ { 0x7C6CFE57, 0x601758FD }, { 0xA9EA63F5, 0x7A56A27E }, { 0x23271A16, 0xDFFF00B7 }, { 0x253AF5A3, 0xBFCD1747 }, { 0x800FFFBD, 0x359E35D7 }, { 0x1686104A, 0x7F151C1F }, { 0x6CA92363, 0x9A3F410C }, { 0xAD474799, 0x4BEA6BAC } },
{ { 0x46647D6E, 0xFA68407A }, { 0x36904F35, 0xBF71C572 }, { 0xC2BEC6B6, 0x0AF21F66 }, { 0x1C9AB7B4, 0xCFFAA6B7 }, { 0x9AF08EC6, 0x187F9AB4 }, { 0x5142A46C, 0x2D66C4F9 }, { 0x7A3039C0, 0x6FA4C33B }, { 0x1D3AD3D9, 0xAE4FAEAE } },
{ { 0x3A14D493, 0x8886564D }, { 0xA23C4AF3, 0x3517454C }, { 0x284A0504, 0x06476983 }, { 0x2D822C37, 0x0992ABC5 }, { 0x197A93C9, 0xD3473E33 }, { 0xE6BF87C9, 0x399EC6C7 }, { 0xBF240954, 0x51AC86FE }, { 0xEEAAC5EC, 0xF4C70E16 } },
{ { 0xBF02E71E, 0xA47F0DD4 }, { 0x5951A8D9, 0x36ACC235 }, { 0xD1A5C42F, 0x69D18D2B }, { 0x929B0690, 0xF4892BCB }, { 0x4DDBC49A, 0x89B4443B }, { 0x9C36DE1E, 0x4EB7F871 }, { 0x0C6E4141, 0x03E7AA02 }, { 0x4D93C9A7, 0x9B1F5B42 } },
{ { 0x83235ADB, 0x72614451 }, { 0xCB1F2A60, 0x0E38DC92 }, { 0xA6079C54, 0x7B2B8A9A }, { 0xDBB2CEB1, 0x800A440B }, { 0xE00D0984, 0x3CD955B7 }, { 0x25894224, 0x3A7D3A1B }, { 0xEC165FDE, 0x944C9AD8 }, { 0x1631229B, 0x378F5A54 } },
{ { 0x98459CED, 0x74B4C7FB }, { 0x153BB6C3, 0x3698FAD1 }, { 0x3B7652F4, 0x7A1E6C30 }, { 0xAF69334B, 0x9FE76702 }, { 0x1B336103, 0x1FFFE18A }, { 0xFF8A78DB, 0x8941E71C }, { 0xB2E4F3F3, 0x382AE548 }, { 0x80056F52, 0xABBEDEA6 } },
{ { 0x81F32D1B, 0x6BCAA4CD }, { 0xC06FD85D, 0xDEA2594A }, { 0x7D476E98, 0xEFBACD1D }, { 0xEA48B9CA, 0x8A1D71EF }, { 0x14846679, 0x20018021 }, { 0xEBAB0761, 0xD8FA6BBB }, { 0x635AFE94, 0x3002C6CD }, { 0xEFC889FB, 0x7BCD9ED0 } },
{ { 0xF11BD720, 0x48BC924A }, { 0xD9B21B99, 0xFAF417D5 }, { 0x88E12852, 0xE71DA4AA }, { 0x1891CC86, 0x5D80EF9D }, { 0x30219F9B, 0xF82012D4 }, { 0xBCDF1D77, 0xCDA43C32 }, { 0x0449B17A, 0xD21380B0 }, { 0xF11631BA, 0x378EE767 } } };


#define Kx(n) K[n] = _XOR(K[n], x[(c >> ((n) & 0x1F)) & 1]);
#define bmK(n) b[n] = _XOR(m[n], K[n]);
#define bbK(n) b[n] = _XOR(b[n], K[n]);
#define Kb(n) K[n] = _XOR(K[n], b[n]);


void functionE_bitslice(T* K, const T* m)
{
	int i = 0, j;
	_ALIGN(MALLOCALIGN) const T x[2] = { _ZERORIGHT, _NOT(_ZERORIGHT) };
	T *b = K + 512;
	T *tmp = b + 512; // 20241014

	for (j = 0; j < 512; j+=8)
	{
		const uint32_t c = constC[i][(j) >> 6][((j) >> 5) & 1];
		bmK(j) bmK(j+1) bmK(j+2) bmK(j+3) bmK(j+4) bmK(j+5) bmK(j+6) bmK(j+7)
		Kx(j) Kx(j+1) Kx(j+2) Kx(j+3) Kx(j+4) Kx(j+5) Kx(j+6) Kx(j+7)
	}
	LPS_bitslice_SSE(b, tmp);
	LPS_bitslice_SSE(K, tmp);

	for (i = 1; i <= 11; i++)
	{
		for (j = 0; j < 512; j += 8)
		{
			const uint32_t c = constC[i][(j) >> 6][((j) >> 5) & 1];
			bbK(j) bbK(j+1) bbK(j+2) bbK(j+3) bbK(j+4) bbK(j+5) bbK(j+6) bbK(j+7)
			Kx(j) Kx(j+1) Kx(j+2) Kx(j+3) Kx(j+4) Kx(j+5) Kx(j+6) Kx(j+7)		
		}
		LPS_bitslice_SSE(b, tmp); /* очередное вычисление в формуле E(K,m) */
		LPS_bitslice_SSE(K, tmp); /* сформировали очередной Ki описание пункт 7 формула 10 */
	}

	for (j = 0; j < 512; j+=8)
	{
		Kb(j) Kb(j+1) Kb(j+2) Kb(j+3) Kb(j+4) Kb(j+5) Kb(j+6) Kb(j+7)		
	}
}


// маска задает позиции, которые требуется изменить
void functionG_bitslice_mask(const T *N, T *h, const T *m, const T mask_)
{
	int i;
	T* t = h + 512;
	T *tmp = t + 512;
	//T* t = aligned_malloc(sizeof(T) * 512*2);
	for (i = 0; i < 512; ++i) t[i] = _XOR(h[i], N[i]); //t[i] = h[i] ^ N[i];
	LPS_bitslice_SSE(t, tmp);
	functionE_bitslice(t, m);
	for (i = 0; i < 512; ++i) h[i] = _XOR(_AND(h[i], _NOT(mask_)), _AND(_XOR(h[i], _XOR(t[i], m[i])), mask_)); // h[i] ^= t[i] ^ m[i];
	//aligned_free(t);
}


void functionG_bitslice(const T *N, T *h, const T *m)
{
	int i;
	T* t = h + 512;
	T *tmp = t + 512;
	//T* t = aligned_malloc(sizeof(T) * 512*2);
	//for (i = 0; i < 512; ++i) t[i] = _XOR(h[i], N[i]); //t[i] = h[i] ^ N[i];
	for (i = 0; i < 512; ++i) t[i] = _XOR(h[i], N[i]);
	LPS_bitslice_SSE(t, tmp);
	functionE_bitslice(t, m);
	//for (i = 0; i < 512; ++i) h[i] = _XOR(h[i], _XOR(t[i], m[i])); // h[i] ^= t[i] ^ m[i];
	for (i = 0; i < 512; ++i) h[i] = _XOR(h[i], _XOR(t[i], m[i]));
	//aligned_free(t);
}


// было во входном параметре h[512], но выскакивало предупреждение от компилятора в виде выхода за диапазон, т.к. используется T* t = h + 512
// заменил на h[1024] перестало выскакивать предупреждение, потом заменил вообще на T *h и тоже нет предупреждения
// можно так оставить, т.к. функция void functionG_Zero_bitslice(T *h, const T m[512]) является внутренней функцией
// т.е. используется лишь внутри основной функции вычисления хэш-значения
void functionG_Zero_bitslice(T *h, const T *m)
{
	int i;
	T* t = h + 512;
	T *tmp=t+512;
	//T* t = aligned_malloc(sizeof(T) * 512*2);
	for (i = 0; i < 512; ++i) t[i] = h[i];
	LPS_bitslice_SSE(t, tmp);
	functionE_bitslice(t, m);
	for (i = 0; i < 512; ++i) h[i] = _XOR(h[i], _XOR(t[i], m[i])); // h[i] ^= t[i] ^ m[i];
	//aligned_free(t);
}


// сложение над кольцом 2^N, где N = size по маске
// т.е. маска задает какие позиции будут меняться
void Add_Z_2_N_mask_bitslice(T *v1, T *v2, T mask, uint32_t size)
{
	uint32_t i;
	T xXORy, xANDy, s = _ZERORIGHT; // знак переноса

	for (i = 0; i < size; ++i)
	{
		xXORy = _XOR(v1[i], v2[i]); // v1[i] ^ v2[i];
		xANDy = _AND(v1[i], v2[i]); // v1[i] & v2[i];
		v1[i] = _ANDNOT(mask, v1[i]); // v1[i] &= ~mask; // позиции в которые будем записывать занулить, остальные позиции останутся без изменений
		v1[i] = _OR(v1[i], _AND(mask, _XOR(xXORy, s))); // v1[i] |= (xXORy ^ s) & mask;
		s = _AND(s, xXORy); // s &= xXORy;
		s = _OR(s, xANDy); // s |= xANDy;
	}
}


void Add_512_Z_2_N_mask_bitslice(T *v1, T mask, uint32_t size)
{
	uint32_t i;
	T t, s = v1[9]; // знак переноса
	
	v1[9] = _XOR(mask, v1[9]);
	for (i = 10; i < size; ++i)
	{
		t = v1[i]; // т.к. в векторе со значением 512 лишь на 9-й позиции единицы, остальные нули
		v1[i] = _ANDNOT(mask, v1[i]); // v1[i] &= ~mask; // позиции в которые будем записывать занулить, остальные позиции останутся без изменений
		v1[i] = _OR(v1[i], _AND(mask, _XOR(t, s)));
		s = _AND(s, t);		
	}
}


// сложение над кольцом 2^N, где N = size
void Add_Z_2_N_bitslice(T *v1, T *v2, uint32_t size)
{
	Add_Z_2_N_mask_bitslice(v1, v2, _NOT(_ZERORIGHT), size);
	//Add_Z_2_N_mask_bitslice(v1, v2, ~(T(0)), size);
}


// это частный случай сложения, т.е. можно просто вызвать верхнюю функцию с нужным параметром
void Add_Z_2_512_bitslice(T *v1, T *v2)
{
	Add_Z_2_N_bitslice(v1, v2, 512);
}


//!!! эту версию заменил на Streebog_bitslice_ctx, т.к. там не требуется выделять постоянно память под mem и
// hash_value также располагается в контексте
// количество сообщений countMessage
int Streebog_bitslice(const struct message_context *msg, uint32_t countMessage, uint32_t hashLength, uint8_t (*hash_value)[64])
{
	uint32_t i, j; /* текущий байт сообщения */
	T v2;
	uint64_t cb = 0; // достаточно одного счетчика байтов, не нужно массив заводить

	if (hashLength != 256 && hashLength != 512) return -1;
	if (!countMessage) return 0;

	T* mem = aligned_malloc(sizeof(T) * 512 * 7, sizeof(T)); // было sizeof(T) * 512 * 8, но удалил _512
	if (!mem) return -2;
	T	*m = mem, * N = mem + 512, * Sigma = mem + 1024, * h = mem + 1536; // and mem+2048 for temp variable for functionG_bitslice

	/* Stage 1*/
	for (i = 0; i < 512; ++i)
	{
		N[i] = Sigma[i] = m[i] = _ZERORIGHT;
		h[i] = ((hashLength == 256 && !(i&7)) ? _NOT(_ZERORIGHT) : _ZERORIGHT); // 0x01010101 : 0
	}

	/* Stage 2 */
	while (1) //(cb * 8 + 512 <= lengthInBits[0]) /* 2.1 */
	{
		// 2.1 здесь проверка на наличие длинных сообщений, для которых требуется еще выполнять этап 2 алгоритма
		v2 = _ZERORIGHT;
		for (j = 0; j < countMessage; ++j)
		{
			if (msg[j].lengthInBits < cb * 8 + 512) continue;
			Set1_T_macros(v2, j);
		}
		if (IsZero(v2)) break; // Если v2==0, тогда нет или не осталось больше необработанных длинных сообщений, поэтому переход на этап 3
		// в результате в v2 единицы будут стоять на тех позициях, для которых соответствующие сообщения требуют выполнения этапа 2

		/* 2.2 */
		ConvertMsgToBitSlice_Stage2(msg, countMessage, v2, cb, m);
		cb += 64;

		/* 2.3 */
		functionG_bitslice_mask(N, h, m, v2);
		
		/* 2.4 */
		Add_512_Z_2_N_mask_bitslice(N, v2, 512);
		//Add_Z_2_N_mask_bitslice(N, _512, v2, 512); //!!!
				
		/* 2.5 */
		Add_Z_2_N_mask_bitslice(Sigma, m, v2, 512);
	}

	/* Stage 3 */
	/* 3.1 */
	ConvertMsgToBitSlice_Stage3(msg, countMessage, m);

	/* 3.2	*/
	functionG_bitslice(N, h, m);

	/* 3.3 */ /* после этапа 3.3, N должен равняться длине сообщений. Это ясно из описания алгоритма */
	for (j = 0; j < countMessage; ++j)
	{
		SetByteInBitSliceSSE(j, msg[j].lengthInBits & 0xFF, &N[0]); // 8 младших байт
		//SetBit_T_macros(N[8], j, (msg[j].lengthInBits >> 8) & 1);
		if ((msg[j].lengthInBits >> 8) & 1) Set1_T_macros(N[8], j);
	}

	/* 3.4 */
	Add_Z_2_512_bitslice(Sigma, m);

	/* 3.5 */
	functionG_Zero_bitslice(h, N);

	/* 3.6 */
	functionG_Zero_bitslice(h, Sigma);

	ConvertHashFromBitSlice_all(h, countMessage, hashLength, hash_value);

	aligned_free(mem);

	return 0;
}


int streebog_bitslice_context_init(struct streebog_bitslice_context* ctx)
{
	ctx->mem = aligned_malloc(sizeof(T) * 512 * 7, sizeof(T)); // было sizeof(T) * 512 * 8, но удалил _512	
	if (!ctx->mem) return -2;
	ctx->hash_value = malloc(sizeof(ctx->hash_value[0]) * MaxCountMessage);
	return 0;
}


int streebog_bitslice_context_free(struct streebog_bitslice_context* ctx)
{
	if (ctx->mem) aligned_free(ctx->mem);
	if (ctx->hash_value) free(ctx->hash_value);
	return 0;
}


// количество сообщений countMessage
// если hash_value==NULL, тогда результат сохраняется в ctx->hash_value, иначе
int Streebog_bitslice_ctx(struct streebog_bitslice_context *ctx, const struct message_context *msg, uint32_t countMessage, uint32_t hashLength, uint8_t (*hash_value)[64])
{
	uint32_t j;
	T v2;
	uint64_t cb = 0; // достаточно одного счетчика байтов, не нужно массив заводить

	if (hashLength != 256 && hashLength != 512) return -1;
	if (!countMessage) return 0;

	T	*m = ctx->mem, * N = ctx->mem + 512, * Sigma = ctx->mem + 1024, * h = ctx->mem + 1536;
	
	/* Stage 1*/
	for (uint32_t i = 0; i < 512; ++i)
	{
		N[i] = Sigma[i] = m[i] = _ZERORIGHT;
		h[i] = ((hashLength == 256 && !(i&7)) ? _NOT(_ZERORIGHT) : _ZERORIGHT); // 0x01010101 : 0
	}

	/* Stage 2 */
	while (1) //(cb * 8 + 512 <= lengthInBits[0]) /* 2.1 */
	{
		// 2.1 здесь проверка на наличие длинных сообщений, для которых требуется еще выполнять этап 2 алгоритма
		v2 = _ZERORIGHT;
		for (j = 0; j < countMessage; ++j)
		{
			if (msg[j].lengthInBits < cb * 8 + 512) continue;
			Set1_T_macros(v2, j);
		}
		if (IsZero(v2)) break; // Если v2==0, тогда нет или не осталось больше необработанных длинных сообщений, поэтому переход на этап 3
		// в результате в v2 единицы будут стоять на тех позициях, для которых соответствующие сообщения требуют выполнения этапа 2

		/* 2.2 */
		ConvertMsgToBitSlice_Stage2(msg, countMessage, v2, cb, m);
		cb += 64;

		/* 2.3 */
		functionG_bitslice_mask(N, h, m, v2);
		
		/* 2.4 */
		Add_512_Z_2_N_mask_bitslice(N, v2, 512);
		//Add_Z_2_N_mask_bitslice(N, _512, v2, 512); //!!!
				
		/* 2.5 */
		Add_Z_2_N_mask_bitslice(Sigma, m, v2, 512);
	}

	/* Stage 3 */
	/* 3.1 */
	ConvertMsgToBitSlice_Stage3(msg, countMessage, m);

	/* 3.2	*/
	functionG_bitslice(N, h, m);

	/* 3.3 */ /* после этапа 3.3, N должен равняться длине сообщений. Это ясно из описания алгоритма */
	for (j = 0; j < countMessage; ++j)
	{
		SetByteInBitSliceSSE(j, msg[j].lengthInBits & 0xFF, &N[0]); // 8 младших байт
		//SetBit_T_macros(N[8], j, (msg[j].lengthInBits >> 8) & 1);
		if ((msg[j].lengthInBits >> 8) & 1) Set1_T_macros(N[8], j);
	}

	/* 3.4 */
	Add_Z_2_512_bitslice(Sigma, m);

	/* 3.5 */
	functionG_Zero_bitslice(h, N);

	/* 3.6 */
	functionG_Zero_bitslice(h, Sigma);

	ConvertHashFromBitSlice_all(h, countMessage, hashLength, ctx->hash_value);
	
	if (hash_value!=NULL)
	{
		const uint32_t cb = hashLength==256 ? 32:64;
		for (uint32_t i = 0; i < countMessage; ++i)
		{
			for (uint32_t j = 0; j < cb; ++j)
			{
				hash_value[i][j]=ctx->hash_value[i][j];
			}
		}
	}

	return 0;
}
