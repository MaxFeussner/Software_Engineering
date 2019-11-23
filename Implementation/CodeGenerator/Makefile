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

clean:
	rm -rf *.o
