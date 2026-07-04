#ifndef __MACS_H__
#define __MAC_H__ 1

#include "lines.h"

struct macs_t
{
    struct lines_t *line;
    struct macs_t *next;
};

void macInit(void);

int macAdd(struct lines_t *ln);

void macClean(void);

int macCutFromAsm(void);
int macAddToAsm(void);

#endif /* __MAC_H__ */
