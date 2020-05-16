#! /usr/bin/env python3
import subprocess
import numpy as np
import pandas as pd

def gengraph(n = 100, c = 0, d = 1):
    stream = subprocess.Popen(['testgen/graphgen', str(n), str(c), str(d)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    graph, err = stream.communicate()
    return graph

def runDHAM(g, modalg=1):
    proc = subprocess.Popen(['dham/main', str(modalg)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    outs, errs = proc.communicate(input=g)
    return outs
            
def runtests():
    n = 500
    timesheet = {}
    accrsheet = {}
    atmpsheet = {}
    while n < 4001:
        avgs = []
        accr = []
        atmp = []
        for k in range(4):
            k = 2**k
            times = []
            count = 1 
            attemptsum = 0
            for x in range(count):
                g = gengraph(n)
                attempt=0
                while attempt < 50: 
                    attempt = attempt + 1
                    outp = runDHAM(g, k).decode()
                    ans = [int(s) for s in outp.split() if s.isdigit()]
                    if ans[0] == 1:
                        times.append(ans[1])
                        print("n = {}, c = {}, atmp = {}, time = {}\n".format(n, k, attempt, ans[1]))
                        break
                    #print(ans)
                attemptsum += attempt
            avgs.append(np.mean(times))
            accr.append(len(times)/count)
            if len(times) > 0:
                atmp.append(attemptsum/len(times))
            else :
                atmp.append(-1)
        timesheet[n] = avgs
        atmpsheet[n] = atmp
        accrsheet[n] = accr
        n = n + 100
    a, b, c = pd.DataFrame(timesheet), pd.DataFrame(accrsheet), pd.DataFrame(atmpsheet)
    a.transpose().to_csv('time.csv')
    b.transpose().to_csv('accr.csv')
    c.transpose().to_csv('atmp.csv')
    #print(timesheet)
    #print(accrsheet)

def main():
    runtests()

if __name__ == "__main__":
    main()
