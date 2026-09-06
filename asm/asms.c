#include "asms.h"
#include <stdio.h>

int asmAssembly(fun_asm_t fun) {
    struct lines_t *head = linesGetHead();
    int asm_count, need_asm_count, err, first=1;
    while (1) {
        struct lines_t *ln = head;
        asm_count=0; need_asm_count=0;
        while (ln != NULL) {
            if (first) {
                printf("info : asm set first=0 %d\r\n",ln->address);
                first = 0;
                if (ln->address < 0) {
                    ln->address = 0;
                    printf("info : asm set first address\r\n");
                }
            }
            int not_rdy = 0;
            if (ln->szcmd < 0) {
                printf("size of word %d\r\n",ln->word1E - ln->word1S);
                if (ln->word1E - ln->word1S == 0) {
                    ln->szcmd = 0;
                } else {
                    not_rdy = fun(ln);
                    printf("asmAssembly error=%d\r\n",not_rdy);
                    if (not_rdy) {
                        need_asm_count++;
                    } else {
                        asm_count++;
                    }
                }
            }
            if (ln->next != NULL) {
                if (ln->next->address < 0) {
                    ln->next->address = ln->address;
                    printf("info : asm set next address\r\n");
                }
            }
            if (not_rdy) {
                ln->szcmd = -1;
            }
            ln = ln->next;
        }
        // printf("need_asm_count=%d, asm_count=%d\r\n",need_asm_count,asm_count);
        if (need_asm_count == 0) { return 0; }
        if (asm_count == 0) { return 1; }
    }
}
