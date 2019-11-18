CC=gcc
CFLAGS=-Wall
node=node
stack=stack

##no linking (we don't want an executable file, only the .o files

##compile
all: $(node).c $(stack).c
	$(CC) $(node).c -c
	$(CC) $(stack).c -c

##clear
clean:
	rm -rf *.o
