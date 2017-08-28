#ifndef LUCES_CPP
#define LUCES_CPP

string filepathLuces_catedra = "recursos/resultados_y_ejemplos/luces.txt";
string filepathLuces_propia = "luces_calibradas.txt";

// Una luz seria un vector de 3 coordenadas
typedef vector<double> luz;

vector<luz> leerLuces(bool catedra=false) {
    vector<luz> luces;

    ifstream fileLuces;
    fileLuces.open(catedra ? filepathLuces_catedra : filepathLuces_propia);
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

vector<luz> calibrarLuces() {
    return vector<luz>();
}

#endif