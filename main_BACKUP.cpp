#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Imagen.cpp"
#include "Auxiliares.cpp"
#include "Luces.cpp"
#include "test_matriz.cpp"
#include "cholesky.cpp"

using std::string;
using std::vector;
using std::ifstream;

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

vector<vector<vector<double> > > leerNormalesCatedra() {
    vector<vector<vector<double> > > normales;
    normales.assign(252, vector<vector<double> > (273, vector<double> (3, 0)));

    ifstream fileNomalX;
    fileNomalX.open("normalesX_catedra.txt");
    if (fileNomalX.is_open()) {
        for (int f = 0; f < 252; f++) {
            for (int c = 0; c < 273; c++) {
                double valor; fileNomalX >> valor;
                normales[f][c][0] = valor;
            }
        }
    }

    ifstream fileNomalY;
    fileNomalY.open("normalesY_catedra.txt");
    if (fileNomalY.is_open()) {
        for (int f = 0; f < 252; f++) {
            for (int c = 0; c < 273; c++) {
                double valor; fileNomalY >> valor;
                normales[f][c][1] = valor;
            }
        }
    }

    ifstream fileNomalZ;
    fileNomalZ.open("normalesZ_catedra.txt");
    if (fileNomalZ.is_open()) {
        for (int f = 0; f < 252; f++) {
            for (int c = 0; c < 273; c++) {
                double valor; fileNomalZ >> valor;
                normales[f][c][2] = valor;
            }
        }
    }

    return normales;
}


// @TODO aun no usa factorizacion LU
vector<vector<vector<double> > > calcularNormales(int alto, int ancho, Matriz &S,
                        Imagen &foto1, Imagen &foto2, Imagen &foto3, Imagen &mascara) {

    vector<vector<vector<double> > > normales(alto, vector<vector<double> > (ancho, vector<double>(3, 0)));

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {

            // Si (x,y) NO esta en la mascara, no resuelvo nada, la normal es 0
            if (mascara.prom[f][c] == 0) {
                normales[f][c] = vector<double>(3, 1);
                double norma = NormaVectorial(normales[f][c]);
                normales[f][c][0] /= norma;
                normales[f][c][1] /= norma;
                normales[f][c][2] /= norma;

                continue;
            }

            // (x,y) esta en la mascara, asi que resuelvo el sistema

            // @TODO: Usar factorizacion LU

            // Resolver el sistema arruina la matriz original, entonces uso una copia
            // Haciendo factorizacion LU este problema se soluciona
            Matriz A = S;
            vector<double> b = {foto1.prom[f][c], foto2.prom[f][c], foto3.prom[f][c]};

            vector<double> X = A.resolverSistemaGauss(b);

            normales[f][c][0] = X[1];
            normales[f][c][1] = X[0];
            normales[f][c][2] = X[2];

            double norma = NormaVectorial(normales[f][c]);
            if (norma > EPSILON) {
                normales[f][c][0] /= norma;
                normales[f][c][1] /= norma;
                normales[f][c][2] /= norma;
            }
        }
    }

    return normales;
}

int main() {
    // Indices de las luces que voy a usar
    vector<int> indexes = {0, 1, 2};

    // Leo el archivo de luces
    bool luces_catedra = false;
    vector<luz> luces = leerLuces(luces_catedra);

    // Ahora luces es un vector que tiene todas las luces. S la matriz que las contiene
    Matriz S({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });

    // 512 x 340 px
    bool testPath = true;
    Imagen foto1(getFotoPath("caballo_small", indexes[0], testPath));
    Imagen foto2(getFotoPath("caballo_small", indexes[1], testPath));
    Imagen foto3(getFotoPath("caballo_small", indexes[2], testPath));
    Imagen mascara(getFotoPath("caballo_small", "mask", testPath));

    ancho = foto1.ancho;
    alto = foto1.alto;

    // Normales es una tabla ancho*alto con valor (x,y,z)s
    bool normalesCatedra = false;
    vector<vector<vector<double> > > normales;

    if (normalesCatedra) {
        normales = leerNormalesCatedra();
    } else {
        normales = calcularNormales(alto, ancho, S, foto1, foto2, foto3, mascara);
    }

    alto = normales.size();
    ancho = normales[0].size();

    // DEBUG, QUITAR ESTO
    // normales.assign(3, vector<vector<double> > (3, vector<double> (3, 2)));
    // alto = 3;
    // ancho = 3;


    // cout << "Armo la matriz de profundidades M usando las normales\n";
    vector<map<int, double> > M = armarMatrizProfundidades(normales);

    // cout << "Traspongo M con las dimensiones adecuadas\n";
    vector<map<int, double> > MT = traspuestaEspecial(M, alto*ancho + alto);

    // cout << "Armo la matriz de profundidades A usando formula para no tenes que multiplicar\n";
    vector<map<int, double> > A = armarMatrizProfundidadesPosta(normales);
    // vector<map<int, double> > Aprim = matrizPorMatriz(MT, M, alto*ancho);

    // cout << "Encuentro la L de cholesky";
    vector<map<int, double> > L_choles = dameCholesky(A);

    // cout << "Traspongo la L de cholesky";
    vector<map<int, double> > L_choles_T = traspuestaEspecial(L_choles, L_choles.size());

    // Creo vector de normales a la derecha de la igualdad
    vector<double> v = vectorNormalesXY(normales);

    // cout << "b = Mt * v\n";
    vector<double> b = matrizPorVector(MT, v);

    // cout << "Resuelvo para L de la izquierda\n";
    vector<double> y = resolverInferior(L_choles, b);

    // cout << "Resuelvo para Lt con el resultado anterior\n";
    vector<double> Z = resolverSuperior(L_choles_T, y);

    // cout << "Guardo mi vector de zetas como una matriz\n";
    vector<vector<double> > zetas = recuperarZetas(Z, alto, ancho);

    // Escritura de zetas
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            cout << fixed << zetas[i][j] << (j + 1 == ancho ? "" : ",");
        }
        cout << "\n";
    }

}
