CFLAGS = -I. -fcommon

all: tests

tests: annlib_tests/main.o annlib_tests/annlib_tests.o
	$(CC) -o $@ $^
