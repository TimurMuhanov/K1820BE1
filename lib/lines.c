#include "lines.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "labels.h"

struct lines_list_t {
    struct lines_t *head;
    struct lines_t *nall;
    struct lines_t *next;
};

struct lines_list_t __lines_global;

void linesInit(void) {
    __lines_global.head = NULL;
    __lines_global.nall = NULL;
    __lines_global.next = NULL;
}

struct lines_t* linesPushBack(struct lines_t *ln) {
    struct lines_t *tmp = (struct lines_t*)malloc(sizeof(struct lines_t));
    if (tmp==NULL) {
        printf("ERROR : linesPushBack cannot add line\r\n");
        return NULL;
    }
    strcpy(tmp->filename,ln->filename);
    strcpy(tmp->line,ln->line);
    tmp->numLine = ln->numLine;
    tmp->next = NULL;
    tmp->nall = NULL;
    tmp->szcmd = -1 ; // not ready
    linesCutComment(tmp);
    linesHighCase(tmp);
    linesCutLabel(tmp);
    linesFindFirstWord(tmp);
    if (__lines_global.head == NULL) {
        __lines_global.head = tmp;
        __lines_global.nall = tmp;
        __lines_global.next = tmp;
    } else {
        __lines_global.nall->next = tmp;
        __lines_global.nall->nall = tmp;
        __lines_global.nall = tmp;
    }
    // printf("add to tail [%p]\r\n",__lines_global.tail);
    return tmp;
}

void linesClean(void) {
    struct lines_t *x = __lines_global.head, *t;
    while (x != NULL) {
        t = x->nall;
        // printf("delete [%p]\r\n",x);
        free(x);
        x = t;
    }
}

void linesPrint(void) {
    struct lines_t *x = __lines_global.head;
    while (x != NULL) {
        printf("<%s> [%d] {%d} \"%s\"\r\n",x->filename,x->numLine,x->szcmd,x->line);
        x = x->nall;
    }
}

void linesPrint4asm(void) {
    struct lines_t *x = __lines_global.head;
    while (x != NULL) {
        if (x->szcmd) {
            printf("<%s> [%d] {%d} \"%s\"\r\n",x->filename,x->numLine,x->szcmd,x->line);
        }
        x = x->next;
    }
}

void linesCutComment(struct lines_t *ln) {
    int i=0 , n=strlen(ln->line);
    while ((i<n) && (ln->line[i] != ';')) { i++; }
    ln->commentS = i;
}

void linesHighCase(struct lines_t *ln) {
    for (int i=0; i<ln->commentS; i++) {
        if ((ln->line[i] >= 'a') && (ln->line[i] <= 'z')) {
            ln->line[i] -= 'a'-'A';
        }
    }
}

void linesCutLabel(struct lines_t *ln) {
    int i=0, n=ln->commentS;
    while ((i<n) && (ln->line[i] != ':')) { i++; }
    if (i<n) {
        int j=0, k=i;
        int err = labelAdd(ln,&j,&k);
        if (err) {
            printf("linesCutLabel Error\r\n");
        } else {
            ln->word1S = i+1;
            ln->labelS = j;
            ln->labelE = k;
        }
    } else {
        ln->word1S = 0;
        ln->labelS = 0;
        ln->labelE = 0;
    }
}

int linesSkipSpaces(char *c, int s, int n) {
    // printf("linesSkipSpaces (line in) [");
    // for (int j=0; j<n; j++) { printf("%c",c[j]); }
    // printf("]\r\n");
    int i=s;
    while ((i<n) && ((c[i] == ' ') || (c[i] == '\t'))) { i++; }
    return i;
}

int linesSkipSymbols(char *c, int s, int n) {
    // printf("linesSkipSymbols (line in) [");
    // for (int j=0; j<n; j++) { printf("%c",c[j]); }
    // printf("]\r\n");
    int i=s;
    while ((i<n) && ((c[i] != ' ') && (c[i] != '\t'))) { i++; }
    return i;
}

void linesFindFirstWord(struct lines_t *ln) {
    // printf("start of 1st word is %d\r\n",ln->word1S);
    int a = linesSkipSpaces(ln->line, ln->word1S, ln->commentS);
    int b = linesSkipSymbols(ln->line, a, ln->commentS);
    ln->word1S = a;
    ln->word1E = b;
}

void linesGetFirstWord(struct lines_t *ln, char *w, uint8_t *n) {
    *n = ln->word1E - ln->word1S;
    strncpy(w,ln->line+ln->word1S, *n);
    w[*n]=0;
}

void linesGetArg(struct lines_t *ln, uint8_t n, char *w, uint8_t *sz) {
    int k=n, a, b=ln->word1E;
    // printf("full line : [%s]\r\n",ln->line);
    while (k) {
        a = linesSkipSpaces(ln->line, b, ln->commentS);
        b = linesSkipSymbols(ln->line, a, ln->commentS);
        // char t2[LINES_SIZE];
        // strncpy(t2,ln->line+a,b-a); t2[b-a]=0; printf("found word : [%s] a=%d b=%d\r\n",t2,a,b);
        k--;
    }
    if (b>a) {
        strncpy(w,ln->line+a,b-a);
        w[b-a]=0;
    }
    *sz = b-a;
}

struct lines_t* linesGetHead(void) {
    return __lines_global.head;
}

struct lines_t* linesGetNALL(void) {
    return __lines_global.nall;
}

struct lines_t* linesGetNext(void) {
    return __lines_global.next;
}

struct lines_t* linesInsert(struct lines_t *afterIt, struct lines_t *data) {
    struct lines_t *tmp = (struct lines_t*)malloc(sizeof(struct lines_t));
    if (tmp==NULL) {
        printf("ERROR : linesPushBack cannot add line\r\n");
        return NULL;
    }
    strcpy(tmp->filename,data->filename);
    strcpy(tmp->line,data->line);
    tmp->numLine = data->numLine;
    tmp->next = afterIt->next;
    tmp->nall = NULL;
    tmp->szcmd = -1 ; // not ready
    afterIt->next = tmp;
    __lines_global.nall->nall = tmp;
    __lines_global.nall = tmp;
    linesCutComment(tmp);
    linesHighCase(tmp);
    linesCutLabel(tmp);
    linesFindFirstWord(tmp);
    return tmp;
}
