#include "files.h"
#include <stdio.h>
#include <string.h>
#include "names.h"
#include "macs.h"
#include "equs.h"
#include "orgs.h"

int fileRecursive(char *filename) {
    if (namesAdd(filename)) {
        printf("ERROR : <%s> - this file open already\r\n",filename);
        return 1;
    }
    // printf("try to open %s file\r\n",filename);
    FILE *f = fopen(filename,"r");
    if (f==NULL) {
        printf("ERROR : <%s> - cannot be open\r\n",filename);
        return 2;
    }
    // printf("file %s was opened successfully\r\n",filename);
    char line[LINES_SIZE];
    char tmp_word[LINES_SIZE];
    char tmp_arg[LINES_SIZE];
    int line_count=1;
    uint8_t tmp_word_len,tmp_arg_len;
    while (fgets(line, sizeof(line), f) != NULL) {
        int n = strlen(line)-1;
        while ((line[n] == '\r') || (line[n] == '\n')) { line[n] = 0; n--; }
        struct lines_t tmp_line;
        strcpy(tmp_line.filename,filename);
        strcpy(tmp_line.line,line);
        tmp_line.numLine = line_count;
        struct lines_t *tmp_real = linesPushBack(&tmp_line);
        linesGetFirstWord(tmp_real,tmp_word,&tmp_word_len);
        linesGetArg(tmp_real,1,tmp_arg,&tmp_arg_len);
        // printf("line is %d \"%s\", 1st word=%s, arg=%s [%d]\r\n",line_count,line,tmp_word,tmp_arg,tmp_arg_len);
        if (tmp_word_len) {
            if ((tmp_word_len == 4) && (strncmp(tmp_word,".INC", tmp_word_len) == 0)) {
                if (tmp_arg_len) {
                    // printf("open file : %s ...\r\n",tmp_word);
                    if (fileRecursive(tmp_arg)) {
                        printf("ERROR : <%s>[%d] - in include file\r\n",filename,line_count);
                        return 3;
                    } else {
                        tmp_real->szcmd = 0;
                    }
                } else {
                    printf("ERROR : <%s>[%d] - .INC without filename\r\n",filename,line_count);
                    return 4;
                }
            }
            if ((tmp_word_len == 4) && (strncmp(tmp_word,".MAC", tmp_word_len) == 0)) {
                if (tmp_arg_len) {
                    if (macAdd(tmp_real)) {
                        printf("ERROR : <%s>[%d]\r\n",filename,line_count);
                        return 5;
                    }
                } else {
                    printf("ERROR : <%s>[%d] - .MAC without name\r\n",filename,line_count);
                    return 6;
                }
            }
            if ((tmp_word_len == 4) && (strncmp(tmp_word,".EQU", tmp_word_len) == 0)) {
                if (tmp_arg_len) {
                    equAdd(tmp_real);
                } else {
                    printf("ERROR : <%s>[%d] - .EQU without name\r\n",filename,line_count);
                    return 8;
                }
            }
            if ((tmp_word_len == 4) && (strncmp(tmp_word,".ORG", tmp_word_len) == 0)) {
                if (tmp_arg_len) {
                    orgAdd(tmp_real);
                } else {
                    printf("ERROR : <%s>[%d] - .ORG without name\r\n",filename,line_count);
                    return 10;
                }
            }
        }
        line_count++;
    }
    // printf("close file <%s> ... \r\n",filename);
    fclose(f);
}

int filesRead(char *filename) {
    linesInit();
    namesInit();
    macInit();
    equInit();
    orgInit();
    if (fileRecursive(filename)) {
        namesClean();
        printf("ERROR : <%s> - in include file\r\n",filename);
        return 1;
    }
    // printf("files was opened successfully\r\n");
    namesClean();
    return 0;
}

int fileWrite(void) {
    printf("fileWrite does not work yet\r\n");
}
