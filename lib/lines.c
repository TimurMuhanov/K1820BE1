#include "lines.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct lines_list_t {
    struct lines_t *head;
    struct lines_t *tail;
};

struct lines_list_t __lines_global;

void linesInit(void) {
    __lines_global.head = NULL;
    __lines_global.tail = NULL;
}

int linesPushBack(struct lines_t *ln) {
    struct lines_t *tmp = (struct lines_t*)malloc(sizeof(struct lines_t));
    if (tmp==NULL) {
        printf("ERROR : linesPushBack cannot add line\r\n");
        return 1;
    }
    strcpy(tmp->filename,ln->filename);
    strcpy(tmp->line,ln->line);
    strcpy(tmp->com,ln->com);
    strcpy(tmp->label,ln->label);
    tmp->line_count = ln->line_count;
    tmp->line_start = ln->line_start;
    tmp->line_end = ln->line_end;
    tmp->next = NULL;
    tmp->prev = NULL;
    if (__lines_global.head == NULL) {
        __lines_global.head = tmp;
        __lines_global.tail = tmp;
    } else {
        __lines_global.tail->next = tmp;
        tmp->prev = __lines_global.tail;
        __lines_global.tail = tmp;
    }
    // printf("add to tail [%p]\r\n",__lines_global.tail);
    return 0;
}

void linesClear(void) {
    struct lines_t *x = __lines_global.head, *t;
    while (x != NULL) {
        t = x->next;
        // printf("delete [%p]\r\n",x);
        free(x);
        x = t;
    }
}

void linesPrint(void) {
    struct lines_t *x = __lines_global.head;
    while (x != NULL) {
        printf("<%s> [%d] \"%s\"\r\n",x->filename,x->line_count,x->line);
        x = x->next;
    }
}

void linesCutComment(struct lines_t *ln) {
    int i = 0;
    while ((i<ln->line_end) && (ln->line[i] != ';')) { i++; }
    if (i<ln->line_end) {
        strncpy(ln->com,ln->line + i, ln->line_end - i);
        ln->com[ln->line_end - i] = 0;
        ln->line_end = i;
    }
}

void linesCutLabel(struct lines_t *ln) {
    int i = 0;
    while ((i<ln->line_end) && (ln->line[i] != ':')) { i++; }
    if (i<ln->line_end) {
        strncpy(ln->label, ln->line , i);
        ln->label[i] = 0;
        ln->line_start = i+1;
    }
}

int linesSkipSpaces(char *c, int n) {
    // printf("linesSkipSpaces (line in) [");
    // for (int j=0; j<n; j++) { printf("%c",c[j]); }
    // printf("]\r\n");
    int i=0;
    while ((i<n) && ((c[i] == ' ') || (c[i] == '\t'))) { i++; }
    return i;
}

int linesSkipSymbols(char *c, int n) {
    // printf("linesSkipSymbols (line in) [");
    // for (int j=0; j<n; j++) { printf("%c",c[j]); }
    // printf("]\r\n");
    int i=0;
    while ((i<n) && ((c[i] != ' ') && (c[i] != '\t'))) { i++; }
    return i;
}

int linesGetWord(struct lines_t *ln, int n, char *cout) {
    int k=n, a, b=ln->line_start;
    // printf("full line : [%s]\r\n",ln->line);
    while (k) {
        a = linesSkipSpaces(ln->line + b, ln->line_end - b) + b;
        b = linesSkipSymbols(ln->line + a, ln->line_end - a) + a;
        // char t2[LINES_SIZE];
        // strncpy(t2,ln->line+a,b-a); t2[b-a]=0; printf("found word : [%s] a=%d b=%d\r\n",t2,a,b);
        k--;
    }
    if (b>a) {
        strncpy(cout,ln->line+a,b-a);
        cout[b-a]=0;
        return 1;
    }
    return 0;
}
