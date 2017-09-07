from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt
import pandas as pd


gauss = []
with open('gaussDim.txt') as my_file:
    for line in my_file:
        gauss.append(float(line.rstrip()))

lu = []
with open('LUDIM.txt') as my_file:
    for line in my_file:
        lu.append(float(line.rstrip()))
cholesky = []
with open('cholesky.txt') as my_file:
    for line in my_file:
        cholesky.append(float(line.rstrip()))

range = []
with open('range.txt') as my_file:
    for line in my_file:
        range.append(float(line.rstrip()))




plt.plot(range, gauss, '-o', label="gauss")
plt.plot(range, lu, '-o', label="lu")
plt.plot(range, cholesky, '-o',  label="cholesky")
plt.ylabel('time (s)')
plt.xlabel('dimension (n)')
#plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
plt.show()
