from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

alto = 0
ancho = 0

def calcular_ancho_alto(catedra=False):
    global alto, ancho
    with open(getFilename("x", catedra)) as f:
        alto = 0
        for line in f:
            alto += 1
            ancho = len(line.split(","))

    if (catedra):
        ancho -= 1 # por el formateo que tiene

def pos(dato):
    if (dato == "x"):
        return 0
    if (dato == "y"):
        return 1
    if (dato == "z"):
        return 2

def getFilename(coor, catedra=False):
    if (catedra):
        return "normales_" + coor + "_catedra.txt"
    else:
        return "norma" + coor + ".txt"


# coor : "x", "y", "z"
def guardar_dato(coor, catedra=False):
    with open(getFilename(coor, catedra)) as archivo:
        fila = 0
        for line in archivo:
            columna = 0
            col = line.split(",")

            if (col == ""):
                continue

            for c in col:
                try:
                    c = float(c)
                except ValueError:
                    continue

                normas[pos(coor)][fila][columna] = c

                columna += 1
            fila += 1

def leer_datos(catedra=False):
    guardar_dato("x", catedra)
    guardar_dato("y", catedra)
    guardar_dato("z", catedra)


normales_catedra = False

# IMPORTANTE LLAMAR
calcular_ancho_alto(normales_catedra)

# Se lee normai[fila][columna]
normax = [[0 for _ in range(ancho)] for __ in range(alto)]
normay = [[0 for _ in range(ancho)] for __ in range(alto)]
normaz = [[0 for _ in range(ancho)] for __ in range(alto)]

normas = [normax, normay, normaz]

leer_datos(normales_catedra)

step = 1

# Make the grid
x, y = np.meshgrid(
    np.arange(0, ancho, step),
    np.arange(0, alto, step)
)

# 0: x,  1: y,  2: z
direcciones = [0, 1]

# Tomar los vectores de la imagen de forma tal que coincida dimensiones
nx = [ a[::step] for a in normas[direcciones[0]][::step] ]
ny = [ a[::step] for a in normas[direcciones[1]][::step] ]
u = np.array(nx)
v = np.array(ny)

# Ploteo
# ----------------------

plt.title("Normales - Luces 0,1,2")

mult = 2
escala = None

if (normales_catedra):
    mult = 2
    escala = 150

plt.quiver(x, y, mult*u, mult*v, scale=escala)
axes = plt.gca()

if not normales_catedra:
    plt.gca().invert_yaxis()

# Plot de caballo consistente
axes.set_xlim([200,500])
axes.set_ylim([250,50])

plt.show()