#ifndef AUXILIARES_CPP
#define AUXILIARES_CPP

#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;

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