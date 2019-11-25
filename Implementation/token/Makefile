CC=gcc
CFLAGS=-lm
token=token
test=token_test

##no linking (we don't want an executable file, only the .o files

##compile
all: $(token).o

$(token).o: $(token).c
	$(CC) $(CFLAGS) $(token).c -c

test: $(token).o $(test).o
	$(CC) $(CFLAGS) $(token).o $(test).o -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

##clear
clean:
	rm -rf *.o
