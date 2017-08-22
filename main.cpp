#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Imagen.cpp"

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
            std::cout << "luz: " << i << "     (" << x << ", " << y << ", " << z << ")\n";
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

    S.print();

    // 512 x 340 px
    Imagen foto1(filepathsFotos[ indexes[0] ]);
    Imagen foto2(filepathsFotos[ indexes[1] ]);
    Imagen foto3(filepathsFotos[ indexes[2] ]);

    //Pequeño test

    std::cout << std::endl << "Test producto matricial" << std::endl;

    vector<double> e1 = {1, 0, 0};
    vector<double> e2 = {0, 1, 0};
    vector<double> e3 = {0, 0, 1};
    vector<double> nulo = {0, 0, 0};
    vector<double> uno = {1, 1, 1};

    vector<vector<double> > coeficientes1;
    vector<vector<double> > coeficientes2;
    vector<vector<double> > coeficientes3;
    vector<vector<double> > coeficientes4;

    //identidad
    coeficientes1.push_back(e1);
    coeficientes1.push_back(e2);
    coeficientes1.push_back(e3);

    Matriz id = Matriz(coeficientes1);

    /*
	1 0 0
	0 1 0
	1 1 1
    */
    coeficientes2.push_back(e1);
    coeficientes2.push_back(e2);
    coeficientes2.push_back(uno);

    Matriz matr = Matriz(coeficientes2);

    //nula
    coeficientes3.push_back(nulo);
    coeficientes3.push_back(nulo);
    coeficientes3.push_back(nulo);

    Matriz nula = Matriz(coeficientes3);

    //uno
    coeficientes4.push_back(uno);
    coeficientes4.push_back(uno);
    coeficientes4.push_back(uno);

    Matriz deUnos = Matriz(coeficientes4);

    std::cout << "Matriz de unos \n" << deUnos << std::endl;

    std::cout << "Porducto id * unos \n" << std::endl;

    Matriz producto = deUnos.productoM(id, deUnos);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto << std::endl;


}
