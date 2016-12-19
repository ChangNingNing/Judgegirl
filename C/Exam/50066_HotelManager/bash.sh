#!/bin/bash
for ((i=0; i<=10; i+=1))
do
	echo $i
	time ./a.exe <$i.in >test.out
	diff -w $i.out test.out
done
