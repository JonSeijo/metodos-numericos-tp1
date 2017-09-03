#ifndef MATRIZ_ESPECIAL
#define MATRIZ_ESPECIAL

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;

int alto, ancho;

bool esta(map<int, double> &fila, int index) {
    return (fila.find(index) != fila.end());
}

vector<map<int, double> > armarMatrizProfundidades(vector<vector<vector<double> > > &normales) {
    int n = normales.size();
    int m = normales[0].size();

    vector<map<int, double> > matrix; // [fila][columna]

    int cont = 0;

    int cantFilasNulas = 0;

    for (int f = 0; f < n-1; f++) {
        for (int c = 0; c < m; c++) {
            double valor = normales[f][c][2];

            map<int, double> fila1;
            map<int, double> fila2;

            fila1[cont] = valor;

            // REVISAR, PUEDE SER +M
            fila1[cont + n] = valor;
            fila2[cont] = valor;
            fila2[cont + 1] = valor;

            matrix.push_back(fila1);
            if (c + 1 < m) {
                matrix.push_back(fila2);
            } else {
                matrix.push_back(map<int, double>());
                cantFilasNulas++;
            }

            cont++;
        }
    }

    return matrix;
}

vector<map<int, double> > dameCholesky(vector<map<int, double> > &A) {
    int n = A.size();
    vector<map<int, double> > L(n);

    for (int j = 0; j < n; j++) {

        if (j % 100 == 0) {
            // cout << "cholesky j: " << j << "\n";
        }

        // Inicio Sumatoria 1
        double suma1 = 0;
        for (auto it : L[j]) {
            if (it.first >= j) {
                break;
            }
            suma1 += it.second;
        }
        // Fin Sumatoria 1

        // La diagonal de A siempre deberia estar ... (MENTIRA, que onda?)
        if (A[j][j] - suma1 <= EPSILON) {
            // cout << "owfuck " << j << "  fabs(A[j][j]): " << fabs(A[j][j]) << "   suma: " << suma1 << "\n";
        } else {

            L[j][j] = sqrt(A[j][j] - suma1);

            for (int i = j+1; i < min(j + alto + 1, n); i++) {

                // Inicio Sumatoria2
                double suma2 = 0;
                for (auto it : L[i]) {
                    int k = it.first;
                    if (k >= j) {
                        break;
                    }
                    if (esta(L[k], j)) {
                        suma2 += L[i][k] * L[k][j];
                    }
                }
                // Fin Sumatoria2

                L[i][j] = (1.0/L[j][j]) * ((esta(A[i], j) ? A[i][j] : 0) - suma2);
            }
        }
    }
    return L;
}

vector<map<int, double> > armarMatrizProfundidadesPosta(vector<vector<vector<double> > > &normales) {
    if (normales.size() == 0) {
        cout << "armarMatrizProfundidadesPosta: VECTOR NORMALES VACIO\n";
    }

    int filas = normales.size();
    int columnas = normales[0].size();

    vector<map<int, double> > matrix(filas*columnas); // [fila][columna]
    int diag = 0;

    for (int f = 0; f < filas-1; f++) {
        // cout << "fila: " << f << "\n";
        for (int c = 0; c < columnas; c++) {

            double valor = normales[f][c][2] * normales[f][c][2];

            if (c+1 < columnas) {
                matrix[diag][diag] += valor;
                matrix[diag][diag+1] += valor;
                matrix[diag+1][diag] += valor;
                matrix[diag+1][diag+1] += valor;
            }

            // Ojo que puede ser filas/columnas, ver
            int n = columnas;

            matrix[diag][diag] += valor;
            matrix[diag][diag+n] += valor;
            matrix[diag+n][diag] += valor;
            matrix[diag+n][diag+n] += valor;

            diag++;
        }
    }

    return matrix;
}


vector<map<int, double> > traspuestaEspecial(vector<map<int, double> > &L, int cantfilasnueva) {

    int tam = L.size();
    vector<map<int, double> > T(cantfilasnueva);

    for (int f = 0; f < tam; f++) {
        for (auto it : L[f]) {

            int nf = it.first;
            int nc = f;
            double value = it.second;

            T[nf][nc] = value;
        }
    }

    return T;
}


vector<double> matrizPorVector(vector<map<int, double> > &A, vector<double> &X) {
    vector<double> res(X.size());

    for (int f = 0; f < A.size(); f++) {

        if (f % 100 == 0) {
            // cout << "matriz por vector: " << f << "\n";
        }
        double suma = 0;
        for (auto it : A[f]) {
            suma += it.second * X[it.first];
        }
        res[f] = suma;
    }

    return res;
}

// Pre: las dimensiones dan bien
vector<map<int, double> > matrizPorMatriz(vector<map<int, double> > &A, vector<map<int, double> > &B, int tam) {
    vector<map<int, double> > R(A.size());

    for (int f = 0; f < A.size(); f++) {

        // if (f % 10 == 0) {
        //     cout << "f: " << f << "\n";
        // }
        for (int c = 0; c <= f; c++) {
            double suma = 0;

            for (auto it : A[f]) {
                int j = it.first;
                double ai = it.second;

                if (esta(B[j], c)) {
                    suma += ai * B[j][c];
                }
            }

            if (suma != 0) {
                R[f][c] = suma;
                R[c][f] = suma;
            }
        }
    }


    return R;
}


vector<double> vectorNormalesXY(vector<vector<vector<double> > > &normales) {
    vector<double> vect;

    int filas = normales.size();
    int columnas = normales[0].size();

    int cantBlancas = 0;

    for (int f = 0; f < filas-1; f++) {
        for (int c = 0; c < columnas; c++) {
            vect.push_back(normales[f][c][1]);
            vect.push_back(normales[f][c][0]);
        }
    }

    return vect;
}


// Pre: L es triangular inferior
vector<double> resolverInferior(vector<map<int, double> > &L, vector<double> b) {
    vector<double> X(L.size(), 0);
    for (int i = 0; i < L.size(); i++) {
        if (i % 100 == 0) {
            // cout << "i: " << i << "   resolverInferior\n";
        }
        if (L[i][i] < EPSILON) {
            // std::cerr << "PERO QUE HACES CHABON COMO VAS A DIVIDIR POR CERO LOCO\n";
            X[i] = 0;
        } else {
            X[i] = b[i] / L[i][i];
            for (int k = i + 1; k < L.size(); k++ ) {
                if (esta(L[k], i)) {
                    b[k] -= L[k][i] * X[i];
                }
            }
        }
    }
    return X;
}

// Pre: L es triangular superior
vector<double> resolverSuperior(vector<map<int, double> > &L, vector<double> b) {
    vector<double> X(L.size(), 0);
    for (int i = L.size() - 1; i >= 0; i--) {
        if (i % 100 == 0) {
            // cout << "i: " << i << "   iiiii esto tarda\n";
        }
        if (L[i][i] < EPSILON) {
            // std::cerr << "PERO QUE HACES CHABON COMO VAS A DIVIDIR POR CERO LOCO\n";
            X[i] = 0;
        } else {
            X[i] = b[i] / L[i][i];
            for (int k = i - 1; k >= 0; k-- ) {
                if (esta(L[k], i)) {
                    b[k] -= L[k][i] * X[i];
                }
            }
        }
    }
    return X;
}


vector<vector<double> > recuperarZetas(vector<double> Z, int alto, int ancho) {
    vector<vector<double> > zetas(alto, vector<double>(ancho, 0));

    int f = 0;
    int c = 0;
    for (int index = 0; index < Z.size(); index++) {

        zetas[f][c] = Z[index];

        if (c+1 < ancho) {
            c++;
        } else {
            c = 0;
            f++;
        }

    }

    return zetas;
}

#endif