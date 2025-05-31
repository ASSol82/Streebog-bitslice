

#include <stdint.h>
#include "VectorType.h"
#include "Streebog_bitslice.h"


#define GetBit_T_macros(v, num) ((((uint8_t*)(&v))[(num) >> 3] >> ((num) & 7))&1)
#define Set1_T_macros(v, num) ((uint8_t*)(&v))[(num) >> 3] |= (1 << ((num) & 7));
#define SetBit_T_macros(v, num, b) if (b) ((uint8_t*)(&v))[(num) >> 3] |= (1 << ((num) & 7)); else ((uint8_t*)(&v))[(num) >> 3] &= ~(1 << ((num) & 7));


// макросом заменил функцию GetBit
#define GetBit(M, numBit) ((M[(numBit) >> 3] >> ((numBit) - (((numBit) >> 3) << 3))) & 1)
// извлечь байт из вектора типа T
#define GetByte_T_macros(v, numByte) ((uint8_t*)(&(v)))[numByte];


void SetByteInBitSliceSSE(const uint32_t num, const uint8_t src, T *dst);
void SetArrayByteToBitSlice(int num, const uint8_t src[64], T* dst);
void ConvertMsgToBitSlice_Stage2(const struct message_context* msg, const uint32_t countMessage, const T v, const uint64_t cb, T* dst);
void ConvertMsgToBitSlice_Stage3(const struct message_context* msg, const uint32_t countMessage, T* dst);
void ConvertHashFromBitSlice_all(const T h[512], const uint32_t countMessage, const uint32_t hashLength, uint8_t(*hash_value)[64]);
