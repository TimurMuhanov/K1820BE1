#include "orgs.h"
#include <stdio.h>
#include "numbers.h"
#include "equs.h"
#include <stdlib.h>

struct orgs_t {
    struct lines_t *ln;
    struct orgs_t *next;
};

struct orgs_t *__global_orgs_head;
struct orgs_t *__global_orgs_tail;

void orgInit(void) {
    __global_orgs_head = NULL;
    __global_orgs_tail = NULL;
}

int orgAdd(struct lines_t *ln) {
    struct orgs_t *o = (struct orgs_t*)malloc(sizeof(struct orgs_t));
    o->ln = ln;
    o->next = NULL;
    if (__global_orgs_head == NULL) {
        __global_orgs_head = o;
        __global_orgs_tail = o;
    } else {
        __global_orgs_tail->next = o;
        __global_orgs_tail = o;
    }
}

int orgSetAddresses(void) {
    struct orgs_t *o = __global_orgs_head;
    while (o != NULL) {
        int adr;
        int err = numberTryGet(   o->ln->line + o->ln->argS, o->ln->argE - o->ln->argS, &adr, numberVoid);
        if (err) {
            err = equGet( o->ln->line + o->ln->argS, o->ln->argE - o->ln->argS, &adr);
            if (err) { return 1; }
        }
        o->ln->address = adr;
        o->ln->szcmd = 0;
        if (o->ln->next != NULL) {
            o->ln->next->address = adr;
        }
        struct orgs_t *t = o;
        o = o->next;
        __global_orgs_head = o;
        free(t);
    }
}

void orgClean(void) {
    while (__global_orgs_head != NULL) {
        struct orgs_t *t = __global_orgs_head;
        __global_orgs_head = __global_orgs_head->next;
        free(t);
    }
}