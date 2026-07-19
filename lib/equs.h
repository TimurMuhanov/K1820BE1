#ifndef __EQUS_H__
#define __EQUS_H__ 1

#include "lines.h"

void equInit(void);

// @return 0 - ok, else - errors
int equAdd(struct lines_t *ln);

// @return 0 - ok, else - errors
int equResolver(void);

void equClean(void);

int equGet(char *c, int sz, int *ret);

void equPrint(void);

#endif /* __EQUS_H__ */
