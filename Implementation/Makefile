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

test:
	make -C $(tokDir) test
	make -C $(tokenDir) test
	make -C $(stackDir) test
	make -C $(commonDir) test
	make -C $(i2pDir) test
	make -C $(CGDir) test
	make -C $(VMDir) test

test_all:
	make -C $(tokDir) run_test
	make -C $(tokenDir) run_test
	make -C $(stackDir) run_test
	make -C $(commonDir) run_test
	make -C $(i2pDir) run_test
	make -C $(CGDir) run_test
	make -C $(VMDir) run_test

