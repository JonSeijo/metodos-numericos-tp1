#include <bits/stdc++.h>
#include "Imagen.cpp"
#include "Auxiliares.cpp"

using namespace std;

/*
Pasos a seguir:

|- Leer mascara de esfera y las 12 imagenes
|- Calcular R con la mascara
|- Calcular Cx, Cy con la mascara
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

    double min_fila = 1e8;
    double max_fila = 0;

    double min_col = 1e8;
    double max_col = 0;

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {
            if (mascara.prom[f][c] != 0) {
                min_fila = min(min_fila, (double)f);
                max_fila = max(max_fila, (double)f);

                min_col = min(min_col, (double)c);
                max_col = max(max_col, (double)c);
            }
        }
    }

    double radio = (max_col - min_col) / 2.0;

    double center_y = min_fila + (max_fila - min_fila) / 2.0;
    double center_x = min_col + (max_col - min_col) / 2.0;

    debug(radio, "radio");
    debug(center_x, "center_x");
    debug(center_y, "center_y");
}