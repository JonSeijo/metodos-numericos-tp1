#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Imagen.cpp"
#include "Auxiliares.cpp"
#include "Luces.cpp"
#include "test_matriz.cpp"
#include "cholesky.cpp"

#include "MatrizEspecialFunciones.cpp"

using std::string;
using std::vector;
using std::ifstream;


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

            vector<double> X = A.resolverSistemaGauss(b, false);

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
/*
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
    */
    std::cout << "\n\nESTO ANDA, SOLO HAY QUE AUMENTAR LA PRECISION EN EL COUT PORQUE APARECEN FRACCIONES\n\n";

    Matriz tengoLU({
        {6, -2, 2, 4},
        {12, -8, 6, 10},
        {3, -13, 9, 3},
        {-6, 4, 1, -18}
    });
    std::cout << "Matriz Original: \n\n" << tengoLU << "\n\n";
    tengoLU.triangular(true);
    std::cout << "Matriz Factorizada: \n\n" << tengoLU << "\n\n";

}
