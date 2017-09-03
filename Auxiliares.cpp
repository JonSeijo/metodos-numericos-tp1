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
    //ÉCHENLE LA CULPA A QUIENES PUSIERON LOS EJES AL REVÉS
    for(int i = 0; i < M.cantColumnas() - 1; i++){
        for(int j = 0; j < M.cantFilas() - 1; j++){
            //ESTARÍA RE PIOLA INICIALIZARLOS CON TAMAÑO (FILAS*COLUMNAS)-1
            vector<double> v_fila;
            vector<double> v_fila2; 
            //PONER CEROS CORRIESPONDIENTES A LA FILA AAAAAAAAAAAAAA
            for(int cerosLocos = 0; cerosLocos < j + i*(M.cantFilas()); cerosLocos++){
                v_fila.push_back(0);
                v_fila2.push_back(0);
            }
            //WOW, MANY ZEROS

            //AHORA ALGO (QUIZÁS) DISTINTO DE CERO, PARA CALENTAR EL AMBIENTE
            //ENCHUFAMOS A LA PRIMER FILA LA NORMA QUE LE CORRESPONDE
            v_fila.push_back(M[j][i]);

            //AHORA MÁS CEROS
            for(int k = 1; k < M.cantFilas(); k++){
                v_fila.push_back(0);
            }
            //PONEMOS LO QUE CORRESPONDE, NO LA VAMOS A CAGAR AHORA

            v_fila.push_back(M[j][i]);

            //Y AHORA A RELLENAR DE CEROS ASLDKJFALSDJGKALFJN
            //LE SAQUE UN -1 A LO DE FILAS*COLUMNAS Y SE LO SUME AL I + J JEJE, SOLO PARA NO HACER UNA
            //SUMA AL PEDO
            for(int l = i + j + 2 + M.cantFilas(); l < (M.cantColumnas())*(M.cantFilas()); l++){
                v_fila.push_back(0);
            }

            //AHORA LA SEGUNDA FILA LEL

            v_fila2.push_back(M[j][i]); v_fila2.push_back(M[j][i]);

            //DE NUEVO LLENO DE CEROS AL TOQUE PERRO
            for(int l = i + j + 2; l < (M.cantColumnas())*(M.cantFilas()); l++){
                v_fila2.push_back(0);
            }
            v.push_back(v_fila);
            v.push_back(v_fila2);
        }
    }

    return Matriz(v);
}

#endif