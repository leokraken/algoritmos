#!/bin/bash
INSTANCES=../ProblemInstances/FJSS-instances
GA_DIR=../rep/GA
CHC_DIR=../rep/CHC
GA_DIR_CFGS=../rep/GA/cfgs

SLEEP_TIME=10

#para GA
for CASO in {28..28}
do 
	echo CASO $CASO
	mkdir $GA_DIR/gantt/data/$CASO
	mkdir $GA_DIR/res/$CASO
	mkdir $GA_DIR/LOG/$CASO

	for f in $( ls $INSTANCES); do
		echo item: $f
		$GA_DIR/MainSeq $GA_DIR_CFGS/caso-$CASO.cfg $INSTANCES/$f $GA_DIR/res/$CASO/${f%.*}.txt $GA_DIR/gantt/data/$CASO/$f >$GA_DIR/LOG/$CASO/${f%.*}.txt
		sleep $SLEEP_TIME
	done
done
