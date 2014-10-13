#! /usr/bin/python3
# -*- coding: utf-8 -*-
import sys

if __name__ == "__main__":
    it = 1
    for ind in [50, 100, 200]:
        for mut in [0.01,0.05,0.1]:
            for cross in [0.6, 0.7, 0.8]:
                namefile = "caso-%d.cfg" %it
                file = open(namefile,"w")
                it = it + 1
                str = "30		// number of independent runs 10\n";
                str = str + "1000		// number of generations 100\n";
                str = str + "%d		// number of individuals\n" %ind ;
                str = str + "100		// size of offsprings in each generation\n"
                str = str + "1		// if replaces parents for offsprings, or only offsprings may be new parents\n"
                str = str + "0		// display state ?\n"
                str = str + "Selections	// selections to apply\n"
                str = str + "1 3		// selection of parents 1 3\n"
                str = str + "1 3		// selection of offsprings 2 0\n"
                str = str + "Intra-Operators	// operators to apply in the population\n"
                str = str + "0 %.1f		// crossover & its probability 0.6\n" %cross
                str = str + "1 1.0 %.2f	// mutation & its probability x x 0.01\n" %mut
                str = str + "Inter-Operators // operators to apply between this population and anothers\n"
                str = str + "0 10 5 1 3 1 5  // operator number, operator rate, number of individuals, selection of indidivual to send and remplace\n"
                str = str + "LAN-configuration\n"
                str = str + "1		// refresh global state\n"
                str = str + "0		// 0: running in asynchronized mode / 1: running in synchronized mode\n"
                str = str + "1		// interval of generations to check solutions from other populations\n"
                file.write(str)
                file.close
                #print(str)