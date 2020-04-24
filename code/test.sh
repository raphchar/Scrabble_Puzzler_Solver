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
