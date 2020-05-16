import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Data for plotting
times = pd.read_csv('time.csv')
accr = pd.read_csv('accr.csv')
atmp = pd.read_csv('atmp.csv')
x = np.linspace(0, 10000, 10000)


# Plotting time against n
timeplot = times.plot(x='Unnamed: 0')
#timeplot.plot(x, 0.0012*(x**(1.5)), label='n sqrt(n)')
timeplot.legend()
timeplot.set_xlabel('No. of vertices, n')
timeplot.set_ylabel('Runtime (ms)')
timeplot.get_figure().savefig("time.png", dpi=200)

# PLotting accr
accrplot = accr.plot(x='Unnamed: 0')
accrplot.legend()
accrplot.set_xlabel('No. of vertices, n')
accrplot.set_ylabel('Accuracy')
accrplot.get_figure().savefig("accr.png", dpi=200)

# PLotting avg number of tries per success
atmpplot = atmp.plot(x='Unnamed: 0')
atmpplot.legend()
atmpplot.set_xlabel('No. of vertices, n')
atmpplot.set_ylabel('Avg. no. of tries per success')
atmpplot.get_figure().savefig("atmp.png", dpi=200)



plt.show()
