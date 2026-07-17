#include "macs.h"
#include <stdio.h>
#include "names.h"
#include <stdlib.h>
#include <string.h>
#include "numbers.h"

struct macs_t *__macHead;
struct macs_t *__macTail;

void macInit(void) {
    __macHead = NULL;
    __macTail = NULL;
}

int macAdd(struct lines_t *ln) {
    char *name;
    uint8_t nsz;
    int tmpi;
    linesGetArgs(ln,&name,&nsz);
    char name_for_add[LINES_SIZE];
    strncpy(name_for_add,name,nsz);
    if (!numberTryGet(name,nsz,&tmpi,(fun_num_t)numberVoid)) {
        printf("ERROR: MACRO <%s> it is number %d\r\n",name,tmpi);
        return 1;
    }
    if (nameAdd(name_for_add,nsz)) {
        printf("ERROR: MACRO <%s> already exist\r\n",name);
        return 2;
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
    char *fw;
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
                linesGetFirstWord(lnt,&fw,&fws);
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
    char *fw,*fwm;
    uint8_t fws,fwms;
    struct lines_t *ln = linesGetHead();
    struct lines_t *lnt = linesGetNALL();
    while (ln != NULL) {
        if (!(ln->szcmd)) { ln = ln->next; continue; }
        printf("line is %s\r\n",ln->line);
        linesGetFirstWord(ln,&fw,&fws);
        if ((fws==5) && (strncmp(fw,".ENDM",fws) == 0) && (ln->szcmd != 0)) {
            printf("ERROR: <%s>[%d] ENDM without MACRO\r\n",ln->filename,ln->numLine);
            return 1;
        }
        // check in macro definisions
        struct macs_t *mc = __macHead;
        int macro_find=1;
        while (macro_find && (mc!= NULL)) {
            linesGetArgs(mc->line,&fwm,&fwms);
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
