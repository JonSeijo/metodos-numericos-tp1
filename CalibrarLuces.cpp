#include <bits/stdc++.h>
#include "Imagen.cpp"
#include "Auxiliares.cpp"

using namespace std;

typedef vector<double> luz;

/*
Pasos a seguir:

|- Leer mascara de esfera y las 12 imagenes
|- Calcular R con la mascara
|- Calcular Cx, Cy con la mascara
- Para cada imagen de esfera:
    : identificar Px Py el punto mas iluminado
    : hacer el calculo de vector luz para esta imagen

@Jonno
*/

double valorVecindad(int filaInicial, int columnaInicial, int rango, int filas, int columnas, Imagen &foto) {
    double acum = 0;
    for (int f = max(0, filaInicial-rango); f <= min(filas-1, filaInicial+rango); f++) {
        for (int c = max(0, columnaInicial-rango); c <= min(columnas-1, columnaInicial+rango); c++) {
            acum += foto.prom[f][c];
        }
    }
    return acum;
}


int main() {
    string tipo_cromada = "cromada";
    string tipo_mate = "mate";

    // La esfera cromada da resultados mas exactos pues el brillo maximo es muchisimo mas notorio
    string tipo = tipo_cromada;

    Imagen mascara(getFotoPath(tipo, "mask"));
    vector<Imagen> fotos;
    for (int i = 0; i < 12; i++) {
        fotos.push_back(Imagen(getFotoPath(tipo, i)));
    }

    double ancho = mascara.ancho;
    double alto = mascara.alto;

    double min_fila = 1e8;
    double max_fila = 0;
    double min_col = 1e8;
    double max_col = 0;

    double EPSILON = 1e-10;

    // ---------------------------------------
    // Obtencion de datos de la mascara

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {
            if (fabs(mascara.prom[f][c] - 0) > EPSILON) {
                min_fila = min(min_fila, (double)f);
                max_fila = max(max_fila, (double)f);
                min_col = min(min_col, (double)c);
                max_col = max(max_col, (double)c);
            }
        }
    }

    double radio = (max_col -  min_col + 1.0) / 2.0 + 1;
    double radioFila = (max_fila - min_fila + 1.0) / 2.0 + 1;

    double center_y = min_fila + radio + 1;
    double center_x = min_col + radio + 1;

    // cout << "center_y: " << center_y << "    center_x: " << center_x << "\n";

    // ---------------------------------------
    // Tomo los Px Py de cada imagen (maximo punto de luminosidad)

    vector<pair<int,int> > maxima_luminosidad(12);

    for (int i = 0; i < 12; i++) {
        Imagen foto = fotos[i];

        double luz_fila = 0;
        double luz_col = 0;
        double max_luz = 0;

        for (int f = 0; f < alto; f++) {
            for (int c = 0; c < ancho; c++) {
                double mivecindad = valorVecindad(f, c, 6, alto, ancho, foto);
                if (mivecindad > max_luz) {
                    max_luz = mivecindad;
                    luz_fila = f;
                    luz_col = c;
                }
            }
        }

        maxima_luminosidad[i] = {luz_fila, luz_col};
    }

    vector<luz> luces(12);

    for (int i = 0; i < 12; i++) {
        double py = maxima_luminosidad[i].first; // fila es eje y
        double px = maxima_luminosidad[i].second;

        double luz_x = (center_x - px);
        double luz_y = (center_y - py);

        // Explicacion en el informe
        double luz_z = sqrt ((radio*radio) - (luz_x*luz_x) - (luz_y*luz_y));

        // Re-traslado. (Eje y es inverso)
        px = px - center_x;
        py = center_y - py;
        luz_z = luz_z - radio/2;

        double norma = NormaVectorial({px, py, luz_z});
        luces[i] = {px/norma, py/norma, luz_z/norma};
    }

    cout << 12 << "\n";
    for (int i = 0; i < 12; i++) {
        cout << fixed << setprecision(10) <<
            luces[i][0] << " " << luces[i][1] << " " << luces[i][2] << "\n";
    }
}