#ifndef __PICOORDFUNC_BITSLICE_SSE__
#define __PICOORDFUNC_BITSLICE_SSE__


#include "VectorType.h"
#include "LogicalOperations.h"


static const int PiStroke_ver = 21;


// 8 элементов
#define bitAlpha_macros(a0,a1,a2,a3,a4,a5,a6,a7,tmp,tmp2,tmp3,tmp4) \
	tmp = a0; tmp2 = a2; tmp3 = a3; tmp4 = a7; \
	a2=_XOR(a4, a7); \
	a3=_XOR(a6, tmp2); \
	a0=_XOR(a3, a5); \
	a7=_XOR(a6, tmp); \
	tmp=_XOR(tmp3, a7); \
	a6=_XOR(tmp, a1); \
	a1=_XOR(tmp4, _XOR(a5, _XOR(tmp3, a1))); \
	a4=_XOR(a1, tmp2); \
	a5=_XOR(tmp, a4);


#define bitOmega_macros(a0,a1,a2,a3,a4,a5,a6,a7,tmp1,tmp2,tmp3) \
	tmp1=a1, tmp2=a2, tmp3=a7; \
	a1=_XOR(a1,a7); \
	a2=_XOR(a2,a6); \
	a7=_XOR(a3, tmp1); \
	a4=_XOR(a4,_XOR(tmp3,a7)); \
	a6=tmp2;


#define bitInv_macros(a0,a1,a2,a3,tmp5,tmp6,tmp7,tmp8,tmp12,tmp13,tmp14) \
	tmp12 = _AND(a1, a2); \
	tmp13 = _AND(_XOR(tmp12, a0), a3); \
	tmp14 = _OR(tmp12, a3); \
	tmp7 = _XOR(a2, tmp13); \
	tmp8 = _XOR(tmp14, _XOR(tmp13, _OR(tmp13, a2))); \
	tmp6 = _XOR(_XOR(_AND(a1, a3), tmp8), _OR(tmp12, a0)); \
	tmp5 = _XOR(a1, _XOR(tmp6, _XOR(tmp14, _AND(tmp6, a0))));


#define bitNu0_macros(a0,a1,a2,a3,tmp1,tmp2,tmp3,tmp4,tmp5) \
	tmp1 = _AND(a1, a2); tmp2 = _XOR(tmp1, a0); tmp3 = _XOR(a1, tmp2); tmp4 = _NOT(_OR(tmp1, tmp2)); tmp5 = _AND(a1, tmp3); \
	tmp1 = a3; \
	a1=_XOR(tmp2, _AND(_OR(tmp3, a2), a3)); \
	a0=_XOR(tmp4, _OR(_XOR(tmp5, a2), a3)); \
	tmp2 = _AND(a1, a0); \
	a3 = _XOR(tmp5, _AND(_XOR(tmp2, a2), a3)); \
	a2 = _XOR(tmp1, _XOR(_OR(tmp2, tmp4), tmp3));


#define bitNu1_macros(a0,a1,a2,a3,tmp0,tmp1,tmp2) \
	tmp0=a3; \
	a3 = _XOR(_XOR(_OR(a3, a1), a2), a0); \
	tmp1 = _NOT(a1); \
	a0 = _XOR(tmp1, _OR(a3, tmp0)); \
	tmp2 = _XOR(a3, a1); \
	a1 = _XOR(_OR(tmp2, a0), a2); \
	a2 = _XOR(_OR(tmp2, tmp1), tmp0);


// 4 бита
#define bitPhi_macros(a0,a1,a2,a3,tmp1,tmp2,tmp3,tmp4) \
	tmp1 = _XOR(a1, a3); tmp2 = _OR(a1, a0); tmp3 = _OR(_AND(tmp2, tmp1), a2); tmp4 = _XOR(a2, tmp2); \
	a2=_XOR(tmp1,_XOR(a0,tmp3)); \
	tmp2=_OR(_AND(tmp4,a2),a3); \
	a3=_XOR(a0,tmp2); \
	tmp3 =_AND(_XOR(a1, tmp2), tmp3); \
	a1=_XOR(tmp3, _AND(tmp4, a1)); \
	a0=_OR(_NOT(tmp4), tmp3);


// 4 бита
// 20241015 добавил выходные переменные b0,b1,b2,b3
// выходные переменные требуются, чтобы сразу использовать перестановку тау
// см. макрос pi_r_macros_2
#define bitSigma_macros(a0,a1,a2,a3,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,b0,b1,b2,b3) \
	tmp1 = _XOR(a3, _OR(a2, a1)), tmp2 = _XOR(a0, tmp1), tmp3 = _XOR(tmp2, a1), \
		tmp4 = _XOR(tmp1, tmp3), tmp5 = _AND(tmp4, tmp2), tmp6 = _OR(tmp5, a2); \
	b1 = _XOR(tmp1, _OR(_XOR(_AND(a2, tmp1), a1), a0)); \
	b2 = _XOR(tmp4, _OR(_XOR(_NOT(tmp5), a2), a0)); \
	b0 = _XOR(tmp3, tmp6); \
	b3 = _XOR(_OR(tmp2, b2), _XOR(tmp6, a3));


#define mulf_2_2_macros(a0, a1, b0, b1, tmp) \
	tmp = _AND(_XOR(a0, a1), _XOR(b0, b1)); \
	a0 = _XOR(_AND(a0, b0), tmp); \
	a1 = _XOR(_AND(a1, b1), tmp);


// по 4 элемента
#define mul2_2_2_macros(a0, a1, a2, a3, b0, b1, b2, b3, tmp0, tmp1, tmp2, tmp3, tmp4) \
	tmp0 = _XOR(a0, a2); tmp1 = _XOR(a1, a3); tmp2 = _XOR(b0, b2); tmp3 = _XOR(b1, b3); \
	mulf_2_2_macros(tmp0, tmp1, tmp2, tmp3, tmp4); \
	tmp2 = a0; tmp3 = a1; \
	mulf_2_2_macros(tmp2, tmp3, b0, b1, tmp4); \
	mulf_2_2_macros(a2, a3, b2, b3, tmp4); \
	a0 = _XOR(tmp2, _XOR(a2, a3)); \
	a1 = _XOR(tmp3, a2); \
	a2 = _XOR(tmp2, tmp0); \
	a3 = _XOR(tmp3, tmp1);


//{ _ALIGN(MALLOCALIGN) register T tmp[14]; \ ругается MSVC

// Pi в виде макроса
#define pi_r_macros(a0, a1, a2, a3, a4, a5, a6, a7) \
	{ _ALIGN(MALLOCALIGN) T tmp[14]; \
	bitAlpha_macros(a0,a1,a2,a3,a4,a5,a6,a7,tmp[0],tmp[1],tmp[2],tmp[3]); \
	tmp[0] = _NOT(_OR(_OR(a0, a1), _OR(a2, a3))); \
	tmp[1] = a4; tmp[2] = a5; tmp[3] = a6; tmp[4] = a7; \
	bitNu0_macros(tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7],tmp[8],tmp[9]); \
	bitInv_macros(a0,a1,a2,a3,tmp[5],tmp[6],tmp[7],tmp[8],tmp[12],tmp[13],tmp[11]); \
	mul2_2_2_macros(a4, a5, a6, a7, tmp[5], tmp[6], tmp[7], tmp[8], tmp[9], tmp[10], tmp[11], tmp[12], tmp[13]); \
	bitNu1_macros(a4,a5,a6,a7,tmp[5],tmp[6],tmp[7]); \
	a4=_XOR(_AND(tmp[0], tmp[1]), a4); \
	a5=_XOR(_AND(tmp[0], tmp[2]), a5); \
	a6=_XOR(_AND(tmp[0], tmp[3]), a6); \
	a7=_XOR(_AND(tmp[0], tmp[4]), a7); \
	tmp[0] = a4; tmp[1] = a5; tmp[2] = a6; tmp[3] = a7; \
	bitPhi_macros(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]); \
	mul2_2_2_macros(a0, a1, a2, a3, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], tmp[6], tmp[7], tmp[8]); \
	bitSigma_macros(a0, a1, a2, a3, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], a0, a1, a2, a3); \
	bitOmega_macros(a0, a1, a2, a3, a4, a5, a6, a7, tmp[0], tmp[1], tmp[2]); }


// Pi в виде макроса с выходными векторами b0, b1, b2, b3, b4, b5, b6, b7. Выход записывается именно в b0, b1, b2, b3, b4, b5, b6, b7
#define pi_r_macros_2(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7) \
	{ _ALIGN(MALLOCALIGN) T tmp[14]; \
	bitAlpha_macros(a0,a1,a2,a3,a4,a5,a6,a7,tmp[0],tmp[1],tmp[2],tmp[3]); \
	tmp[0] = _NOT(_OR(_OR(a0, a1), _OR(a2, a3))); \
	tmp[1] = a4; tmp[2] = a5; tmp[3] = a6; tmp[4] = a7; \
	bitNu0_macros(tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7],tmp[8],tmp[9]); \
	bitInv_macros(a0,a1,a2,a3,tmp[5],tmp[6],tmp[7],tmp[8],tmp[12],tmp[13],tmp[11]); \
	mul2_2_2_macros(a4, a5, a6, a7, tmp[5], tmp[6], tmp[7], tmp[8], tmp[9], tmp[10], tmp[11], tmp[12], tmp[13]); \
	bitNu1_macros(a4,a5,a6,a7,tmp[5],tmp[6],tmp[7]); \
	b4=_XOR(_AND(tmp[0], tmp[1]), a4); \
	b5=_XOR(_AND(tmp[0], tmp[2]), a5); \
	b6=_XOR(_AND(tmp[0], tmp[3]), a6); \
	b7=_XOR(_AND(tmp[0], tmp[4]), a7); \
	tmp[0] = b4; tmp[1] = b5; tmp[2] = b6; tmp[3] = b7; \
	bitPhi_macros(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]); \
	mul2_2_2_macros(a0, a1, a2, a3, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], tmp[6], tmp[7], tmp[8]); \
	bitSigma_macros(a0, a1, a2, a3, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], b0, b1, b2, b3); \
	bitOmega_macros(b0, b1, b2, b3, b4, b5, b6, b7, tmp[0], tmp[1], tmp[2]); }


#endif
