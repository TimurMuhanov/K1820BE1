#include "numbers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int numberGet(char *c, int st, int se, int *n,fun_num_t external_function_for_unknown_name) {
    // printf("INFO : numberGet receive \"");
    // for (int i=st;i<se;i++) {
    //     printf("%c",c[i]);
    // }
    // printf("\" st=%d se=%d\r\n",st,se);
    int h=0,q=0,b=0,d=0,f=0;
    if ((se-st)<1) { return 1; }
    if ((se-st)<2) { d=1; f=1; }
    if (c[st+se-1]=='H') { h=1; f=2; }
    if (c[st+se-1]=='Q') { q=1; f=2; }
    if ((!f)&&(c[st+0] == '0')&&(se-st>2)) {
        if (c[st+1]=='X') { h=1; f=1; st+=2; }
        if (c[st+1]=='B') { b=1; f=1; st+=2; }
    }
    // printf("%c\r\n",c[se-1]);
    if (c[se-1]=='B') { b=1; f=2; }
    if (c[se-1]=='D') { d=1; f=2; }
    if ((!f)&&(c[st+0] == '0')) { q=1; f=1; }
    if (!f) { d=1; f=1; }
    if (f==2) { se--; }
    // printf("INFO : numberGet  h=%d,q=%d,b=%d,d=%d,f=%d,st=%d,se=%d\r\n",h,q,b,d,f,st,se);
    int t=0;
    for (int i=st; i<se; i++) {
        if (c[i]<'0') { return 2; }
        if (b) {
            if (c[i]>'1') { return 3; }
            t <<= 1; t |= c[i]-'0';
        }
        if (q) {
            if (c[i]>'7') { return 4; }
            t <<= 3; t |= c[i]-'0';
        }
        if (d) {
            if (c[i]>'9') { return 5; }
            t *= 10; t += c[i]-'0';
        }
        if (h) {
            if (c[i]>'9') {
                if ((c[i]<'A') || (c[i]>'F')) { return 6; }
                t <<= 4; t |= c[i]-'A'+10;
            } else {
                t <<= 4; t |= c[i]-'0';
            }
        }
    }
    *n = t;
    // printf("INFO : numberGet it is number %d\r\n",t);
    return 0;
}

int numberAddNum(struct numbers_t **tail, int number) {
    struct numbers_t *t = (struct numbers_t*)malloc(sizeof(struct numbers_t));
    if (t == NULL) { return 1; }
    t->number = number;
    t->action = '.';
    t->next = NULL;
    if (*tail == NULL) { *tail = t; }
    else {
        (*tail)->next = t;
        *tail = t;
    }
    return 0;
}

int numberGetNum(char *c, int *st, int se, struct numbers_t **ns,fun_num_t external_function_for_unknown_name) {
    int i=*st, tmp;
    while ((i<se) && ((c[i]>='0') && (c[i]<='9') || (c[i]>='A') && (c[i]<='Z'))) {
        i++;
    }
    if (i==*st) { printf("error: number not found\r\n"); return 1; }
    int err = numberGet(c,*st,i,&tmp,external_function_for_unknown_name);
    if (err) {
        int err2 = external_function_for_unknown_name(c+(*st),i-(*st),&tmp);
        if (err2) {
            // printf("error: numberGet return %d\r\n",err);
            return 2;
        }
        err=err2;
    }
    *st=i;
    // printf("INFO : numberGetNum 1 err=%d\r\n",err);
    err = numberAddNum(ns,tmp);
    // printf("INFO : numberGetNum 2 err=%d\r\n",err);
    if (err) {
        // printf("error: numberAddNum return %d\r\n",err);
        return 3;
    }
    return 0;
}

void numberClean(struct numbers_t *head) {
    struct numbers_t *t = head;
    // printf("INFO : numberClean 1\r\n");
    while (head != NULL) {
        t = head->next;
        free(head);
        head = t;
    }
    // printf("INFO : numberClean 2\r\n");
}

void numberPrint(struct numbers_t *ns) {
    struct numbers_t *t = ns;
    while (t != NULL) {
        printf("%d \"%c\" [%p]\r\n",t->number,t->action,t);
        t = t->next;
    }
}

int numberAddChar(struct numbers_t *tail, char action) {
    if (tail == NULL) { return 1; }
    if (tail->action != '.') { return 2; }
    tail->action = action; return 0;
}

int numberOneAction(struct numbers_t *ns) {
    if (ns->next == NULL) {
        // printf("error : numberOneAction\r\n");
        return 1;
    }
    struct numbers_t *t = ns->next;
    if (ns->action == '*') { ns->number = ns->number * ns->next->number; }
    if (ns->action == '/') { ns->number = ns->number / ns->next->number; }
    if (ns->action == '+') { ns->number = ns->number + ns->next->number; }
    if (ns->action == '-') { ns->number = ns->number - ns->next->number; }
    ns->action = t->action;
    ns->next = t->next;
    free(t);
    return 0;
}

void numberPrintSubLine(struct numbers_t *head) {
    struct numbers_t *nm = head;
    while (nm != NULL) {
        printf("%d %c ",nm->number,nm->action);
        nm = nm->next;
    }
    printf("\r\n");
}

int numberCalc(struct numbers_t **ns) {
    struct numbers_t *t = *ns, *p;
    // numberPrintSubLine(t);
    // nsPrint(ns);
    if (t == NULL) {
        // printf("error : numberCalc nothing to calc\r\n");
        return 1;
    }
    while (t != NULL) {
        if ((t->action == '*') || (t->action == '/')) {
            if (numberOneAction(t)) {
                // printf("error : numberCalc the last symbol must not be action\r\n");
                return 2;
            }
        } else { t = t->next; }
    }
    t = *ns;
    while ((t->action == '+') || (t->action == '-')) {
        if (numberOneAction(t)) {
            // printf("error : numberCalc the last symbol must not be action\r\n");
            return 3;
        }
    }
    if ((*ns)->next != NULL) { return 4; }
    // printf("info : numberCalc return %d\r\n",(*ns)->number);
    return 0;
}

int numberGetSubLine(char *c, int *st, int se, struct numbers_t **head, fun_num_t external_function_for_unknown_name) {
    // printf("info : numberGetSubLine head=<%p>\r\n",head);
    int i=*st, tmp, err; struct numbers_t *tail = *head;
    while (i<se) {
        // numberPrintSubLine(*head);
        // printf("INFO : numberGetSubLine i=%d/%d\r\n",i,se);
        switch (c[i]) {
        case '*':
        case '/':
        case '+':
        case '-':
            // printf("info : numberAddChar %c\r\n",c[i]);
            err = numberAddChar(tail,c[i]);
            if (err) {
                // printf("error: numberAddChar return %d\r\n",err);
                return 1;
            }
            i++;
            *st=i;
            break;
        case '(':
            i++;
            if (tail == NULL) {
                err = numberGetSubLine(c,&i,se,&tail,external_function_for_unknown_name);
            } else {
                err = numberGetSubLine(c,&i,se,&(tail->next),external_function_for_unknown_name);
            }
            if (err) {
                // printf("error: numberGetSubLine return %d\r\n",err);
                return 2;
            }
            if (tail->next != NULL) { tail = tail->next; }
            // printf("info : numberGetSubLine return %d\r\n",tail->number);
            if (c[i]!=')') {
                // printf("error: numberGetSubLine not found ')'\r\n");
                return 3;
            }
            i++;
            *st=i;
            // printf("INFO : numberGetSubLine '(' %d %d %d\r\n",i,se,tail->number);
            // tmp = tail->number;
            // err = numberAddNum(&tail,tmp);
            if (err) {
                // printf("error: numberAddNum return %d\r\n",err);
                return 4;
            }
            if (*head == NULL) { *head = tail; }
            break;
        case ')':
            err = numberCalc(head);
            if (err) {
                // printf("error: numberCalc return %d\r\n",err);
                return 5;
            }
            *st = i; i = se;
            break;
        default:
            err = numberGetNum(c,&i,se,&tail,external_function_for_unknown_name);
            if (err) {
                // printf("error: numberGetNum return %d\r\n",err);
                return 6;
            }
            // printf("INFO : numberGetSubLine result default = %d\r\n",(*head)->number);
            if (*head == NULL) { *head = tail; }
            *st = i; 
        }
    }
    err = numberCalc(head);
    // printf("INFO : numberGetSubLine result = %d\r\n",(*head)->number);
    if (err) {
        // printf("error: numberCalc return %d\r\n",err);
        return 7;
    }
    return 0;
}

int numberVoid(char *c, int sz, int *num) {
    return 1; // not found
}

int numberTryGet(char *c, int sz, int *num, fun_num_t external_function_for_unknown_name) {
    int i=0;
    struct numbers_t *head = NULL;
    int err = numberGetSubLine(c,&i,sz,&head,external_function_for_unknown_name);
    if (i<sz) {
        // printf("error : numberTryGet not use full line %d/%d\r\n",i,sz);
        numberClean(head);
        return 1;
    }
    if (head != NULL) {
        *num = head->number;
        // printf("INFO : numberTryGet return number = %d with error=%d\r\n",*num,err);
    }
    numberClean(head);
    return err;
}
