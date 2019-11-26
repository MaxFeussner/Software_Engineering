##AUTHOR: Andrés Otero García
CC=gcc
CFLAGS=-Wall
tokenDir=../token
stackDir=../stack
commonDir=../common
##stack and node should be in the same directory
token=token
node=node
stack=stack
common=common
i2p=infix-to-postfix
main=main
test=i2p_test

all: $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(i2p).o $(main).o 
	$(CC) $(CFLAGS) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(i2p).o $(main).o -o $(main)

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(i2p).o: $(i2p).c
	$(CC) $(CFLAGS) $(i2p).c -c

$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)

test: $(token).o $(test).o $(tokenDir)/$(token).o $(stackDir)/$(stack).o $(stackDir)/$(node).o $(commonDir)/$(common).o $(i2p).o
	$(CC) $(CFLAGS) $(tokenDir)/$(token).o $(stackDir)/$(stack).o $(stackDir)/$(node).o $(commonDir)/$(common).o $(i2p).o $(test).o -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c

$(node).o: $(nodeDir)/$(node).c
	make -C $(stackDir)

##clear
clean:
	rm -rf *.o $(main)
