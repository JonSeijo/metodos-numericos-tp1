import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import seaborn
from seaborn import *

seaborn.set_style(style='white')

# tmp
alto = -1
ancho = -1
profs = []

def guardar_dato():
    global alto, ancho, profs
    with open("profundidades.txt") as archivo:
        fila = 0
        for line in archivo:
            columna = 0

            if (alto == -1 and ancho == -1):
                line = line.split(" ")

                alto = int(line[0])
                ancho = int(line[1])

                # alto = int(line[1])
                # ancho = int(line[0])

                profs = [[0 for __ in range(ancho)] for _ in range(alto)]
                continue


            col = line.split(",")

            # print(col)
            if (col == ""):
                continue


            for c in col:
                try:
                    c = float(c)
                except ValueError:
                    print(c)
                    continue

                # limit = 0.4
                limit = 2
                if (abs(c) > limit):
                    c = limit/c
                    # c = 0

                if (c == 0):
                    c = float('nan')

                profs[fila][columna] = c

                columna += 1
            fila += 1

# print(profs)

guardar_dato()


step = 1

# Make the grid
x, y = np.meshgrid(
    np.arange(0, ancho, step),
    np.arange(0, alto, step)
)

# Tomar los vectores de la imagen de forma tal que coincida dimensiones
nz = [ profs[y] for y in range(alto) ]

Z = np.array(nz[::step])

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.axis('off')

colores = [cm.magma, cm.gray, cm.bone, cm.binary, cm.coolwarm, cm.copper]

color = 2
stride = 4
lim = 3

ax.plot_surface(x, y, Z[::-1], cmap=colores[color], linewidth=1, cstride=stride, rstride=stride,
    vmin=np.nanmin(Z), vmax=np.nanmax(Z))
# cset = ax.contour(x, y, Z[::-1], cmap=cm.coolwarm)

ax.set_title("Profundidades usando luces: 3,7,10")

ax.set_zlim(-lim, lim)

# setup the colorbar
scalarmappaple = cm.ScalarMappable(cmap=colores[color])
scalarmappaple.set_array(Z)
plt.colorbar(scalarmappaple)

plt.show()