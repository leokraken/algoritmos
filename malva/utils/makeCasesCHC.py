#! /usr/bin/python3
# -*- coding: utf-8 -*-
import sys

if __name__ == "__main__":
    it = 1
    for ind in [50, 100, 200]:
        for div in [0.5, 0.7, 0.9]:
            for cross in [0.6, 0.7, 0.8]:
                namefile = "caso-%d.cfg" %it
                file = open(namefile,"w")
                it = it + 1
                str = "30		// number of independent runs 10\n";
                str = str + "1000		// number of generations 100\n";
                str = str + "%d		// number of individuals\n" %ind ;
                str = str + "0		// display state ?\n"
                str = str + "Selection-Parameters	// selections to apply\n"
                str = str + "0.9 1 %.1f		// selection parameter , diverge operator & its probability 0.9\n" %div
                str = str + "Intra-Operators	// operators to apply in the population\n"
                str = str + "0 %.1f		// crossover & its probability 0.6\n" %cross
                str = str + "Inter-Operators  // operators to apply between this population and anothers\n"
                str = str + "0 25 5 1 3 1 5		// operator number, operator rate, number of individuals, selection of indidivual to send and remplace\n"
                str = str + "LAN-configuration\n"
                str = str + "101		// refresh global state\n"
                str = str + "1 		// 0: running in asynchronized mode / 1: running in synchronized mode\n"
                str = str + "1		// interval of generations to check solutions from other populations\n"
                file.write(str)
                file.close
                #print(str)
