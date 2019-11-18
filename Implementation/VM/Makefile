CC=gcc
CFLAGS=-lm
tokenDir=../token
stackDir=../stack
token=token
node=node
stack=stack
main=VM

##link
$(main): $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(main).o
	$(CC) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(main).o $(CFLAGS) -o $(main)

##compile
$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(node).o:

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c


##clear
clean:
	rm -rf *.o $(main)
