#ifndef __EQUS_H__
#define __EQUS_H__ 1

#include "lines.h"

void equInit(void);

// @return 0 - ok, else - errors
int equAdd(struct lines_t *ln);

// @return 0 - ok, else - errors
int equResolver(void);

void equClean(void);

// @return 1 - found, 0 - not found
void equGetNumber(char *name, int st, int se, int *number);

#endif /* __EQUS_H__ */
