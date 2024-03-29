from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt
import pandas as pd
 
 
luces_catedra = [
    [0.403259,0.480808,0.778592],
    [0.0982272,0.163712,0.981606],
    [-0.0654826,0.180077,0.98147],
    [-0.127999,0.431998,0.892745],
    [-0.328606,0.485085,0.810377],
    [-0.110339,0.53593,0.837021],
    [0.239071,0.41439,0.878138],
    [0.0642302,0.417497,0.906406],
    [0.12931,0.339438,0.931698],
    [0.0323953,0.340151,0.939813],
    [0.0985318,0.0492659,0.993914],
    [-0.16119,0.354617,0.921013]
]
 
luces_propias = [
    [0.4046511628,0.4418604651,0.8006352264],
    [0.0604651163,0.1906976744,0.9797848573],
    [0.3209302326,-0.0046511628,0.9470914172],
    [0.3302325581,-0.0325581395,0.9433379167],
    [0.3395348837,-0.1906976744,0.9210594225],
    [0.3395348837,-0.0418604651,0.9396615158],
    [0.2744186047,0.1534883721,0.9492817016],
    [0.3116279070,0.0511627907,0.9488258093],
    [0.2465116279,0.1255813953,0.9609689539],
    [0.3023255814,0.0511627907,0.9518306633],
    [0.0511627907,0.1906976744,0.9803146259],
    [0.3023255814,-0.0511627907,0.9518306633]
]
 
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
plt.show()
