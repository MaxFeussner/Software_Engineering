CC=gcc
CFLAGS=-Wall
commonDir=../common
common=common
cg=codegenerator
main=main
test=testparts

all: $(commonDir)/$(common).o $(cg).o $(main).o
	$(CC) $(CFLAGS) $(commonDir)/$(common).o $(cg).o $(main).o -o $(main)

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(cg).o: $(cg).c
	$(CC) $(CFLAGS) $(cg).c -c

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)

test: $(common).o $(cg).o $(test).o
	$(CC) $(CFLAGS) $(commonDir)/$(common).o $(cg).o $(test).o -o $(test).t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

clean:
	rm -rf *.o
