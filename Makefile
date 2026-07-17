LIB := lib
TEST := tests

all:
	gcc -o $(TEST)/K1820BE1 main.c $(LIB)/files.c \
	$(LIB)/lines.c $(LIB)/names.c $(LIB)/macs.c \
	$(LIB)/equs.c $(LIB)/orgs.c $(LIB)/labels.c $(LIB)/numbers.c

test: all
	tests/test_run.sh