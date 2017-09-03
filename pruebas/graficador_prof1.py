import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# alto = 60
# ancho = 60

alto = 133
ancho = 200

# alto = 340
# ancho = 512

# alto = 252
# ancho = 273

profs = [[0 for __ in range(ancho)] for _ in range(alto)]

def guardar_dato():
    with open("profundidades.txt") as archivo:
        fila = 0
        for line in archivo:
            columna = 0
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

                limit = 2

                if (c > limit):
                    c = limit
                elif (c < -limit):
                    c = -limit

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

Z = np.array(nz)

fig = plt.figure()
ax = fig.gca(projection='3d')


colores = [cm.magma, cm.gray]
color = 1



ax.plot_surface(x, y, Z, cmap=colores[color])
# ax.scatter(x, y, Z)
plt.show()