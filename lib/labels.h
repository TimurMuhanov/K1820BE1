#ifndef __LABELS_H__
#define __LABELS_H__ 1

#include "lines.h"

void labelInit(void);

int labelAdd(struct lines_t *ln);

void labelClean(void);

int labelGet(char *c, int sz, int *ret);

void labelPrint(void);

#endif /* __LABELS_H__ */
