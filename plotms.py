#! /usr/bin/env python3
import subprocess
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
def gengraph(n = 100, c = 0, d = 1):
    stream = subprocess.Popen(['testgen/checkms', str(n), str(c), str(d)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    graph, err = stream.communicate()
    return graph

def runDHAM(g, modalg=1):
    proc = subprocess.Popen(['dham/main', str(modalg)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    outs, errs = proc.communicate(input=g)
    return outs
            
def runtests():
    n = 100
    mssheet = {}
    while n < 10001:
        avms = []
        for k in [5]:
            times = []
            count = 20
            ams, ams2 = 0, 0
            for x in range(count):
                g = gengraph(n, k).decode()
                ans = [int(s) for s in g.split() if s.isdigit()]
                ams += ans[0]
                ams2 += ans[1]

            avms.append(ams2/ams)
            print("n = {} : ms = {}, ms2 = {}".format(n, ams/count, ams2/count))
        mssheet[n] = avms
        n = n + 200
    a = pd.DataFrame(mssheet)
    x = a.transpose().plot()
    plt.show()
    x.get_figure().savefig("accr.png", dpi=200)
    #print(timesheet)
    #print(accrsheet)

def main():
    runtests()

if __name__ == "__main__":
    main()
