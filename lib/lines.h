#ifndef __LINES_H__
#define __LINES_H__ 1

#include <stdint.h>

#define LINES_SIZE 64
#define FILENAME_SIZE 32

struct lines_t {
    char line[LINES_SIZE];
    char filename[FILENAME_SIZE];
    int8_t labelS,labelE,word1S,word1E,commentS,argS,argE,szcmd;
    int16_t numCmd;
    uint32_t cmd;
    int16_t numLine,address;
    struct lines_t *nall;
    struct lines_t *next;
};

void linesInit(void);
struct lines_t* linesPushBack(struct lines_t *ln);
void linesClean(void);
void linesPrint(void);
void linesPrint4asm(void);
void linesCutComment(struct lines_t *ln);
void linesHighCase(struct lines_t *ln);
int linesCutLabel(struct lines_t *ln);
void linesFindFirstWord(struct lines_t *ln);
void linesGetFirstWord(struct lines_t *ln, char **w, uint8_t *n);
void linesFindArgs(struct lines_t *ln);
void linesGetArgs(struct lines_t *ln, char **w, uint8_t *sz);
struct lines_t* linesGetHead(void);
struct lines_t* linesGetNALL(void);
struct lines_t* linesGetNext(void);
struct lines_t* linesInsert(struct lines_t *afterIt, struct lines_t *data);

#endif /* __LINES_H__ */
