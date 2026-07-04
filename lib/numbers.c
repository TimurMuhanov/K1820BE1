#include "numbers.h"
#include <string.h>


int numbersGet(char *c, int *n) {
    int h=0,q=0,b=0,d=0,f=0,st=0,se=strlen(c);
    if (se<1) { return 1; }
    if (se<2) { d=1; f=1; }
    if (c[se-1]=='H') { h=1; f=2; }
    if (c[se-1]=='Q') { q=1; f=2; }
    if ((!f)&&(c[0] == '0')) {
        if (c[1]=='X') { h=1; f=1; st=2; }
        if (c[1]=='B') { b=1; f=1; st=2; }
    }
    if (c[se-1]=='Q') { b=1; f=2; }
    if (c[se-1]=='D') { d=1; f=2; }
    if ((!f)&&(c[0] == '0')) { q=1; f=1; }
    if (!f) { d=1; f=1; }
    if (f==2) { se--; }
    int t=0;
    for (int i=st; i<se; i++) {
        if (c[i]<'0') { return 2; }
        if (b) {
            if (c[i]>'1') { return 3; }
            t <<= 1; t |= c[i]-'0';
        }
        if (q) {
            if (c[i]>'7') { return 4; }
            t <<= 3; t |= c[i]-'0';
        }
        if (d) {
            if (c[i]>'9') { return 5; }
            t *= 10; t += c[i]-'0';
        }
        if (h) {
            if (c[i]>'9') {
                if ((c[i]<'A') || (c[i]>'F')) { return 6; }
                t <<= 4; t |= c[i]-'A'+10;
            } else {
                t <<= 4; t |= c[i]-'0';
            }
        }
    }
    *n = t;
    return 0;
}
