LIB := lib
TEST := tests

all:
	gcc -o $(TEST)/K1820BE1 main.c $(LIB)/files.c $(LIB)/lines.c $(LIB)/names.c