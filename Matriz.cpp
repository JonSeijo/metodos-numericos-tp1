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

    Matriz productoM(const Matriz B){
        if(this->columnas != B.filas){
            std::cout << "Producto indefinido para estas dos matrices \n";
            return Matriz();
        }
        else{
            vector<vector<double> > coeficientes;
            for(int i = 0; i < this->filas; i++){
                vector<double> vectorFila;
                for(int j = 0; j < B.columnas; j++){
                    double suma = this->m[i][0] * B.m[0][j];
                    for(int k = 1; k < this->columnas; k++){
                        suma += this->m[i][k] * B.m[k][j];
                    }
                    vectorFila.push_back(suma);
                }
                coeficientes.push_back(vectorFila);
            }
            return Matriz(coeficientes);
        }
    }

    bool operator==(const Matriz B){
        if(this->filas != B.filas || this->columnas != B.columnas){
            return false;
        }
        else{
            for(int i = 0; i < this->filas; i++){
                for(int j = 0; j < this->columnas; j++){
                    if(this->m[i][j] != B.m[i][j]){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    bool operator!=(const Matriz B){
        return !(*this == B);
    }

    private:
        void mostrar(std::ostream& os) const{
            os << std::endl;
            if(filas == 0 || columnas == 0){
                os << "[]" << std::endl;
            }
            else{
                for(int i = 0; i < filas; i++){
                    for(int j = 0; j < columnas; j++){
                        os << m[i][j] << " ";
                    }
                    os << std::endl;
                }
                os << std::endl;   
            }
            
        }

        friend std::ostream& operator<<(std::ostream& os, const Matriz &c){
            c.mostrar(os);
            return os;
        };



};




#endif