#include <stdio.h>
#include "lib/files.h"

int main(int argc, char* argv[]) {
    if (argc != 2) { return 1; }
    int err = filesRead(argv[1]);
    if (err) {
        linesClear();
        return err;
    }
    linesPrint();
    linesClear();
}