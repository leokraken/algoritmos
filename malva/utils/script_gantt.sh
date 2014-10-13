#!/bin/bash
INSTANCES=./ProblemInstances/FJSS-instances
GA_DIR=./rep/GA
CHC_DIR=./rep/CHC

#para GA
mkdir $GA_DIR/gantt/data
for f in $( ls $INSTANCES); do
	echo item: $f
	./MainGantt $INSTANCES/$f $GA_DIR/gantt/data/$f $GA_DIR/gantt/latex/$f
done

#para CHC
mkdir $CHC_DIR/gantt/data
for f in $( ls $INSTANCES); do
	echo item: $f
	./MainGantt $INSTANCES/$f $CHC_DIR/gantt/data/$f $CHC_DIR/gantt/latex/$f
done
