#!/bin/sh
#PBS -N 'qn_test'
#PBS -q Q1
#PBS -j oe
#PBS -l nodes=1:ppn=1:D

####################################################
NPROCS=1
VISDIR=$HOME/src/vis

NODEFILE=$PBS_NODEFILE
cat $NODEFILE
#cd $PBS_O_WORKDIR

cd ${VISDIR}
./sqb_wrapper
