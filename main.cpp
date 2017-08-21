#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;

// Una luz seria un vector de 3 coordenadas
typedef vector<double> luz;

string filepathLuces = "recursos/resultados_y_ejemplos/luces.txt";

int main() {

    vector<luz> luces(12);

    // Leo el archivo de luces
    ifstream fileLuces;
    fileLuces.open(filepathLuces);
    if (fileLuces.is_open()) {

        int cantLuces;
        fileLuces >> cantLuces;

        for (int i = 0; i < cantLuces; i++) {
            double x, y, z;
            fileLuces >> x >> y >> z;
            luces[i] = luz({x, y, z});

            std::cout << "luz: " << i << "     (" << x << ", " << y << ", " << z << ")\n";
        }
    }



}
