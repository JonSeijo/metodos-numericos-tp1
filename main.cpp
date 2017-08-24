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

// Por ej, "recursos/ppmImagenes/caballo/caballo.0.ppm"
string getFotoPath(string figura, int i) {
    string s = "";
    s += pathImages + figura + "/" + figura + "." + std::to_string(i) + ".ppm";
    return s;
}


int main() {
    // Indices de las luces que voy a usar
    vector<int> indexes = {0, 1, 2};

    // Obtengo los paths de las fotos
    vector<string> filepathsFotos({
        getFotoPath("caballo", indexes[0]),
        getFotoPath("caballo", indexes[1]),
        getFotoPath("caballo", indexes[2])
    });

    // Leo el archivo de luces
    vector<luz> luces = leerLuces();

    // Ahora luces es un vector que tiene todas las luces
    Matriz S({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });

    // S.print();

    // 512 x 340 px
    Imagen foto1(filepathsFotos[ indexes[0] ]);
    Imagen foto2(filepathsFotos[ indexes[1] ]);
    Imagen foto3(filepathsFotos[ indexes[2] ]);

    // TEST Triangulacion
    Matriz A({
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    });

    cout << A;

    A.triangular();

    cout << A;

    // ------TESTING-----------------------------------------------------

    // std::cout << "Mini test norma vectorial: " << std::endl;
    // vector<double> v0 = {4, 3, 3, 3, 4, 4, 3, 4};
    // if(10 == NormaVectorial(v0)){
    //     std::cout << "TODO BIEN" << std::endl;
    // }
    // else{
    //     std::cout << "TODO MAL" << std::endl;
    // }
    // testDeMatrices();
}
