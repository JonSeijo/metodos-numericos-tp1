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

Hay *pequeños* cambios con respecto a las luces de la catedra.
El mas notorio es la esfera 7.
La razon creo que es porque hay unas malformaciones mas blancas
 que no se corresponden con la iluminacion mayor,
Entonces el algoritmo considera que esa es la direccion de la luz
 y puede no serlo exactamente.

@Jonno
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

    // ---------------------------------------
    // Obtencion de datos de la mascara

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

    // debug(center_x, "center_x");
    // debug(center_y, "center_y");

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
                if (foto.prom[f][c] > max_luz) {
                    max_luz = foto.prom[f][c];
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

        double luz_x = px - center_x;
        // Recordar que eje y comienza desde arriba
        double luz_y = center_y - py;

        // Explicacion en el informe
        double luz_z = sqrt(radio*radio - luz_x*luz_x - luz_y*luz_y);

        // fila, columna, zeta
        luz luz_raw = {luz_x, luz_y, luz_z};

        luz_x /= NormaVectorial(luz_raw);
        luz_y /= NormaVectorial(luz_raw);
        luz_z /= NormaVectorial(luz_raw);

        luces[i] = {luz_x, luz_y, luz_z};
    }

    cout << 12 << "\n";
    for (int i = 0; i < 12; i++) {
        cout << fixed << setprecision(10) <<
            luces[i][0] << " " << luces[i][1] << " " << luces[i][2] << "\n";
    }
}