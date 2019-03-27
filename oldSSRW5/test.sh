#!/bin/bash
make clean
make
for ((i=1; i<=10000; i =i+1))  
do
   ./RW  1 >>Poker_10W
done
