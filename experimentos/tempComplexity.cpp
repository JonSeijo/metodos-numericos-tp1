#include "../cholesky.cpp"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;


Matriz generateRandomMatrix(int n){
    srand (time(NULL));
    Matriz m = Matriz(n, n);
    for(int i = 0; i < m.cantFilas(); i++){
        for(int j = 0; j < m.cantColumnas(); j++){
            m[i][j] = ((double) rand() / (RAND_MAX));
        }
    }
    return m;
}

// generar PositiveDefiniteSimetricMatrix

Matriz generatePDSM(int n){
    Matriz m = generateRandomMatrix(n);
    Matriz mt = m.traspuesta();
    Matriz MxMt = m.productoM(mt);
    Matriz nI = Matriz(n, n, "identidad").multiplicacionEscalar(n); //matriz con ns en la diagonal
    MxMt = MxMt.sumaM(nI);
    cout << MxMt;
    return MxMt;
}

vector<double> generateRandomB(int n){
    srand (time(NULL));
    vector<double> res;
    for(int i=0; i < n; i++) res.push_back((double) rand() / (RAND_MAX));
    return res;
}

int main(){
        int n = 10;
        Matriz m = generatePDSM(n);
        vector<double> b = generateRandomB(n);
        vector<double> res =  m.resolverSistemaGauss(b, true);
        for(int i=0;i<res.size();i++) cout << res[i] << " ";
        return 0;
}


