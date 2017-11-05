from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt
import pandas as pd
# from seaborn import *


# gauss = []
# with open('gauss-1000b-dimension1000.txt') as my_file:
#     for line in my_file:
#         gauss.append(float(line.rstrip()))

# lu = []
# with open('lu-1000b-dimension1000.txt') as my_file:
#     for line in my_file:
#         lu.append(float(line.rstrip()))
# cholesky = []
# with open('cholesky-1000b-dimension1000.txt') as my_file:
#     for line in my_file:
#         cholesky.append(float(line.rstrip()))

# rango = []
# with open('range-b.txt') as my_file:
#     for line in my_file:
#         rango.append(float(line.rstrip()))


gauss = []
with open('gauss-dim500-promedio10.txt') as my_file:
    for line in my_file:
        gauss.append(float(line.rstrip().split()[1]))

lu = []
with open('lu-dim500-promedio10.txt') as my_file:
    for line in my_file:
        lu.append(float(line.rstrip().split()[1]))

cholesky = []
with open('cholesky-dim500-promedio10.txt') as my_file:
    for line in my_file:
        cholesky.append(float(line.rstrip().split()[1]))

rango = [i for i in range(210)]

# Los 10 primeros son basura

rango = rango[11:]
lu = lu[11:]
gauss = gauss[11:]
cholesky = cholesky[11:]



tope = 100
rango = rango[:tope]
lu = lu[:tope]
gauss = gauss[:tope]
cholesky = cholesky[:tope]


espaciado = 5
rango = rango[::espaciado]
lu = lu[::espaciado]
gauss = gauss[::espaciado]
cholesky = cholesky[::espaciado]

tipoPlot = "--"


ax = plt.plot(rango, gauss, tipoPlot)
plt.plot(rango, lu, tipoPlot)
plt.plot(rango, cholesky, tipoPlot)
plt.ylabel('Tiempo (s)')
plt.xlabel('Dimensión')

# plt.yscale("log")
# plt.title("Tiempos Cholesky, LU y Gauss. Escala logarítmica.")

plt.legend([
    "Gauss",
    "LU",
    "Cholesky"
])

plt.show()
