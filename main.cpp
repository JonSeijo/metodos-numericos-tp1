#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Imagen.cpp"
#include "Auxiliares.cpp"
#include "test_matriz.cpp"

using std::string;
using std::vector;
using std::ifstream;

string filepathLuces = "recursos/resultados_y_ejemplos/luces.txt";
string pathImages = "recursos/ppmImagenes/";
string figura = "caballo";


// Una luz seria un vector de 3 coordenadas
typedef vector<double> luz;

vector<luz> leerLuces() {
    vector<luz> luces;

    ifstream fileLuces;
    fileLuces.open(filepathLuces);
    if (fileLuces.is_open()) {

        int cantLuces; fileLuces >> cantLuces;
        luces.resize(cantLuces);

        for (int i = 0; i < cantLuces; i++) {
            double x, y, z;
            fileLuces >> x >> y >> z;
            luces[i] = luz({x, y, z});
            // @DEBUG
            // std::cout << "luz: " << i << "     (" << x << ", " << y << ", " << z << ")\n";
        }
    }

    return luces;
}

// Por ej, (caballo, 0) -> "recursos/ppmImagenes/caballo/caballo.0.ppm"
string getFotoPath(string figura, string i) {
    string s = "";
    s += pathImages + figura + "/" + figura + "." + i + ".ppm";
    return s;
}
string getFotoPath(string figura, int i) {
    return getFotoPath(figura, std::to_string(i));
}


template <typename T>
void debug(vector<T> &v, string msg = "Debug: ") {
    cout << msg << ": \n";
    for (auto e : v) {
        cout << e << " ";
    }
    cout << "\n";
}

int main() {
    // Indices de las luces que voy a usar
    vector<int> indexes = {0, 1, 2};

    // Leo el archivo de luces
    vector<luz> luces = leerLuces();

    // Ahora luces es un vector que tiene todas las luces. S la matriz que las contiene
    Matriz S({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });


    // 512 x 340 px
    Imagen foto1(getFotoPath("caballo", indexes[0]));
    Imagen foto2(getFotoPath("caballo", indexes[1]));
    Imagen foto3(getFotoPath("caballo", indexes[2]));
    Imagen mascara(getFotoPath("caballo", "mask"));

    int ancho = foto1.ancho;
    int alto = foto1.alto;

    // Normales es una tabla ancho*alto con valor (x,y,z)
    vector<double> normales[alto][ancho];

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {

            // Si (x,y) NO esta en la mascara, no resuelvo nada, la normal es 0
            if (mascara.prom[f][c] == 0) {
                normales[f][c] = vector<double>(3, 0);
                continue;
            }

            // (x,y) esta en la mascara, asi que resuelvo el sistema

            // @TODO: Usar factorizacion LU
            // Resolver el sistema arruina la matriz original, entonces uso una copia
            // Haciendo factorizacion LU este problema se soluciona
            Matriz A = S;
            vector<double> b = {foto1.prom[f][c], foto2.prom[f][c], foto3.prom[f][c]};
            normales[f][c] = A.resolverSistema(b);

            double norma = NormaVectorial(normales[f][c]);
            normales[f][c][0] /= norma;
            normales[f][c][1] /= norma;
            normales[f][c][2] /= norma;
        }
    }

    // TEST : Resolucion de sistema
    // Matriz A({
    //     {1, 2, -3},
    //     {6, 3, -9},
    //     {7, 14, -21}
    // });
    // vector<double> b = {2, 6, 13};

    // cout << "A: \n";
    // cout << A;

    // // resolverSistema modifica la matriz A
    // auto rta = A.resolverSistema(b);
    // debug(b, "B");
    // debug(rta, "X");
}
