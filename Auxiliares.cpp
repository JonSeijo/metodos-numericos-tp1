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

#endif