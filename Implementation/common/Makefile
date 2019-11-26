CC=gcc
common=common
test=common_test

##no linking (we don't want an executable file, only the .o files

##compile
all: $(common).c
	$(CC) $(common).c -c


test: $(common).o $(test).o
	$(CC) $(CFLAGS) $(common).o $(test).o -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

##clear
clean:
	rm -rf *.o
