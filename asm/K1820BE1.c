#include "K1820BE1.h"
#include "../lib/equs.h"
#include "../lib/numbers.h"
#include "../lib/labels.h"
#include <string.h>
#include <stdio.h>

struct K1820BE1_t {
    char name[8];
    int code;
    int high; // if non zero ---> instruction have 2 byte ; else 1
    int mask; // if non zero ---> it has argument(s), which set according to this mask
    char op;  // type of argument(s) : 0-3 , y=0-15 , a=0-mask , r=0-3, d --- "r,d" r=0-3, d=0-15
};

const struct K1820BE1_t K1820BE1_instructions[] = {
    { .name = "ASC",   .code = 0x30, .high=0x0,  .mask=0,     .op=0   }, // 0
    { .name = "ADD",   .code = 0x31, .high=0x0,  .mask=0,     .op=0   }, // 1
    { .name = "ADT",   .code = 0x4a, .high=0x0,  .mask=0,     .op=0   }, // 2
    { .name = "AISC",  .code = 0x50, .high=0x0,  .mask=0xf,   .op='y' }, // 3
    { .name = "CASC",  .code = 0x10, .high=0x0,  .mask=0,     .op=0   }, // 4
    { .name = "CLRA",  .code = 0x00, .high=0x0,  .mask=0,     .op=0   }, // 5
    { .name = "COMP",  .code = 0x40, .high=0x0,  .mask=0,     .op=0   }, // 6
    { .name = "NOP",   .code = 0x44, .high=0x0,  .mask=0,     .op=0   }, // 7
    { .name = "RC",    .code = 0x32, .high=0x0,  .mask=0,     .op=0   }, // 8
    { .name = "SC",    .code = 0x22, .high=0x0,  .mask=0,     .op=0   }, // 9
    { .name = "XOR",   .code = 0x02, .high=0x0,  .mask=0,     .op=0   }, // 10
    { .name = "JID",   .code = 0xff, .high=0x0,  .mask=0,     .op=0   }, // 11
    { .name = "JMP",   .code = 0x00, .high=0x60, .mask=0x3ff, .op='a' }, // 12
    { .name = "JP",    .code = 0x80, .high=0x0,  .mask=0x7f,  .op='a' }, // 13 spec f
    { .name = "JSRP",  .code = 0x80, .high=0x0,  .mask=0x3f,  .op='a' }, // 14 spec f
    { .name = "JSR",   .code = 0x00, .high=0x68, .mask=0x3ff, .op='a' }, // 15
    { .name = "RET",   .code = 0x48, .high=0x0,  .mask=0,     .op=0   }, // 16
    { .name = "RETSK", .code = 0x49, .high=0x0,  .mask=0,     .op=0   }, // 17
    { .name = "CAMQ",  .code = 0x3c, .high=0x33, .mask=0,     .op=0   }, // 18
    { .name = "CQMA",  .code = 0x2c, .high=0x33, .mask=0,     .op=0   }, // 19
    { .name = "LD",    .code = 0x05, .high=0x0,  .mask=0x30,  .op='r' }, // 20
    { .name = "LDD",   .code = 0x00, .high=0x23, .mask=0x3f,  .op='d' }, // 21
    { .name = "LQID",  .code = 0xbf, .high=0x0,  .mask=0,     .op=0   }, // 22
    { .name = "RMB",   .code = 0x4c, .high=0x0,  .mask=0,     .op='0' }, // 23
    { .name = "RMB",   .code = 0x45, .high=0x0,  .mask=0,     .op='1' }, // 24
    { .name = "RMB",   .code = 0x42, .high=0x0,  .mask=0,     .op='2' }, // 25
    { .name = "RMB",   .code = 0x43, .high=0x0,  .mask=0,     .op='3' }, // 26
    { .name = "SMB",   .code = 0x4d, .high=0x0,  .mask=0,     .op='0' }, // 27
    { .name = "SMB",   .code = 0x47, .high=0x0,  .mask=0,     .op='1' }, // 28
    { .name = "SMB",   .code = 0x46, .high=0x0,  .mask=0,     .op='2' }, // 29
    { .name = "SMB",   .code = 0x4b, .high=0x0,  .mask=0,     .op='3' }, // 30
    { .name = "STII",  .code = 0x70, .high=0x0,  .mask=0xf,   .op='y' }, // 31
    { .name = "X",     .code = 0x06, .high=0x0,  .mask=0x30,  .op='r' }, // 32
    { .name = "XAD",   .code = 0x80, .high=0x23, .mask=0x3f,  .op='d' }, // 33
    { .name = "XDS",   .code = 0x07, .high=0x0,  .mask=0x30,  .op='r' }, // 34
    { .name = "XIS",   .code = 0x04, .high=0x0,  .mask=0x30,  .op='r' }, // 35
    { .name = "CAB",   .code = 0x50, .high=0x0,  .mask=0,     .op=0   }, // 36
    { .name = "CBA",   .code = 0x4e, .high=0x0,  .mask=0,     .op=0   }, // 37
    { .name = "LBI",   .code = 0x00, .high=0x0,  .mask=0,     .op='d' }, // 38 spec f
    { .name = "LEI",   .code = 0x60, .high=0x33, .mask=0xf,   .op='y' }, // 39
    { .name = "XABR",  .code = 0x12, .high=0x0,  .mask=0,     .op=0   }, // 40
    { .name = "SKC",   .code = 0x20, .high=0x0,  .mask=0,     .op=0   }, // 41
    { .name = "SKE",   .code = 0x21, .high=0x0,  .mask=0,     .op=0   }, // 42
    { .name = "SKGZ",  .code = 0x21, .high=0x33, .mask=0,     .op=0   }, // 43
    { .name = "SKGBZ", .code = 0x01, .high=0x33, .mask=0,     .op='0' }, // 44
    { .name = "SKGBZ", .code = 0x11, .high=0x33, .mask=0,     .op='1' }, // 45
    { .name = "SKGBZ", .code = 0x03, .high=0x33, .mask=0,     .op='2' }, // 46
    { .name = "SKGBZ", .code = 0x13, .high=0x33, .mask=0,     .op='3' }, // 47
    { .name = "SKMBZ", .code = 0x01, .high=0x0,  .mask=0,     .op='0' }, // 48
    { .name = "SKMBZ", .code = 0x11, .high=0x0,  .mask=0,     .op='1' }, // 49
    { .name = "SKMBZ", .code = 0x03, .high=0x0,  .mask=0,     .op='2' }, // 50
    { .name = "SKMBZ", .code = 0x13, .high=0x0,  .mask=0,     .op='3' }, // 51
    { .name = "SKT",   .code = 0x41, .high=0x0,  .mask=0,     .op=0   }, // 52
    { .name = "ING",   .code = 0x2a, .high=0x33, .mask=0,     .op=0   }, // 53
    { .name = "ININ",  .code = 0x28, .high=0x33, .mask=0,     .op=0   }, // 54
    { .name = "INIL",  .code = 0x29, .high=0x33, .mask=0,     .op=0   }, // 55
    { .name = "INL",   .code = 0x2e, .high=0x33, .mask=0,     .op=0   }, // 56
    { .name = "OBD",   .code = 0x3e, .high=0x33, .mask=0,     .op=0   }, // 57
    { .name = "OGI",   .code = 0x50, .high=0x33, .mask=0,     .op=0   }, // 58
    { .name = "OMG",   .code = 0x3a, .high=0x33, .mask=0,     .op=0   }, // 59
    { .name = "XAS",   .code = 0x4f, .high=0x0,  .mask=0,     .op=0   }  // 60
};

int K1820BE1DecodeInstruction(struct lines_t *ln) {
    printf("info : asm (1) \"%s\"\r\n",ln->line);
    int n=sizeof(K1820BE1_instructions)/sizeof(struct K1820BE1_t);
    int i=0, sz=(ln->word1E - ln->word1S);
    char *c = ln->line + ln->word1S;
    while (i<n) {
        if ((sz==strlen(K1820BE1_instructions[i].name)) \
        && (strncmp(c,K1820BE1_instructions[i].name,sz) == 0)) {
            break;
        }
        i++;
    }
    if (i>=n) { return 1; }
    // printf("info : asm (2) \"%s\"\r\n",K1820BE1_instructions[i].name);
    ln->szcmd = 1;
    if (K1820BE1_instructions[i].high) { ln->szcmd++; }
    ln->cmd = (((uint32_t)K1820BE1_instructions[i].high)<<8) | (K1820BE1_instructions[i].code);
    int mask=K1820BE1_instructions[i].mask;
    int arg1,arg2,err;
    if (K1820BE1_instructions[i].op) {
        printf("info : asm (3) it is need arg\r\n");
        if (K1820BE1_instructions[i].op == 'd') { // find ',' and get arg1 and arg2
            int j=ln->argS, k=-1;
            while ((k<0) && (j< ln->argE)) {
                if (ln->line[j] == ',') { break; }
                j++;
            }
            err = numberTryGet(ln->line + ln->argS, j- ln->argS, &arg1, numberVoid);
            if (err) { err = equGet(ln->line + ln->argS, j- ln->argS, &arg1); }
            if (err) { err = labelGet(ln->line + ln->argS, j- ln->argS, &arg1); }
            if (err) { return 2; }
            if ((arg1<0) || (arg1>3)) { return 3; }
            err = numberTryGet(ln->line + j + 1, ln->argE - j - 1, &arg2, numberVoid);
            if (err) { err = equGet(ln->line + j + 1, ln->argE - j - 1, &arg2); }
            if (err) { err = labelGet(ln->line + j + 1, ln->argE - j - 1, &arg2); }
            if (err) { return 4; }
            if ((arg2<0) || (arg2>15)) { return 5; }
            if (i==38) { // LBI
                if ((arg2 == 0) || (arg2 > 8)) {
                    ln->szcmd = 1;
                    ln->cmd = arg1<<4 | ((arg2-1)&0xf);
                } else {
                    ln->szcmd = 2;
                    ln->cmd = 0x3380 | (arg1<<4) | arg2;
                }
            } else {
                ln->cmd |= (arg1<<4) | arg2;
            }
        } else { // try to get arg1
            err = numberTryGet(ln->line + ln->argS, ln->argE - ln->argS, &arg1, numberVoid);
            if (err) { err = equGet(ln->line + ln->argS, ln->argE - ln->argS, &arg1); }
            if (err) { err = labelGet(ln->line + ln->argS, ln->argE - ln->argS, &arg1); }
            if (err) { return 6; }
            if (arg1<0) { return 7; }
            if (i == 13) { // JP
                if ((ln->address < 0x80) || (ln->address >= 0x100)) {
                    mask >>= 1;
                }
                if ((arg1&(~mask)) != (ln->address&(~mask))) {
                    return 8;
                }
                ln->cmd |= (arg1&mask);
            } else {
                if (i == 14) { // JSRP
                    if ((ln->address >= 0x80) || (ln->address < 0x100)) {
                        return 9;
                    }
                    if ((arg1 >= 0x80) || (arg1 < 0xff)) {
                        return 10;
                    }
                    ln->cmd |= (arg1&mask);
                } else {
                    if ((K1820BE1_instructions[i].op >= '0')\
                    && (K1820BE1_instructions[i].op <= '3')) {
                        if (arg1 > 3) {
                            return 11;
                        } else {
                            i += arg1;
                            ln->cmd = K1820BE1_instructions[i].code;
                        }
                    } else {
                        if (K1820BE1_instructions[i].op == 'r') {
                            if (arg1>3) {
                                return 12;
                            } else {
                                ln->cmd |= (arg1<<4);
                            }
                        } else { // a or y no special functions
                            if (arg1 > K1820BE1_instructions[i].mask) {
                                return 13;
                            } else {
                                ln->cmd |= arg1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (ln->szcmd == 1) {
        printf("info : asm (4) addr=0x%03x code=0x%02x\r\n",ln->address, ln->cmd);
        if (ln->next != NULL) {
            ln->next->address = ln->address + ln->szcmd;
        }
        return 0;
    }
    if (ln->szcmd == 2) {
        printf("info : asm (4) addr=0x%03x code=0x%04x\r\n",ln->address, ln->cmd);
        if (ln->next != NULL) {
            ln->next->address = ln->address + ln->szcmd;
        }
        return 0;
    }
    return 14;
}
