#include "names.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define NAME_MAX 128

struct names_t {
    char name[NAME_MAX];
    struct names_t *next;
    
};

struct names_t *__names_global;

void namesInit(void) {
    __names_global = NULL;
}

int namesCheckExist(char *c) {
    struct names_t *nm = __names_global;
    while (nm != NULL) {
        if (strcmp(nm->name,c) == 0) { return 1; }
        nm = nm->next;
    }
    return 0;
}

int namesAdd(char *c) {
    struct names_t *nm = (struct names_t*)malloc(sizeof(struct names_t));
    if (namesCheckExist(c)) { return 1; }
    strcpy(nm->name,c);
    nm->next = __names_global;
    __names_global = nm;
    return 0;
}

void namesClean(void) {
    struct names_t *nm = __names_global;
    while (nm != NULL) {
        __names_global = nm->next;
        free(nm);
        nm = __names_global;
    }
}