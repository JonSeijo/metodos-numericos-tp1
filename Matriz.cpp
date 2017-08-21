#ifndef MATRIZ_CPP
#define MATRIZ_CPP

#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;

class Matriz {
    public:
        vector<vector<double> > m;
        int filas, columnas;

    Matriz() {
        filas = 0;
        columnas = 0;
    }

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

    void redimensionar(int _filas, int _columnas) {
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
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

#endif