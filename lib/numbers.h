#ifndef __NUMBERS_H__
#define __NUMBERS_H__ 1

#include "lines.h"

typedef int(*fun_num_t)(char *c, int sz, int *ret);

struct numbers_t {
    int number;
    char action;
    struct numbers_t *next;
};

/*
@param 0x... hex
@param ...H hex
@param 0b... bin 
@param ...B bin
@param 0... oct
@param ...Q oct
@param ... dec
@param ...D dec
@return 0 - it is number, else - not
*/
int numberTryGet(char *c, int sz, int *num, fun_num_t external_function_for_unknown_name);

int numberVoid(char *c, int sz, int *num);

#endif /* __NUMBERS_H__ */
