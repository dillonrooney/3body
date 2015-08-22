#!/bin/bash

TIMING=timing
#TIMING_FILE=r1.txt
DATA=plot_r1


cat ${TIMING}/r1.txt | grep 1000 | grep "	naive" > ${DATA}/r1_1000_naive.dat
cat ${TIMING}/r1.txt | grep 1000 | grep "writing" > ${DATA}/r1_1000_writing.dat
cat ${TIMING}/r1.txt | grep 1000 | grep "init_gen2" > ${DATA}/r1_1000_init_gen2.dat
cat ${TIMING}/r1.txt | grep 1000 | grep "init_read" > ${DATA}/r1_1000_init_read.dat
cat ${TIMING}/r1.txt | grep 1000 | grep "comparison" > ${DATA}/r1_1000_comparison.dat

cat ${TIMING}/r1.txt | grep 768 | grep "	naive" > ${DATA}/r1_768_naive.dat
cat ${TIMING}/r1.txt | grep 768 | grep "writing" > ${DATA}/r1_768_writing.dat
cat ${TIMING}/r1.txt | grep 768 | grep "init_gen2" > ${DATA}/r1_768_init_gen2.dat
cat ${TIMING}/r1.txt | grep 768 | grep "init_read" > ${DATA}/r1_768_init_read.dat
cat ${TIMING}/r1.txt | grep 768 | grep "comparison" > ${DATA}/r1_768_comparison.dat

cat ${TIMING}/r1.txt | grep 1536 | grep "	naive" > ${DATA}/r1_1536_naive.dat
cat ${TIMING}/r1.txt | grep 1536 | grep "writing" > ${DATA}/r1_1536_writing.dat
cat ${TIMING}/r1.txt | grep 1536 | grep "init_gen2" > ${DATA}/r1_1536_init_gen2.dat
cat ${TIMING}/r1.txt | grep 1536 | grep "init_read" > ${DATA}/r1_1536_init_read.dat
cat ${TIMING}/r1.txt | grep 1536 | grep "comparison" > ${DATA}/r1_1536_comparison.dat


gnuplot plot_run_1.gp