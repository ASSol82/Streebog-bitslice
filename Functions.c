// _mm256_storeu_epi8 эта функция требует опций компилятора в Ubuntu CodeLite -mavx512vl;-mavx512bw
// т.е. формально поддерживается AVX512
// поэтому пробую заменить эту функцию на обычную работу с памятью с указателями


//#include "Functions.h"
//#include <string.h>
#include <stdint.h>
//#include <stdio.h>
#include <stdlib.h>


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
