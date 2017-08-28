#include <bits/stdc++.h>
#include "Imagen.cpp"
#include "Auxiliares.cpp"

using namespace std;

/*
Pasos a seguir:

|- Leer mascara de esfera y las 12 imagenes
- Calcular R con la mascara
- Calcular Cx, Cy con la mascara
- Para cada imagen de esfera:
    : identificar Px Py el punto mas iluminado
    : hacer el calculo de vector luz para esta imagen

*/

int main() {
    Imagen mascara(getFotoPath("mate", "mask"));
    vector<Imagen> fotos;
    for (int i = 0; i < 12; i++) {
        fotos.push_back(Imagen(getFotoPath("mate", i)));
    }

    int ancho = mascara.ancho;
    int alto = mascara.alto;

    int min_fila = 1e8;
    int max_fila = 0;

    int min_col = 1e8;
    int max_col = 0;

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {
            if (mascara.prom[f][c] != 0) {
                min_fila = min(min_fila, f);
                max_fila = max(max_fila, f);

                min_col = min(min_col, c);
                max_col = max(max_col, c);
            }
        }
    }

    cout << "min_col: " << min_col << "\n";
    cout << "max_col: " << max_col << "\n";

    cout << max_col - min_col << "\n";
    cout << max_fila - min_fila << "\n";


}