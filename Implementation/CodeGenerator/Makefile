CC=gcc
CFLAGS=-Wall
commonDir=../common
common=common
main=codegenerator

$(main): $(commonDir)/$(common).o $(main).o
	$(CC) $(CFLAGS) $(commonDir)/$(common).o  $(main).o -o $(main)

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)

test: $(common).o $(main).o $(test).o
	$(CC) $(CFLAGS) $(common).o $(main).o $(test).o -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

clean:
	rm -rf *.o
