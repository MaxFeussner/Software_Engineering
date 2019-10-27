CC=gcc
CFLAGS=-Wall
token=token
node=node
stack=stack
main=infix-to-postfix

##link
$(main): $(token).o $(node).o $(stack).o $(main).o
	$(CC) $(CFLAGS) $(token).o $(node).o $(stack).o $(main).o -o $(main)

##compile
$(token).o: $(token).c
	$(CC) $(token).c -c

$(node).o: $(node).c
	$(CC) $(node).c -c

$(stack).o: $(stack).c
	$(CC) $(stack).c -c

$(main).o: $(main).c
	$(CC) $(main).c -c


##clear
clean:
	rm -rf *.o $(main)
