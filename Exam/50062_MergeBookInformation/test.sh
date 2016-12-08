#!/bin/bash

for ((i=0; i<=11; i+=1))
do
	echo $i
	time ./a.out <../../judgesister/testdata/10152/$i.in >test.out
	diff ../../judgesister/testdata/10152/$i.out test.out
done
