#!/bin/bash


#for (i=1; i<=150; i=i+1)  

#do

#for (j=1;j<=20;j=j+1)

#do
#   ./RW 100000  $i >>pallel_time_10W.txt
#done
#done


for num2 in {1..1000}
do
python WRW_6node.py 1 >>6_50_p2p-Gnutella04_50W.txt
wait
done


