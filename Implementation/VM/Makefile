CC=gcc
CFLAGS=-lm
tokenDir=../token
stackDir=../stack
commonDir=../common
common=common
token=token
node=node
stack=stack
main=VM

##link
$(main): $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(main).o
	$(CC) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(main).o $(CFLAGS) -o $(main)

##compile
$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(node).o:

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)


##clear
clean:
	rm -rf *.o $(main)
