#include "equs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numbers.h"
#include "names.h"

#define __EQU_NOT_READY 0
#define __EQU_READY 1
#define __EQU_PROCCESSING -1

struct equs_t {
    char *name;
    int name_sz;
    char *strnum;
    int strnum_sz;
    int number;
    int ready;
    struct equs_t *next;
    struct lines_t *ln;
};

struct equs_t *__equ_global_head;
struct equs_t *__equ_global_tail;

void equInit(void) {
    __equ_global_head = NULL;
    __equ_global_tail = NULL;
}

int equAdd(struct lines_t *ln) {
    char *args;
    uint8_t n,i=0,j=0;
    linesGetArgs(ln,&args,&n);
    // printf("equAdd : n=%d\r\n",n);
    while ((i<n) && (args[i] != '=')) { i++; }
    if (i>=n) { printf("ERROR : equAdd can not find '='\r\n"); return 1; }
    if (i == 0) { printf("ERROR : equAdd has no name '='\r\n"); return 2; }
    if ((n-i-1) == 0) { printf("ERROR : equAdd has no number '='\r\n"); return 3; }
    char name_for_add[LINES_SIZE];
    strncpy(name_for_add,args,i);
    int tmpi;
    if (!numberTryGet(args,i,&tmpi,numberVoid)) {
        printf("ERROR: equAdd <%s> it is number %d\r\n",args,tmpi);
        return 4;
    }
    if (nameAdd(name_for_add,i)) {
        printf("ERROR: equAdd <%s> already exist\r\n",args);
        return 5;
    }
    struct equs_t *t = (struct equs_t*)malloc(sizeof(struct equs_t));
    if (t == NULL) { printf("ERROR : equAdd can not malloc\r\n"); return 6; }
    t->name = args; t->name_sz = i;
    // printf("equAdd : size of name=%d arg=%d\r\n",i,n-i-1);
    t->strnum = &(args[i+1]); t->strnum_sz = n-i-1;
    t->ready = __EQU_NOT_READY; t->next = NULL; t->ln = ln;
    if (__equ_global_tail == NULL) {
        __equ_global_head = t;
        __equ_global_tail = t;
    } else {
        __equ_global_tail->next = t;
        __equ_global_tail = t;
    }
    return 0;
    // printf("equAdd do nothing\r\n");
}

int equResolverRecurcive(struct equs_t *eq);

int equResolverRecurciveByName(char *c, int sz, int *ret) {
    // printf("INFO : equResolverRecurciveByName was called\r\n");
    struct equs_t *eq = __equ_global_head;
    while (eq != NULL) {
        int n = eq->name_sz;
        // printf("\t");
        // for (int i=0;i<n;i++) { printf("%c",eq->name[i]); }
        // printf("\t%d\t%d\r\n",eq->number,eq->ready);
        if ((n==sz) && (strncmp(eq->name,c,n) == 0)) {
            if (eq->ready == __EQU_READY) { *ret = eq->number; return 0; }
            if (eq->ready == __EQU_PROCCESSING) { printf("ERROR EQU find loop %s\r\n",eq->name); return 1; }
            int err = equResolverRecurcive(eq);
            if (!err) { *ret = eq->number; return 0; }
            else { printf("ERROR EQU [get error %d] can not resolve %s\r\n",err,eq->name); return 2; }
        }
        eq = eq->next;
    }
    printf("ERROR EQU not found name ");
    for (int i=0;i<sz;i++) { printf("%c",c[i]); }
    printf("\r\n");
    return 3;
}

int equResolverRecurcive(struct equs_t *eq) {
    eq->ready = __EQU_PROCCESSING;
    int res;
    int err = numberTryGet(eq->strnum,eq->strnum_sz,&res,equResolverRecurciveByName);
    if (!err) {
        eq->number = res;
        eq->ready = __EQU_READY;
        // printf("INFO : equResolverRecurcive return number %d\r\n",res);
        return 0;
    }
    printf("ERROR EQU %d\r\n",err);
    return 1;
}

int equResolver(void) {
    // printf("INFO : equResolver start\r\n");
    struct equs_t *eq = __equ_global_head;
    int err;
    while (eq != NULL) {
        // printf("\r\n");
        if (eq->ready != __EQU_READY) {
            err = equResolverRecurcive(eq);
            if (err) {
                char c[LINES_SIZE];
                strncpy(c,eq->name,eq->name_sz);
                c[eq->name_sz] = 0;
                printf("ERROR : equResolver can not resolve %s=",c);
                strncpy(c,eq->strnum,eq->strnum_sz);
                c[eq->strnum_sz] = 0;
                printf("%s\r\n",c);
                return 1;
            } else {
                eq->ln->szcmd = 0;
            }
        } else {
            eq->ln->szcmd = 0;
        }
        eq = eq->next;
    }
    return 0;
}

void equClean(void) {
    struct equs_t *eq = __equ_global_head, *tmp;
    while (eq != NULL) {
        tmp = eq->next;
        free(eq);
        eq = tmp;
    }
}
