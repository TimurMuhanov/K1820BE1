#ifndef __ASMS_H__
#define __ASMS_H__ 1
#include "../lib/lines.h"

typedef int (*fun_asm_t)(struct lines_t *ln);

int asmAssembly(fun_asm_t fun);

#endif /* __ASMS_H__ */
