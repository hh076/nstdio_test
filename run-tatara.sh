#!/bin/bash
#PJM -N "qn_test"
#PJM -L "rscgrp=cx-dbg"
#PJM -L "vnode=1"
#PJM -L "vnode-core=1"
#PJM -P "vn-policy=abs-unpack"
#PJM -L "elapse=0:30"
#PJM -j
#PJM -X
#PJM --no-stging

NUM_NODES=${PJM_VNODES}
NUM_CORES=1
NUM_PROCS=`expr ${NUM_NODES} \* ${NUM_CORES}`
#NUM_PROCS=32

#####################
#DEV=ib
DEV=udp

#PROG=test_hello_${DEV}
PROG='arp -a'

######################
#EX_NODEFILE=${HOME}/src/test_acp/nodefile_expanded
#export NUM_NODES NUM_CORES NUM_PROCS EX_NODEFILE
#${HOME}/src/test_acp/expand_proc
#
######################
#echo '$DEV' ${DEV}
#echo '$NUM_NODES $NUM_CORES $NUM_PROCS $EX_NODEFILE' ${NUM_NODES} ${NUM_CORES} ${NUM_PROCS} ${EX_NODEFILE}
#echo ${PJM_O_NODEINF}
#cat ${PJM_O_NODEINF}
#
#echo ${EX_NODEFILE}
#cat ${EX_NODEFILE}
#
######################
#export NUM_NODES NUM_CORES NUM_PROCS
#
######################
#echo '$DEV' ${DEV}
#echo '$NUM_NODES $NUM_CORES $NUM_PROCS' ${NUM_NODES} ${NUM_CORES} ${NUM_PROCS}
#echo ${PJM_O_NODEINF}
#cat ${PJM_O_NODEINF}
#
######################
##${HOME}/src/test_acp/acprun --acp-nprocs=${NUM_PROCS} --acp-nodefile=${PJM_O_NODEINF} --acp-envnet=${DEV} ${HOME}/src/test_acp/${PROG}

hostname
arp -a


cd /home/usr2/f70002a/src/vis/
./sqb_wrapper
