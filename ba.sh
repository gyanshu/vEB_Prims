#!/bin/bash
a=1
b=1
count=10
as=0
bs=0
cs=0
ds=0
`g++ prim.cpp -O3 -o bin`
`g++ fib.cpp -O3 -o fib`
`g++ rb.cpp -O3 -o rb`
`g++ temp.cpp -O3 -o veb`
`g++ rancomp.cpp -O3 -o C`
while [ $count -lt 5050 ]
do
	./C $count 1000 > smallgraph;
	a=`./rb < smallgraph`;
	#b=`./bin < smallgraph`;
	c=`./fib < smallgraph`;
	d=`./veb < smallgraph`;
	echo "rb: "$a "fib: " $c "veb: " $d "count: " $count
	echo $count,$a >> data_rbc.txt
	echo $count,$c >> data_fibc.txt
	echo $count,$d >> data_vebc.txt
	count=$[$count+50]
done

#echo $as/100 $bs/100 $cs/100 $ds/100