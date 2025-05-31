#ifndef __TYPES__
#define __TYPES__


#define BYTE    unsigned char
#define v8      BYTE
#define uint16	unsigned short
#define v16     uint16
#define uint32  unsigned int
#define v32     uint32
/*#define uint64 	unsigned long long*/


#define VERIFY_SIZE_TYPES(type, size) { char a[sizeof(type)==(size)?1:-1]; a[0]=0; a[0]=a[0]; }


#define count_bytes 32 /* кол-во байтов для хранения 256-битового числа */
#define decl_num(var_) v8 var_[count_bytes] /* макрос используется для объявления переменной 256-битового числа */
#define arg_num(var_) v8* var_ /* макрос используется для определения типа аргумента при передачи в функцию 256-битового числа */
#define c_arg_num(var_) const v8* var_

#define count_words 16 /* кол-во 16-битовых слов из которых составляется большое число*/
#define decl_num_v16(var_) v16 var_[count_words] /* макрос используется для объявления переменной 256-битового числа */
#define arg_num_v16(var_) v16* var_ /* макрос используется для определения типа аргумента при передачи в функцию 256-битового числа */


#endif
