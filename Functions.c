// _mm256_storeu_epi8 эта функция требует опций компилятора в Ubuntu CodeLite -mavx512vl;-mavx512bw
// т.е. формально поддерживается AVX512
// поэтому пробую заменить эту функцию на обычную работу с памятью с указателями


#include "LogicalOperations.h"
#include "Functions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//static const uint8_t mask[8] = { ~1,~2,~4,~8,~0x10,~0x20,~0x40,~0x80 };
static const uint8_t mask[8] = { 0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F };
//static const uint8_t mask1[8] = { 1,2,4,8,0x10,0x20,0x40,0x80 };


//#if MaxCountMessage>0 //!!! MaxCountMessage>64
// выделить память, выравненную по параметру alignByte
// например, для использования __m256i следует выравнивать до 32 байт, т.е. alignByte = 32
#ifdef _MSC_VER // для Visual Studio

#include <malloc.h>

void* aligned_malloc(size_t size, uint32_t alignByte) {
	return _aligned_malloc(size, alignByte);
}
void aligned_free(void* ptr) {
	_aligned_free(ptr);
}

#elif defined __GNUC__ //!!! например, для gcc, хотя уточни, там должно быть свое выравнивание

void* aligned_malloc(size_t size, uint32_t alignByte)
{
	return aligned_alloc(alignByte, size);
}
void aligned_free(void *ptr) {
    free(ptr);
}

#else

void* aligned_malloc(size_t size, uint32_t alignByte)
{
	char* mem = malloc(size + alignByte + sizeof(mem));
	if (!mem) return 0;
	char** ptr = (char**)((uintptr_t)(mem + alignByte + sizeof(mem)) & ~(alignByte - 1));
	ptr[-1] = mem;
	return ptr;
}
void aligned_free(void *ptr) {
    free(((char**)ptr)[-1]);
}	
	
#endif


// num - позиция в bitslice векторах dst[0],dst[1],...,dst[7] в которую записывается байт src
void SetByteInBitSliceSSE(int num, const uint8_t src, T *dst)
{
	const int nByte = (num>>3), nBit=(num&7);
	uint8_t *p;
	p = (uint8_t*)(dst+0); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 0) & 1) << nBit);
	p = (uint8_t*)(dst+1); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 1) & 1) << nBit);
	p = (uint8_t*)(dst+2); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 2) & 1) << nBit);
	p = (uint8_t*)(dst+3); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 3) & 1) << nBit);
	p = (uint8_t*)(dst+4); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 4) & 1) << nBit);
	p = (uint8_t*)(dst+5); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 5) & 1) << nBit);
	p = (uint8_t*)(dst+6); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 6) & 1) << nBit);
	p = (uint8_t*)(dst+7); p[nByte] &= mask[nBit]; p[nByte] |= (((src >> 7) & 1) << nBit);
}


// записать бит bit в позицию num элемента на который указывает dst
//void SetBitInBitSliceSSE(int num, const uint8_t bit, T* dst)
//{
//	SetBit_T(dst, num, bit);
//}


uint8_t GetBit_T(const T v, const int num)
{
	const int nByte = (num >> 3), nBit = (num & 7);
	const uint8_t* p = (uint8_t*)(&v);
	return (p[nByte] >> nBit) & 1;
}


// установить бит b на заданной позиции num в v
void SetBit_T(T *v, int num, uint8_t b)
{
	const int nByte = (num >> 3), nBit = (num & 7);
	uint8_t *p = (uint8_t*)v; p[nByte] &= mask[nBit]; p[nByte] |= ((b&1) << nBit);
}
