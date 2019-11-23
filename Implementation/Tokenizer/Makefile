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
