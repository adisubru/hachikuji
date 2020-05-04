#! /usr/bin/env python3
import subprocess
import pandas as pd

def gengraph(n = 100, c = 0, d = 1):
    stream = subprocess.Popen(['testgen/graphgen', str(n), str(c), str(d)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    graph, err = stream.communicate()
    return graph

def runDHAM(g):
    proc = subprocess.Popen(['dham/main'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    outs, errs = proc.communicate(input=g)
    return outs
            
def main():
    g = gengraph(1600, 6)
    outp = runDHAM(g)
    print(outp)

if __name__ == "__main__":
    main()
