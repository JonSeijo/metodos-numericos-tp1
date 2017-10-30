import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

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

                # limit = 1.5
                limit = 2
                if (abs(c) > limit):
                    c = limit/c

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
color = 1

stride = 10

# ax.plot_surface(x, y, Z[::-1], cmap=colores[color], linewidth=1, cstride=stride, rstride=stride)
cset = ax.contour(x, y, Z[::-1], cmap=cm.coolwarm)

plt.show()