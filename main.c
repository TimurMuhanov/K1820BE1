#include <stdio.h>
#include "lib/files.h"
#include "lib/macs.h"
#include "lib/names.h"
#include "lib/equs.h"
#include "lib/orgs.h"

int main(int argc, char* argv[]) {
    linesInit();
    nameInit();
    macInit();
    equInit();
    orgInit();
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
        nameClean();
        return err;
    }
    err = macAddToAsm();
    if (err) {
        printf("ERROR: in MACRO proccessing 2\r\n");
        linesClean();
        macClean();
        nameClean();
        return err;
    }
    err = equResolver();
    if (err) {
        printf("ERROR: in EQU proccessing\r\n");
        linesClean();
        macClean();
        nameClean();
        equClean();
        return err;
    }
    printf("******************************************* print all\r\n");
    linesPrint();
    printf("******************************************* print assembly\r\n");
    linesPrint4asm();
    printf("*******************************************\r\n");
    linesClean();
    macClean();
    nameClean();
}