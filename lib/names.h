#ifndef __NAMES_H__
#define __NAMES_H__ 1

void nameInit(void);

int nameAdd(char *c, int sz);

void nameClean(void);

// @return 0 - ok
int nameRightFormat(char *c, int sz);

#endif /* __NAMES_H__ */
