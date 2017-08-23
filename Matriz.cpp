#ifndef MATRIZ_CPP
#define MATRIZ_CPP

#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;

class Matriz {
    public:
        

    Matriz() {
        filas = 0;
        columnas = 0;
    }

    //Perdón por meterle esos ifs pero no me agradan los seg fault
    Matriz (int _filas, int _columnas) {
        if(_filas < 0 || _columnas < 0){
        	throw std::runtime_error("NO SE PUEDEN CREAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
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
        if(fila < 0 || fila >= filas){
        	throw std::runtime_error("FILA FUERA DE RANGO");
        }
        return m[fila];
    }

    //Perdón por meterle esos ifs pero no me agradan los seg fault
    void redimensionar(int _filas, int _columnas) {
        if(_filas < 0 || _columnas < 0){
        	throw std::runtime_error("NO SE PUEDEN REDIMENSIONAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
    }

    //Traspone en la misma matriz OJO!!
    void trasponerCuadrada(){
        if(this->filas > 1){
            for(int i = 1; i < filas; i++){
                for(int j = 0; j < i; j++){
                    double temp = this->m[i][j];
                    this->m[i][j] = this->m[j][i];
                    this->m[j][i] = temp;
                }
            }
        }
    }

    //La matriz original se pierde OJO!!
    void trasponerGeneral(){
        vector<vector<double> > coeficientes;
        for(int c = 0; c < columnas; c++){
            vector<double> NuevaFila;    
            for(int f = 0; f < filas; f++){
                NuevaFila.push_back(this->m[f][c]);
            }
        coeficientes.push_back(NuevaFila);
        }
        this->m = coeficientes;
        int temp = this->filas;
        this->filas = this->columnas;
        this->columnas = temp;
    }

    //La matriz original se mantiene, y retorna otra (que es la traspuesta de la original)
    Matriz trasponerYMantenerOrig(){
        vector<vector<double> > coeficientes;
        for(int c = 0; c < columnas; c++){
            vector<double> NuevaFila;    
            for(int f = 0; f < filas; f++){
                NuevaFila.push_back(this->m[f][c]);
            }
        coeficientes.push_back(NuevaFila);
        }
        return Matriz(coeficientes);
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
        if(this->columnas != B.filas || this->filas <= 0 || this->columnas <= 0 || B.columnas <= 0){
        	throw std::runtime_error("PRODUCTO MATRICIAL INDEFINIDO");
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

    int cantFilas(){
    	return filas;
    }

    int cantColumnas(){
    	return columnas;
    }

    private:

    	vector<vector<double> > m;
        int filas, columnas;

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