#ifndef __STREEBOG_BITSLICE__
#define __STREEBOG_BITSLICE__


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


struct message_context
{
	uint8_t *M;
	uint64_t lengthInBits;
};


struct streebog_bitslice_context
{
	T* mem;
	uint8_t (*hash_value)[64]; // здесь будет результат, если hashLength==256, тогда младшие 32 байта будут значимыми
};


int streebog_bitslice_context_init(struct streebog_bitslice_context *ctx);
int streebog_bitslice_context_free(struct streebog_bitslice_context *ctx);


//GOST_R_34112012_hash_bitslice
int Streebog_bitslice_ctx(struct streebog_bitslice_context *ctx, const struct message_context *msg, uint32_t countMessage, uint32_t hashLength, uint8_t (*hash_value)[64]);
int Streebog_bitslice(const struct message_context *msg, uint32_t countMessage, uint32_t hashLength, uint8_t (*hash_value)[64]);


#ifdef __cplusplus
}
#endif


#endif
