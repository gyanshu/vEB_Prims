#!/bin/bash

#To automate command line commands
a=1
b=1
count=10
as=0
bs=0
cs=0
ds=0
`g++ fib.cpp -O3 -o fib`
`g++ rb.cpp -O3 -o rb`
`g++ vEB.cpp -O3 -o veb`
`g++ rancomp.cpp -O3 -o C`
while [ $count -lt 5050 ]
do
	#Format for the line below: ./C <number of nodes> <maximum edge weight> <density> smallgraph
	./C $count 1000 75 > smallgraph;
	a=`./rb < smallgraph`;
	c=`./fib < smallgraph`;
	d=`./veb < smallgraph`;
	echo "rb: " $a "fib: " $c "veb: " $d "count: " $count
	echo $count,$a >> data_rb.txt
	echo $count,$c >> data_fib.txt
	echo $count,$d >> data_veb.txt
	count=$[$count+50]
done
