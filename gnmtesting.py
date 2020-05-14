#! /usr/bin/env python3
import subprocess
import numpy as np
import pandas as pd

def gengraph(n = 100, c = 0, d = 1):
    stream = subprocess.Popen(['testgen/graphgen', str(n), str(c), str(d)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    graph, err = stream.communicate()
    return graph

def runDHAM(g):
    proc = subprocess.Popen(['dham/main'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    outs, errs = proc.communicate(input=g)
    return outs
            
def runtests():
    n = 6500 
    timesheet = {}
    accrsheet = {}
    while n < 16001:
        avgs = []
        accr = []
        for c in range(1):
            times = []
            count = 10
            for x in range(count):
                g = gengraph(n, c)
                attempt=0
                while attempt < 50: 
                    attempt = attempt + 1
                    outp = runDHAM(g).decode()
                    ans = [int(s) for s in outp.split() if s.isdigit()]
                    if ans[0] == 1:
                        times.append(ans[1])
                        print("n = {}, c = {}, atmp = {}, time = {}\n".format(n, c, attempt, ans[1]))
                        break
                    #print(ans)
            avgs.append(np.mean(times))
            accr.append(len(times)/count)
        timesheet[n] = avgs
        accrsheet[n] = accr
        n = n + 1000
    a, b = pd.DataFrame(timesheet), pd.DataFrame(accrsheet)
    a.to_csv('time.csv')
    b.to_csv('accr.csv')
    #print(timesheet)
    #print(accrsheet)

def main():
    runtests()

if __name__ == "__main__":
    main()
