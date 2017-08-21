#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;

string filepathLuces = "recursos/resultados_y_ejemplos/luces.txt";

// Una luz seria un vector de 3 coordenadas
typedef vector<double> luz;

class Matriz {
    public:
        vector<vector<double> > m;
        int filas, columnas;

    Matriz (int _filas, int _columnas) {
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
    }

    Matriz (vector<vector<double> > _m) {
        m = _m;
        filas = m.size();
        columnas = filas != 0 ? m[0].size() : 0;
    }

    vector<double> &operator [] (int fila) {
        return m[fila];
    }

    void print() {
        std::cout << "Debug matriz: \n";
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {
                std::cout << m[f][c] << " ";
            }
            std::cout << "\n";
        }
    }

};

vector<luz> leerLuces() {
    vector<luz> luces(12);

    ifstream fileLuces;
    fileLuces.open(filepathLuces);
    if (fileLuces.is_open()) {

        int cantLuces;
        fileLuces >> cantLuces;

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


int main() {
    // Leo el archivo de luces
    vector<luz> luces = leerLuces();

    // Ahora luces es un vector que tiene todas las luces

    Matriz S({
        luces[0],
        luces[1],
        luces[2]
    });

    S.print();
}
