

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "Functions.h"
#include "Pi_bitslice.h"
#include "Streebog_bitslice_test.h"


int main(int argc, char* argv[])
{	
	uint32_t countTestMessage = 1048576;
	uint64_t lengthMessageInBits = 504; //1016; //504;
	int i;

	for (i = 1; i < argc; i++)
	{
		if (i == 1)
		{
			countTestMessage = atoi(argv[i]);
		}
		else if (i == 2)
		{
			lengthMessageInBits = atoi(argv[i]);
		}
	}

	printf("sizeof(T) = %zu\n", sizeof(T));
	printf("PiStroke version %d\n", PiVersion());

//	Streebog_bitslice_SSE_test();
//	Streebog_bitslice_SSE_array_test(256); // verify bitslice for 256 bits hash value
//	Streebog_bitslice_SSE_array_test(512); // verify bitslice for 512 bits hash value

	// benchmark Speed Mbytes/sec = ((double)countTestMessage*(double)lengthMessageInBits) / 8388608.f / elapsedTimeInSeconds
	Streebog_bitslice_test_ControlValue(countTestMessage, lengthMessageInBits, 256);

	return 0;
}
