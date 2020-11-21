#!/bin/sh

num=10
for i in `seq $num`
do
	echo $i
	./func_inlining 10000000
done

