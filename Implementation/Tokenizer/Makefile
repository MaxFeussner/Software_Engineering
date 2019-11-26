prog: tokenizer.o get_the_buffer.o is_xy.o iterate_over_buffer.o ../common/common.o
	gcc -o tokenizer tokenizer.o get_the_buffer.o is_xy.o iterate_over_buffer.o ../common/common.o

tokenizer.o: tokenizer.c
		gcc -c tokenizer.c

get_the_buffer.o: get_the_buffer.c
			gcc -c get_the_buffer.c

is_xy.o: is_xy.c
		gcc -c is_xy.c

iterate_over_buffer.o: iterate_over_buffer.c
			gcc -c iterate_over_buffer.c

common.o: ../common/common.c
	make -C ../common

test: ../common/common.o get_the_buffer.o get_the_buffer_test.o is_xy.o is_xy_test.o iterate_over_buffer.o iterate_over_buffer_test.o tokenizer_test.o
	gcc -Wall ../common/common.o is_xy.o iterate_over_buffer.o get_the_buffer.o tokenizer_test.o -o tokenizer_test.t
	gcc -Wall ../common/common.o get_the_buffer.o get_the_buffer_test.o -o get_the_buffer_test.t
	gcc -Wall ../common/common.o is_xy.o is_xy_test.o -o is_xy_test.t
	gcc -Wall ../common/common.o get_the_buffer.o is_xy.o iterate_over_buffer.o iterate_over_buffer_test.o -o iterate_over_buffer_test.t

tokenizer_test.o: tokenizer_test.c
	gcc -Wall tokenizer_test.c -c

get_the_buffer_test.o: get_the_buffer_test.c
	gcc -Wall get_the_buffer_test.c -c

is_xy_test.o: is_xy_test.c
	gcc -Wall is_xy_test.c -c

iterate_over_buffer_test.o: iterate_over_buffer_test.c
	gcc -Wall iterate_over_buffer_test.c -c


