#ifndef __LINES_H__
#define __LINES_H__ 1

#define LINES_SIZE 128

struct lines_t {
    char filename[LINES_SIZE];
    char line[LINES_SIZE];
    char com[LINES_SIZE];
    char label[LINES_SIZE];
    int line_count, line_start, line_end;
    struct lines_t *next;
    struct lines_t *prev;
};

void linesInit(void);
int linesPushBack(struct lines_t *ln);
void linesClear(void);
void linesPrint(void);
void linesCutComment(struct lines_t *ln);
void linesCutLabel(struct lines_t *ln);
// @return 1 - found, 0 - not
int linesGetWord(struct lines_t *ln, int n, char *cout);

#endif /* __LINES_H__ */
