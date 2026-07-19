LIB := lib
TEST := tests

all:
	gcc -o $(TEST)/K1820BE1 main.c $(LIB)/files.c \
	$(LIB)/lines.c $(LIB)/names.c $(LIB)/macs.c \
	$(LIB)/equs.c $(LIB)/orgs.c $(LIB)/labels.c $(LIB)/numbers.c \
	$(LIB)/../asm/asms.c $(LIB)/../asm/K1820BE1.c 

test: all
	tests/test_run.sh