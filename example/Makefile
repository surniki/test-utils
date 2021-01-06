.POSIX:
.SUFFIXES:

darray_test: test.o test_darray.o test_utils.o darray.o
	gcc -o darray_test test.o test_darray.o test_utils.o darray.o

test.o: test.c test_utils.h
	gcc -c -g -DRUN_TESTS test.c

test_darray.o: test_darray.c test_darray.h test_utils.h
	gcc -c -g -DRUN_TESTS test_darray.c

test_utils.o: test_utils.c test_utils.h
	gcc -c -g -DRUN_TESTS test_utils.c

darray.o: darray.c darray.h test_utils.h
	gcc -c -g -DRUN_TESTS darray.c

clean:
	rm darray_test darray.o test.o test_darray.o test_utils.o
