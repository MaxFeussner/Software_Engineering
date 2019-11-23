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
main=infix-to-postfix

$(main): $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(main).o 
	$(CC) $(CFLAGS) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(commonDir)/$(common).o $(main).o -o $(main)

$(main).o: $(main).c
	$(CC) $(CFLAGS) $(main).c -c

$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(common).o: $(commonDir)/$(common).c
	make -C $(commonDir)

$(node).o:

##clear
clean:
	rm -rf *.o $(main)
