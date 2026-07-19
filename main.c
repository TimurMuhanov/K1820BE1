#include <stdio.h>
#include "lib/files.h"
#include "lib/macs.h"
#include "lib/names.h"
#include "lib/equs.h"
#include "lib/orgs.h"
#include "lib/labels.h"
#include "asm/asms.h"
#include "asm/K1820BE1.h"
#include <string.h>

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
        labelClean();
        return err;
    }
    err = macAddToAsm();
    if (err) {
        printf("ERROR: in MACRO proccessing 2\r\n");
        linesClean();
        macClean();
        nameClean();
        labelClean();
        return err;
    }
    err = equResolver();
    if (err) {
        printf("ERROR: in EQU proccessing\r\n");
        linesClean();
        macClean();
        nameClean();
        equClean();
        labelClean();
        return err;
    }
    err = orgSetAddresses();
    if (err) {
        printf("ERROR: in ORG proccessing\r\n");
        linesClean();
        macClean();
        nameClean();
        equClean();
        labelClean();
        orgClean();
        return err;
    }
    char name_output[128];
    int name_size=strlen(argv[1]);
    sprintf(name_output,"%s",argv[1]);
    sprintf(name_output+name_size,".bin");
    printf("******************************************* print all\r\n");
    linesPrint();
    printf("******************************************* print assembly\r\n");
    linesPrint4asm();
    printf("******************************************* print equs\r\n");
    equPrint();
    printf("******************************************* print labels\r\n");
    labelPrint();
    printf("*******************************************\r\n");
    err = asmAssembly(K1820BE1DecodeInstruction);
    if (err) {
        printf("ERROR: in assembly\r\n");
        linesClean();
        macClean();
        nameClean();
        equClean();
        labelClean();
        orgClean();
        return err;
    }
    err = fileWrite(name_output);
    if (err) {
        printf("ERROR: in filewrite [%d]\r\n",err);
        linesClean();
        macClean();
        nameClean();
        equClean();
        labelClean();
        orgClean();
        return err;
    }
    printf("*******************************************\r\n");
    linesClean();
    macClean();
    nameClean();
    labelClean();
    orgClean();
}