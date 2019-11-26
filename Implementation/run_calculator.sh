tokDir=Tokenizer
tokEx=tokenizer
i2pDir=infix-to-postfix
i2pEx=main
CGDir=CodeGenerator
CGEx=codegenerator
VMDir=VM
VMEx=main
INPUT=$1
OUTPUT=$2
input_good=0
output_good=0

if test -f "$INPUT"
then
	echo "Using input file $INPUT"
	input_good=1
fi

if [ $# -gt 1 ]
then
	touch "$OUTPUT"

	if test -f "$OUTPUT"
	then
		echo "Using output file $OUTPUT"
		output_good=1
	fi
fi


if [ "$input_good" -eq 1 ] && [ "$output_good" -eq 1 ]
then
	cat "$INPUT" | "./$tokDir/$tokEx" | "./$i2pDir/$i2pEx" | "./$CGDir/$CGEx" | "./$VMDir/$VMEx" > "$OUTPUT"
elif [ "$input_good" -eq 1 ]
then
	cat "$INPUT" | "./$tokDir/$tokEx" | "./$i2pDir/$i2pEx" | "./$CGDir/$CGEx" | "./$VMDir/$VMEx"
else
	echo "No input file defined"
fi
