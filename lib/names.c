#include "names.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define NAME_MAX 128

struct names_t {
    char name[NAME_MAX];
    uint8_t size;
    struct names_t *next;
    
};

struct names_t *__names_global;

void nameInit(void) {
    __names_global = NULL;
}

int nameCheckExist(char *c, int sz) {
    struct names_t *nm = __names_global;
    while (nm != NULL) {
        if ( (nm->size == sz) && (strncmp(nm->name,c,sz) == 0) ) { return 1; }
        nm = nm->next;
    }
    return 0;
}

int nameRightFormat(char *c, int sz) {
    // printf("\t\"%c\"\t",c[0]);
    if (!(((c[0] >= 'A') && (c[0]<='Z')) || (c[0] == '_'))) {
        return 1;
    }
    for (int i=1; i<sz; i++) {
        // printf("%c",c[i]);
        if (!(((c[i] >= 'A') && (c[i] <= 'Z')) || \
              ((c[i] >= '0') && (c[i] <= '9')) || \
               (c[i] == '_') || (c[i] == '.'))) {
            return 2;
        }
    }
    return 0;
}

int nameAdd(char *c, int sz) {
    struct names_t *nm = (struct names_t*)malloc(sizeof(struct names_t));
    if (nameCheckExist(c,sz)) { return 1; }
    if (nameRightFormat(c,sz)) { return 2; }
    strncpy(nm->name,c,sz);
    nm->size = sz;
    nm->next = __names_global;
    __names_global = nm;
    return 0;
}

void nameClean(void) {
    struct names_t *nm = __names_global;
    while (nm != NULL) {
        __names_global = nm->next;
        free(nm);
        nm = __names_global;
    }
}