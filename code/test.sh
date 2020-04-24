#!/bin/bash

set -e

clear
make

for test in input/*; do
	echo "TEST FOR $test: "
	./solver $test/words.txt $test/letters.txt $test/scores.txt
	cat $test/solution.txt
	echo "----------------"
done

echo "TEST BONUS FOR input/general_example: "
./solver input/general_example/words.txt input/general_example/letters.txt input/general_example/scores.txt 3
echo "[ [ ab ab ] ] : 24"
