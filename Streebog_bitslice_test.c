

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "VectorType.h"
#include "Functions.h"
#include "Pi_bitslice.h"
#include "LPS_bitslice.h"
#include "LogicalOperations.h"
#include "Streebog_bitslice.h"
#include "Streebog_bitslice_test.h"


struct message_test
{
	char* msg;
	char* h256;
	char* h512;
};


const struct message_test msg_test[] = {
	{
		"323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130",
		"00557be5e584fd52a449b16b0251d05d27f94ab76cbaa6da890b59d8ef1e159d",
		"486f64c1917879417fef082b3381a4e211c324f074654c38823a7b76f830ad00fa1fbae42b1285c0352f227524bc9ab16254288dd6863dccd5b9f54a1ad0541b"
	},
	{
		"fbe2e5f0eee3c820fbeafaebef20fffbf0e1e0f0f520e0ed20e8ece0ebe5f0f2f120fff0eeec20f120faf2fee5e2202ce8f6f3ede220e8e6eee1e8f0f2d1202ce8f0f2e5e220e5d1",
		"508f7e553c06501d749a66fc28c6cac0b005746d97537fa85d9e40904efed29d",
		"28fbc9bada033b1460642bdcddb90c3fb3e56c497ccd0f62b8a2ad4935e85f037613966de4ee00531ae60f3b5a47f8dae06915d5f2f194996fcabf2622e6881e"
	},
	{
		"323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130",
		"286F508BBD53027DFA74F95C1E8146419EB45F57946E51B93F636B9127BF4A71",
		"E5B8DA447601D031019E8FB087961E0498B4CB43E9E5E1E4D2A17484F9F1D81DBB580F1EF76DD0223F6539DEFF56F82B9CA0049FA0AB18AF2B254C07BD13053C"
	}
};


uint8_t ConvertHexCharToByte(char chr)
{
	if (chr >= '0' && chr <= '9') return (chr - '0');
	if (chr == 'A' || chr == 'a') return 10;
	if (chr == 'B' || chr == 'b') return 11;
	if (chr == 'C' || chr == 'c') return 12;
	if (chr == 'D' || chr == 'd') return 13;
	if (chr == 'E' || chr == 'e') return 14;
	if (chr == 'F' || chr == 'f') return 15;
	return 0;
}


/* преобразует текстовые данные в массив байтов */
void ConvertHexStrCharToByte(const char* str, uint8_t* M)
{
	const int len = strlen(str);
	int i, numByte = 0;
	uint8_t b;
	for (i = len - 1; i >= 0; i--)
	{
		b = ConvertHexCharToByte(str[i--]);
		if (i >= 0)
		{
			b |= (ConvertHexCharToByte(str[i]) << 4);
		}
		M[numByte++] = b;
	}
}


// 1 - успешно, 0 - не успешно
int verify_hash(const uint8_t* h, const char* HM)
{
	uint8_t H_test[64];
	const uint32_t hash_test_countBytes = strlen(HM) / 2;
	ConvertHexStrCharToByte(HM, H_test);
	for (int i = 0; i < hash_test_countBytes; ++i)
	{
		if (h[i] != H_test[i]) return 0;
	}
	return 1;
}


int Streebog_bitslice_SSE_test_local(const char* msg, const char* hash_msg_test, int hashLength)
{
	struct message_context msg_ctx;
	int ret = 1;
	uint8_t h_[1][64];
	const uint32_t countBytes = strlen(msg) / 2;
	msg_ctx.lengthInBits = countBytes * 8;
	msg_ctx.M = malloc(countBytes);
	if (!msg_ctx.M) return 0;// -1;
	ConvertHexStrCharToByte(msg, msg_ctx.M);

	Streebog_bitslice(&msg_ctx, 1, hashLength, h_);

	if (!verify_hash(h_[0], hash_msg_test)) ret = 0;

	free(msg_ctx.M);
	return ret; /* ret=1, правильно вычислилось хэш-значение */
}


int Streebog_bitslice_SSE_test()
{
	int error = 0;
	for (int i = 0; i < 3; ++i)
	{
		error += (Streebog_bitslice_SSE_test_local(msg_test[i].msg, msg_test[i].h256, 256) ? 0 : 1);
		error += (Streebog_bitslice_SSE_test_local(msg_test[i].msg, msg_test[i].h512, 512) ? 0 : 1);
	}
	printf("Streebog_bitslice test %s\n", (!error ? "successfully" : "error"));
	return 0;
}


int Streebog_bitslice_SSE_array_test(uint32_t hashLength)
{
	int ret = 1;
	uint8_t (*h_)[64];
	const uint32_t countMessages = 5;
	const int numMsg[] = { 0,1,1,2,1 }; // номера сообщений из массива msg_test
	struct message_context* msg = malloc(sizeof(struct message_context) * countMessages);
	h_ = malloc(sizeof(h_[0]) * MaxCountMessage);

	for (int j = 0; j < countMessages; ++j)
	{
		uint32_t countBytes = strlen(msg_test[numMsg[j]].msg) / 2;
		msg[j].lengthInBits = countBytes * 8;
		msg[j].M = malloc(countBytes);
		ConvertHexStrCharToByte(msg_test[numMsg[j]].msg, msg[j].M);
	}

	Streebog_bitslice(msg, countMessages, hashLength, h_);

	for (int j = 0; j < countMessages; ++j)
	{
		if (!verify_hash(h_[j], (hashLength == 256 ? msg_test[numMsg[j]].h256 : msg_test[numMsg[j]].h512))) ret = 0;
	}

	for (int j = 0; j < countMessages; j++)
	{
		free(msg[j].M);
	}
	free(msg);
	free(h_);
	printf("Streebog_bitslice_SSE_array, hash length %d, test %s\n", hashLength, (ret ? "successfully" : "error"));
	return ret; /* ret=1 правильно вычислилось хэш-значение */
}


void Streebog_bitslice_SSE_array_ControlValue(uint32_t countTestMessage, uint64_t messageLength, uint32_t hashLength)
{
	uint32_t v = 0x12345678; // init value
	int i, j;
	int64_t n;
	struct message_context *msg;
	uint8_t (*h)[64];
	//const uint32_t countMessages = (countTestMessage < MaxCountMessage ? countTestMessage : MaxCountMessage);
	const uint32_t memoryNeed = ((messageLength - 1) / 32 + 1) * 4; // выделяемая память под сообщение кратна 32 битам или 4 байтам

	if (countTestMessage < 1)
	{
		printf("Error: countTestMessage < 1\n");
		return;
	}
	if (messageLength < 1)
	{
		printf("Error: messageLength < 1\n");
		return;
	}

	printf("Streebog_bitslice_SSE_array_ControlValue\n");
	printf("T length in bits %" PRIuMAX "\n", sizeof(T)*8);
	static const uint32_t load_vector = MaxCountMessage; // сколько обрабатывать сообщений за раз, load_vector<=MaxCountMessage
	printf("load_vector = %d from %d\n", load_vector, MaxCountMessage);
	printf("countTestMessage %u\n", countTestMessage);
	printf("messageLengthInBits %" PRIuMAX "\n", messageLength);
	//printf("messageLengthInBits %llu\n", messageLength);
	printf("hash length %u\n", hashLength);
	printf("memoryNeed for 1 message in bytes %u\n", memoryNeed);
	int64_t dataSizeMb = countTestMessage * messageLength / 8 / 1048576; // размер сообщений в Мбайтах
	printf("data size %" PRIu64 " Mb\n", dataSizeMb);
	fflush(stdout);

	msg = malloc(sizeof(msg[0]) * countTestMessage);
	for (j = 0; j < countTestMessage; ++j)
	{
		msg[j].lengthInBits = messageLength;
		msg[j].M = malloc(memoryNeed);
		for (i = 0; i < memoryNeed; i += 4) // заполняем всю выделенную память, кратную 4 байтам
		{
			for (int nbit = 0; nbit < 4; ++nbit)
			{
				msg[j].M[i + nbit] = (v >> (nbit * 8));
			}
			++v;
		}
	}
	h = malloc(sizeof(h[0]) * countTestMessage);
	
	clock_t startTime = clock();

	struct timespec startTime3, endTime3;
	timespec_get(&startTime3, TIME_UTC);

	for (n = 0; n < countTestMessage; n += load_vector)
	{
		const int cycleLen = (n + load_vector < countTestMessage ? load_vector : countTestMessage - n);
		Streebog_bitslice(msg + n, cycleLen, hashLength, h + n);
	}

	timespec_get(&endTime3, TIME_UTC);
	double cpuTimeUsed3 = ((double)endTime3.tv_sec - startTime3.tv_sec) + ((double)endTime3.tv_nsec - startTime3.tv_nsec) / 1000000000.0;

	clock_t endTime = clock();
	double cpuTimeUsed = ((double)endTime - startTime) / CLOCKS_PER_SEC;

	uint32_t verify_check = 0;
	for (j = 0; j < countTestMessage; ++j)
	{
		uint32_t v1 = 0, v_temp;
		for (i = 0; i < 4; ++i)
		{
			v_temp = (uint8_t)h[j][i];
			v_temp <<= (i * 8);
			v1 |= v_temp;
		}
		verify_check ^= v1;
	}

	printf("control value = %08X\n", verify_check);

	printf("Time elapsed variant clock() %f\n", cpuTimeUsed);
	printf("Time elapsed variant timespec_get() %f\n", cpuTimeUsed3);

	for (j = 0; j < countTestMessage; ++j)
	{
		free(msg[j].M);
	}
	free(msg);
	free(h);

	double speed = (double)dataSizeMb / cpuTimeUsed;
	printf("Speed %f Mb/sec\n", speed);
	double speed3 = (double)dataSizeMb / cpuTimeUsed3;
	printf("Speed3 %f Mb/sec\n", speed3);

	return;
}
