CC=gcc
CFLAGS=-Wall
tokenDir=../token
stackDir=../stack
##stack and node should be in the same directory
token=token
node=node
stack=stack
main=infix-to-postfix

$(main): $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(main).o
	$(CC) $(CFLAGS) $(tokenDir)/$(token).o $(stackDir)/$(node).o $(stackDir)/$(stack).o $(main).o -o $(main)

$(token).o: $(tokenDir)/$(token).c
	make -C $(tokenDir)

$(stack).o: $(stackDir)/$(stack).c $(nodeDir)/$(node).c
	make -C $(stackDir)

$(node).o:

##clear
clean:
	rm -rf *.o $(main)
