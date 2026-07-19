#include "labels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct labels_t {
    struct lines_t *ln;
    struct labels_t *next;
};

struct labels_t *__labels_global_head;
struct labels_t *__labels_global_tail;

void labelInit(void) {
    __labels_global_head = NULL;
    __labels_global_tail = NULL;
}

int labelAdd(struct lines_t *ln) {
    struct labels_t *lb = (struct labels_t*)malloc(sizeof(struct labels_t));
    if (lb == NULL) { return 1; }
    lb->ln = ln;
    lb->next = NULL;
    if (__labels_global_head == NULL) {
        __labels_global_head = lb;
        __labels_global_tail = lb;
    } else {
        __labels_global_tail->next = lb;
        __labels_global_tail = lb;
    }
    return 0;
}

void labelClean(void) {
    struct labels_t *lb = __labels_global_head;
    while (lb != NULL) { 
        struct labels_t *lbn = lb->next;
        free(lb);
        lb = lbn;
    }
}

int labelGet(char *c, int sz, int *ret) {
    struct labels_t *lb = __labels_global_head;
    int err;
    while (lb != NULL) {
        int n = lb->ln->labelE - lb->ln->labelS;
        if ((n==sz) && (strncmp(lb->ln->line + lb->ln->labelS,c,n) == 0)) {
            *ret = lb->ln->address;
            return 0;
        }
        lb = lb->next;
    }
    return 1;
}

void labelPrint(void) {
    struct labels_t *lb = __labels_global_head;
    while (lb != NULL) {
        for (int i=lb->ln->labelS; i<lb->ln->labelE; i++) {
            printf("%c",lb->ln->line[i]);
        }
        printf(" - 0x%03x\r\n",lb->ln->address);
        lb = lb->next;
    }
}
