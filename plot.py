import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Data for plotting
times = pd.read_csv('time.csv')
accr = pd.read_csv('accr.csv')
atmp = pd.read_csv('atmp.csv')
x = np.linspace(100, 2000, 2000)


# Plotting time against n
timeplot = times.plot(x='Unnamed: 0')
#timeplot.plot(x, [0]*x, label='k = 3')
#timeplot.plot(x, 0.0012*(x**(1.5)), label='f(x) = n sqrt(n)')
#timeplot.legend(labels = ['Random Tournaments', 'f(x) = n sqrt(n)'])
timeplot.legend(labels = ['r = 5', 'r = 6', 'r = 7', 'f(n) = n sqrt(n)'])
timeplot.set_xlabel('No. of Vertices')
timeplot.set_ylabel('Runtime (ms)')
timeplot.get_figure().savefig("time.png", dpi=200)

# PLotting accr
accrplot = accr.plot(x='Unnamed: 0')
accrplot.legend().remove()
accrplot.legend(labels = ['r = 5', 'r = 6', 'r = 7', 'f(x) = n sqrt(n)'])
#accrplot.legend(labels = ['Random Tournaments', 'f(x) = n sqrt(n)'])
accrplot.set_xlabel('No. of Vertices')
accrplot.set_ylabel('Accuracy')
accrplot.get_figure().savefig("accr.png", dpi=200)

# PLotting avg number of tries per success
atmpplot = atmp.plot(x='Unnamed: 0')
atmpplot.legend(labels = ['r = 5', 'r = 6', 'r = 7', 'f(x) = n sqrt(n)'])
#atmpplot.legend(labels = ['Random Tournaments', 'f(x) = n sqrt(n)'])
atmpplot.set_xlabel('No. of Vertices')
atmpplot.set_ylabel('Avg. no. of tries per success')
atmpplot.get_figure().savefig("atmp.png", dpi=200)



plt.show()
