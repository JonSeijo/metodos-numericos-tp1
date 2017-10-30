from mpl_toolkits.mplot3d.axes3d import Axes3D
# from seaborn import *
import matplotlib.pyplot as plt
import pandas as pd

verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
naranja = '#FFA420'
violeta = '#af73b7'

colores = [azul, verde, rojo, naranja, violeta]
# colores = [violeta, verde, rojo, naranja, azul]

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
    # ESTO ERA LA V1
    # [0.4046511628,0.4418604651,0.8006352264],
    # [0.0604651163,0.1906976744,0.9797848573],
    # [0.3209302326,-0.0046511628,0.9470914172],
    # [0.3302325581,-0.0325581395,0.9433379167],
    # [0.3395348837,-0.1906976744,0.9210594225],
    # [0.3395348837,-0.0418604651,0.9396615158],
    # [0.2744186047,0.1534883721,0.9492817016],
    # [0.3116279070,0.0511627907,0.9488258093],
    # [0.2465116279,0.1255813953,0.9609689539],
    # [0.3023255814,0.0511627907,0.9518306633],
    # [0.0511627907,0.1906976744,0.9803146259],
    # [0.3023255814,-0.0511627907,0.9518306633]
    [0.4352728105,0.4647828316,0.7710476638],
    [0.2040197120,0.1550549811,0.9666094920],
    [-0.0737944693,0.2049846368,0.9759793415],
    [-0.1171167852,0.4606593551,0.8798162406],
    [-0.3365895604,0.5011444566,0.7972212375],
    [-0.1288741685,0.5534008411,0.8228845349],
    [0.2258568798,0.4283492547,0.8749317607],
    [0.0706892458,0.4476985570,0.8913860177],
    [0.1672437711,0.3583795096,0.9184735424],
    [0.0402064740,0.3457756767,0.9374553967],
    [0.0909701953,0.0744301598,0.9930682629],
    [-0.1667469372,0.3731955262,0.9126448149]
]

propias_x = [luces_propias[i][0] for i in range(12)]
propias_y = [luces_propias[i][1] for i in range(12)]
propias_z = [luces_propias[i][2] for i in range(12)]

catedra_x = [luces_catedra[i][0] for i in range(12)]
catedra_y = [luces_catedra[i][1] for i in range(12)]
catedra_z = [luces_catedra[i][2] for i in range(12)]

diff_zetas = [abs(luces_propias[i][2] - luces_catedra[i][2]) for i in range(12)]
maxdiffz = max(diff_zetas)

# for i in range(12):
#     print("Luz " + str(i) + (":  " if (i < 10) else ": "), diff_zetas[i])


# fig, ax = plt.subplots()
# for i in range(len(luces_propias)):
    # ax.plot([0, luces_propias[i][1]], [0, luces_propias[i][0]],zs=[0, luces_propias[i][2]])
    # ax.plot([0, luces_propias[i][1]], [0, luces_propias[i][0]])
    # ax.plot([0, luces_catedra[i][0]], [0, luces_catedra[i][1]])

# for i in range(len(luces_catedra)):
#     ax.plot([0, luces_catedra[i][0]], [0, luces_catedra[i][1]],zs=[0, luces_catedra[i][2]])
# plt.show()

plotter_ax = pd.DataFrame(propias_x).plot(style='--', ylim=(-1,1), xticks=list(range(12)), color=colores[0])
pd.DataFrame(catedra_x).plot(ax=plotter_ax, style='.-', ylim=(-1,1), xticks=list(range(12)), color=colores[0])

pd.DataFrame(propias_y).plot(ax=plotter_ax, style='--', ylim=(-1,1), xticks=list(range(12)), color=colores[1])
pd.DataFrame(catedra_y).plot(ax=plotter_ax, style='.-', ylim=(-1,1), xticks=list(range(12)), color=colores[1])

pd.DataFrame(propias_z).plot(ax=plotter_ax, style='--', ylim=(-1,1), xticks=list(range(12)), color=colores[2])
pd.DataFrame(catedra_z).plot(ax=plotter_ax, style='.-', ylim=(-1,1), xticks=list(range(12)), color=colores[2])

# maximoz = pd.DataFrame([maxdiffz for _ in range(12)])
# maximoz.plot(ax=plotter_ax)

plotter_ax.legend([
    "X propias", "X cátedra",
    "Y propias", "Y cátedra",
    "Z propias", "Z cátedra"
])

plotter_ax.set_title("Valores obtenidos en la calibración de luces.\nComparación con luces de la cátedra.\n")
# plt.annotate('%0.2f' % maxdiffz, xy=(1, maxdiffz), xytext=(8, 0),
#                  xycoords=('axes fraction', 'data'), textcoords='offset points')

plotter_ax.set_xlabel("Luz", size = 14)
plotter_ax.set_ylabel("Valor obtenido", size = 14)
plt.show()