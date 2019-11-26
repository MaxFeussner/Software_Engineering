CC=gcc
CFLAGS=-Wall
node=node
stack=stack
test=node_stack_test

##no linking (we don't want an executable file, only the .o files

##compile
all: $(node).o $(stack).o

$(node).o: $(node).c
	$(CC) $(node).c -c

$(stack).o: $(stack).c
	$(CC) $(stack).c -c

test: $(node).o $(stack).o $(test).o
	$(CC) $(CFLAGS) $(node).o $(stack).o $(test).o -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

##clear
clean:
	rm -rf *.o
