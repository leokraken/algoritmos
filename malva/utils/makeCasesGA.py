#! /usr/bin/python3
# -*- coding: utf-8 -*-
import sys

if __name__ == "__main__":
    namefile = "Cases.txt"
    file = open(namefile,"w")            
    it = 1
    str = ""
    for ind in [50, 100, 200]:
        for mut in [0.01,0.05,0.1]:
            for cross in [0.6, 0.7, 0.8]:
                str = str + "%d\t%.1f\t%.2f\t%d\n" %(it, cross, mut, ind);
                it = it + 1
                
    file.write(str)
    file.close
