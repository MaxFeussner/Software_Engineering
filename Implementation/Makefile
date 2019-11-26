CC=gcc
tokDir=Tokenizer
tokenDir=token
stackDir=stack
i2pDir=infix-to-postfix
commonDir=common
CGDir=CodeGenerator
VMDir=VM

tokEx=tokenizer
i2pEx=main
CGEx=codegenerator
VMEx=main

all:
	make -C $(tokDir)
	make -C $(tokenDir)
	make -C $(stackDir)
	make -C $(commonDir)
	make -C $(i2pDir)
	make -C $(CGDir)
	make -C $(VMDir)

run_pipe:
	echo "Using file \"input_file.txt\""
	cat input_file.txt | ./$(tokDir)/$(tokEx) | ./$(i2pDir)/$(i2pEx) | ./$(CGDir)/$(CGEx) | ./$(VMDir)/$(VMEx)

test:
	make -C $(tokDir) test
	make -C $(tokenDir) test
	make -C $(stackDir) test
	make -C $(commonDir) test
	make -C $(i2pDir) test
	make -C $(CGDir) test
	make -C $(VMDir) test

test_all:
	prove ./$(tokDir)/*.t
	prove ./$(tokenDir)/*.t
	prove ./$(stackDir)/*.t
	prove ./$(commonDir)/*.t
	prove ./$(i2pDir)/*.t
	prove ./$(CGDir)/*.t
	prove ./$(VMDir)/*.t
