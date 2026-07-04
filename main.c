#include <stdio.h>
#include "lib/files.h"
#include "lib/macs.h"
#include "lib/names.h"

int main(int argc, char* argv[]) {
    if (argc != 2) { return 1; }
    int err = filesRead(argv[1]);
    if (err) {
        linesClean();
        return err;
    }
    err = macCutFromAsm();
    if (err) {
        printf("ERROR: in MACRO proccessing 1\r\n");
        linesClean();
        macClean();
        namesClean();
        return err;
    }
    err = macAddToAsm();
    if (err) {
        printf("ERROR: in MACRO proccessing 2\r\n");
        linesClean();
        macClean();
        namesClean();
        return err;
    }
    printf("******************************************* print all\r\n");
    linesPrint();
    printf("******************************************* print assembly\r\n");
    linesPrint4asm();
    printf("*******************************************\r\n");
    linesClean();
    macClean();
    namesClean();
}