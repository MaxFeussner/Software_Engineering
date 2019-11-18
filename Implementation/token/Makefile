CC=gcc
CFLAGS=-lm
token=token

##no linking (we don't want an executable file, only the .o files

##compile
all: $(token).c
	$(CC) $(CFLAGS) $(token).c -c

##clear
clean:
	rm -rf *.o
