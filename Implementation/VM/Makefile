##AUTHOR: Andrés Otero García
CC=gcc
CFLAGS=-lm -Wall
tokenDir=../token
stackDir=../stack
commonDir=../common
common=common
token=token
node=node
stack=stack
VM=VM
main=main
test=VM_test


all: $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(VM).o $(main).o
	$(CC) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(VM).o $(main).o $(CFLAGS) -o $(main)


$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(node).o: $(nodeDir)/$(node).c
	make -C $(stackDir)

$(VM).o: $(VM).c
	$(CC) $(CFLAGS) $(VM).c -c

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)

test: $(token).o $(test).o $(tokenDir)/$(token).o $(stackDir)/$(stack).o $(stackDir)/$(node).o $(commonDir)/$(common).o $(VM).o
	$(CC) $(tokenDir)/$(token).o $(stackDir)/$(stack).o $(stackDir)/$(node).o $(commonDir)/$(common).o $(VM).o $(test).o $(CFLAGS)  -o test.t

$(test).o: $(test).c
	$(CC) $(CFLAGS) $(test).c -c


##clear
clean:
	rm -rf *.o $(main)
