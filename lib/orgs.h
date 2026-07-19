#ifndef __ORGS_H__
#define __ORGS_H__ 1

#include "lines.h"

void orgInit(void);

int orgAdd(struct lines_t *ln);

int orgSetAddresses(void);

void orgClean(void);

#endif /* __ORGS_H__ */
