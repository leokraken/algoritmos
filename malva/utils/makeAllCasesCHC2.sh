#!/bin/bash
INSTANCES=../ProblemInstances/FJSS-instances
CHC_DIR=../rep/CHC
CHC_DIR_CFGS=../rep/CHC/cfgs
SLEEP_TIME=10

#para GA
for CASO in {6..6}
do
	echo CASO $CASO
	mkdir $CHC_DIR/gantt/data/$CASO
	mkdir $CHC_DIR/res/$CASO
	mkdir $CHC_DIR/LOG/$CASO

	for f in $( ls $INSTANCES); do
		echo item: $f
		$CHC_DIR/MainSeq $CHC_DIR_CFGS/caso-$CASO.cfg $INSTANCES/$f $CHC_DIR/res/$CASO/${f%.*}.txt $CHC_DIR/gantt/data/$CASO/$f >$CHC_DIR/LOG/$CASO/${f%.*}.txt
		sleep $SLEEP_TIME
	done
done
