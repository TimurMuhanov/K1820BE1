#ifndef __NUMBERS_H__
#define __NUMBERS_H__ 1

/* @param c : 
    0x... , ...H --- hex
    0b... , ...B --- bin
    0... , ...Q --- oct
    ... , ...D --- dec
    @return 0 - it is number, else - not
*/
int numbersGet(char *c, int *num);

#endif /* __NUMBERS_H__ */
