#ifndef AUXILIARES_CPP
#define AUXILIARES_CPP

#include <bits/stdc++.h>

using namespace std;

string pathImages = "recursos/ppmImagenes/";

// Por ej, (caballo, 0) -> "recursos/ppmImagenes/caballo/caballo.0.ppm"
string getFotoPath(string figura, string i, bool test=false) {
    string s = "";
    s += (test ? "pruebas/" : pathImages + figura + "/") + figura + "." + i + ".ppm";
    return s;
}
string getFotoPath(string figura, int i, bool test=false) {
    return getFotoPath(figura, std::to_string(i), test);
}

template <typename T>
void debug(vector<T> &v, string msg = "Debug: ") {
    cout << msg << ": \n";
    for (auto e : v) {
        cout << e << " ";
    }
    cout << "\n";
}

void debug(double &v, string msg = "Debug: ") {
    cout << msg << ": " << v << "\n";
}

double NormaVectorial(const vector<double>& v){
	if(v.size() <= 0){
		return 0;
	}
	else{
		double suma = v[0]*v[0];
		for(int k = 1; k < v.size(); k++){
			suma += (v[k]*v[k]);
		}
		return sqrt(suma);
	}
}

Matriz obtenerMatrizEcuaciones(Matriz& M){
	
	vector<vector<double> > v; 
    //VAMOS A RRECORRER LA MATRIZ COLUMNA POR COLUMNA, LA CACHÉ SE VA A ENOJAR
    for(int i = 0; i < M.cantColumnas() - 1; i++){
        for(int j = 0; j < M.cantFilas() - 1; j++){
            //ESTARÍA BUENO INICIALIZARLOS CON TAMAÑO (FILAS*COLUMNAS)-1
            vector<double> v_fila;
            vector<double> v_fila2; 
            //PONER CEROS CORRIESPONDIENTES A LA FILA 
            for(int cerosLocos = 0; cerosLocos < j + i*(M.cantFilas()); cerosLocos++){
                v_fila.push_back(0);
                v_fila2.push_back(0);
            }

            //METEMOS A LA PRIMER FILA LA NORMA QUE LE CORRESPONDE
            v_fila.push_back(M[j][i]);

            //AHORA MÁS CEROS
            for(int k = 1; k < M.cantFilas(); k++){
                v_fila.push_back(0);
            }
            //PONEMOS LO QUE CORRESPONDE
            v_fila.push_back(M[j][i]);

            //Y AHORA A RELLENAR DE CEROS 
            for(int l = j + i*(M.cantFilas()) + 2 + M.cantFilas(); l < (M.cantColumnas())*(M.cantFilas()); l++){
                v_fila.push_back(0);
            }

            //AHORA LA SEGUNDA FILA 

            v_fila2.push_back(M[j][i]); v_fila2.push_back(M[j][i]);

            //DE NUEVO LLENO DE CEROS
            for(int l = j + i*(M.cantFilas()) + 2; l < (M.cantColumnas())*(M.cantFilas()); l++){
                v_fila2.push_back(0);
            }
            v.push_back(v_fila);
            v.push_back(v_fila2);
        }
    }

    return Matriz(v);
}

void MostrarVector(vector<double>& v){
    std::cout << "(";
    for(int i = 0; i < v.size(); i++){
        std::cout << v[i];
        if(i == v.size() - 1){
            std::cout << ")";
        }
        else{
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

void MostrarVectorString(vector<string>& v){
    for(int i = 0; i < v.size(); i++){
        if(v[i] != "." && v[i] != ".."){
            std::cout << v[i];
            if(i != v.size() - 1){
                std::cout << ", "; 
            }
        }
    }
    std::cout << std::endl;
}

#endif