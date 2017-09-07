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
'''
# Creo un arreglo con las diferencias
diff_zetas = [abs(luces_propias[i][2] - luces_catedra[i][2]) for i in range(12)]
 
# Tomo el maximo para graficar una linea
maxdiffz = max(diff_zetas)
 
# Creo un dataframe con mis datos
data = pd.DataFrame(diff_zetas)
maximoz_data = pd.DataFrame([maxdiffz for _ in range(12)])
 
 
# Plotteo las 12 muestras
# plotter_ax = data.plot(style='.-', ylim=(0,1), xticks=list(range(12)))
# NOTA: HACE .PLOT DIRECTO, LOS PARAMETROS SON PARA CUSTOMIZAR:
plotter_ax = data.plot()
 
# Grafico una lina con mi maximo en el mismo plot
maximoz_data.plot(ax=plotter_ax)
 
# plotter_ax.legend(["Diferencias", "Máxima diff"])
 
plotter_ax.set_title("Diferencia entre luces propias y de la cátedra, eje Z")
 
# plt.annotate('%0.2f' % maxdiffz, xy=(1, maxdiffz), xytext=(8, 0),
#                  xycoords=('axes fraction', 'data'), textcoords='offset points')
 
plotter_ax.set_xlabel("Luz", size = 14)
plotter_ax.set_ylabel("Diferencia en eje Z", size = 14)
plt.show()'''
