#ifndef __FUNCTIONS_SSE__
#define __FUNCTIONS_SSE__


#include <stdint.h>
#include <stddef.h> // для определения size_t


#ifdef __cplusplus
extern "C" {
#endif


void *aligned_malloc(size_t size, uint32_t alignByte);
void aligned_free(void *ptr);


#ifdef __cplusplus
}
#endif


#endif
