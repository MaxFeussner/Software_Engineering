cd common
echo -e "\e[44mCommon function tests:\e[0m"
prove ./*.t

cd ../token
echo -e "\e[44mToken function tests:\e[0m"
prove ./*.t

cd ../stack
echo -e "\e[44mStack and Node function tests:\e[0m"
prove ./*.t

cd ../Tokenizer
echo -e "\e[44mTokenizer function tests:\e[0m"
prove ./*.t

cd ../infix-to-postfix
echo -e "\e[44mRunning Infix to Postfix tests:\e[0m"
prove ./*.t

cd CodeGenerator
echo -e "\e[44mRunning Code Generator tests:\e[0m"
prove ./*.t

cd ../VM
echo -e "\e[44mRunning Virtual Machine tests:\e[0m"
prove ./*.t
