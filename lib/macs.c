#include "macs.h"
#include <stdio.h>
#include "names.h"
#include <stdlib.h>
#include <string.h>

struct macs_t *__macHead;
struct macs_t *__macTail;

void macInit(void) {
    __macHead = NULL;
    __macTail = NULL;
}

int macAdd(struct lines_t *ln) {
    char name[LINES_SIZE];
    uint8_t nsz;
    linesGetArg(ln,1,name,&nsz);
    // check for not integer name !!!
    if (namesAdd(name)) {
        printf("ERROR: MACRO <%s> already exist\r\n",name);
        return 1;
    }
    struct macs_t *tmp = (struct macs_t*)malloc(sizeof(struct macs_t));
    tmp->line = ln;
    tmp->next = NULL;
    if (__macTail == NULL) {
        __macHead = tmp;
        __macTail = tmp;
    } else {
        __macTail->next = tmp;
        __macTail = tmp;
    }
    return 0;
}

void macClean(void) {
    struct macs_t *x = __macHead;
    while (x != NULL) {
        struct macs_t *next = x->next;
        free(x);
        x = next;
    }
}

int macCutFromAsm(void) {
    struct macs_t *mc = __macHead;
    struct lines_t *ln,*lnt;
    char fw[LINES_SIZE];
    uint8_t fws;
    while (mc != NULL) {
        mc->line->szcmd = 0;
        ln = mc->line;
        // printf("MACRO line cutter : %s\r\n",ln->line);
        lnt = ln;
        int flag_find_endm = 1;
        while (flag_find_endm) {
            lnt = lnt->next;
            if (lnt != NULL) {
                linesGetFirstWord(lnt,fw,&fws);
                // printf("MACRO first word is %s\r\n",fw);
                if ((fws==5) && (strncmp(fw,".ENDM",fws) == 0)) {
                    flag_find_endm = 0;
                    ln->next = lnt->next;
                    lnt->szcmd = 0;
                }
                if ((fws==4) && (strncmp(fw,".MAC",fws) == 0)) {
                    printf("ERROR: <%s>[%d] MACRO in MACRO\r\n",ln->filename,ln->numLine);
                    return 1;
                }
            } else {
                printf("ERROR: <%s>[%d] MACRO without ENDM\r\n",ln->filename,ln->numLine);
                return 2;
            }
        }
        if (mc!=NULL) {mc = mc->next;}
    }
    return 0;
}

int macAddToAsm(void) {
    char fw[LINES_SIZE],fwm[LINES_SIZE];
    uint8_t fws,fwms;
    struct lines_t *ln = linesGetHead();
    struct lines_t *lnt = linesGetNALL();
    while (ln != NULL) {
        if (!(ln->szcmd)) { ln = ln->next; continue; }
        printf("line is %s\r\n",ln->line);
        linesGetFirstWord(ln,fw,&fws);
        if ((fws==5) && (strncmp(fw,".ENDM",fws) == 0) && (ln->szcmd != 0)) {
            printf("ERROR: <%s>[%d] ENDM without MACRO\r\n",ln->filename,ln->numLine);
            return 1;
        }
        // check in macro definisions
        struct macs_t *mc = __macHead;
        int macro_find=1;
        while (macro_find && (mc!= NULL)) {
            linesGetArg(mc->line,1,fwm,&fwms);
            if (fwms == fws) {
                if (strncmp(fw,fwm,fws)==0) {
                    printf("it is macro inserting %s\r\n",fwm);
                    macro_find=0;
                    ln->szcmd=0;
                    struct lines_t *ln1=mc->line->nall,*ln2=ln,*ln3;
                    while ((ln1 != NULL) && (ln1->szcmd != 0)) {
                        ln3 = linesInsert(ln2,ln1);
                        if (ln3 == NULL) {
                            printf("ERROR: MAC can not insert\r\n");
                            return 1;
                        }
                        ln2 = ln3;
                        ln1 = ln1->nall;
                    }
                }
            }
            mc = mc->next;
        }
        //
        ln = ln->next;
    }
    return 0;
}
