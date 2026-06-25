#include "files.h"
#include <stdio.h>
#include <string.h>
#include "names.h"

int fileRecursive(char *filename) {
    if (namesAdd(filename)) {
        printf("ERROR : <%s> - this file open already\r\n",filename);
        return 1;
    }
    FILE *f = fopen(filename,"r");
    if (f==NULL) {
        printf("ERROR : <%s> - cannot be open\r\n",filename);
        return 2;
    }
    char line[LINES_SIZE];
    char tmp_word[LINES_SIZE];
    int line_count=1;
    int tmp_len;
    while (fgets(line, sizeof(line), f) != NULL) {
        int n = strlen(line)-1;
        while ((line[n] == '\r') || (line[n] == '\n')) { line[n] = 0; n--; }
        struct lines_t tmp_line;
        strcpy(tmp_line.filename,filename);
        strcpy(tmp_line.line,line);
        tmp_line.line_start = 0;
        tmp_line.line_end = strlen(line);
        tmp_line.line_count = line_count;
        linesCutComment(&tmp_line);
        linesCutLabel(&tmp_line);
        int it_was_include=0;
        if (linesGetWord(&tmp_line,1,tmp_word)) {
            tmp_len = strlen(tmp_word);
            if ((tmp_len == 4) && (strncmp(tmp_word,".INC",4) == 0)) {
                if (linesGetWord(&tmp_line,2,tmp_word)) {
                    // printf("open file : %s ...\r\n",tmp_word);
                    if (fileRecursive(tmp_word)) {
                        printf("ERROR : <%s>[%d] - in include file\r\n",filename,line_count);
                        return 3;
                    } else {
                        it_was_include=1;
                    }
                } else {
                    printf("ERROR : <%s>[%d] - .INC without filename\r\n",filename,line_count);
                    return 4;
                }
            }
        }
        if (!it_was_include) { linesPushBack(&tmp_line); }
        line_count++;
    }
    // printf("close file <%s> ... \r\n",filename);
    fclose(f);
}

int filesRead(char *filename) {
    linesInit();
    namesInit();
    if (fileRecursive(filename)) {
        namesClear();
        printf("ERROR : <%s> - in include file\r\n",filename);
        return 1;
    }
    // printf("files was opened successfully\r\n");
    namesClear();
    return 0;
}

int fileWrite(void) {
    printf("fileWrite does not work yet\r\n");
}