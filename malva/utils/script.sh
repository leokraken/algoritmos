#!/bin/bash
INSTANCES=../ProblemInstances/FJSS-instances
GA_DIR=../rep/GA
CHC_DIR=../rep/CHC

CASO=30
SLEEP_TIME=10

#para GA
mkdir $GA_DIR/gantt/data/$CASO
mkdir $GA_DIR/res/$CASO
for f in $( ls $INSTANCES); do
	echo item: $f
	$GA_DIR/MainSeq $GA_DIR/newGA.cfg $INSTANCES/$f $GA_DIR/res/$CASO/${f%.*}.txt $GA_DIR/gantt/data/$CASO/$f
	sleep $SLEEP_TIME
done

#para CHC
mkdir $CHC_DIR/gantt/data/$CASO
mkdir $CHC_DIR/res/$CASO
echo CHC
for f in $( ls $INSTANCES); do
	echo item: $f
	$CHC_DIR/MainSeq $CHC_DIR/CHC.cfg $INSTANCES/$f $CHC_DIR/res/$CASO/${f%.*}.txt $CHC_DIR/gantt/data/$CASO/$f
	sleep $SLEEP_TIME
done
