#ifndef IMAGEN_CPP
#define IMAGEN_CPP

#include <bits/stdc++.h>
#include "recursos/ppmloader/ppmloader.h"
#include "Matriz.cpp"

using namespace std;

// La imagen guarda los tres colores y ademas el promedio
// Podria hacerse que solo guarde el promedio o solo guarde alguna otra cosa
class Imagen {
    public:
        int ancho, alto;
        Matriz red;
        Matriz green;
        Matriz blue;

        Matriz prom;


    Imagen (string filepath) {
        // Leo la imagen y guardo la data
        uchar* data = NULL;
        ancho = 0;
        alto = 0;
        read_image(filepath, &data, &ancho, &alto);

        // Redimensiono
        red.redimensionar(alto, ancho);
        green.redimensionar(alto, ancho);
        blue.redimensionar(alto, ancho);
        prom.redimensionar(alto, ancho);

        // Guardo el valor de cada pixel
        // f, c = fila, columna
        for (int f = 0; f < alto; f++) {
            for (int c = 0; c < ancho; c++) {
                red[f][c] = getPixel(data, f, c, alto, ancho, 0);
                green[f][c] = getPixel(data, f, c, alto, ancho, 1);
                blue[f][c] = getPixel(data, f, c, alto, ancho, 2);
                prom[f][c] = (red[f][c] + green[f][c] + blue[f][c])/((double)3);
            }
        }
    }


    /* ----------------------------------------- */
    /* ADAPTADO DE PPMLOADER DE LA CATEDRA */
    typedef unsigned char uchar;

    void read_image(std::string filename, uchar** data, int* width, int* height) {
        *data = NULL;
        *width = 0;
        *height = 0;
        PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;

        bool ret = LoadPPMFile(data, width, height, &pt, filename.c_str());
        if (!ret || width == 0|| height == 0|| pt!=PPM_LOADER_PIXEL_TYPE_RGB_8B) {
            throw std::runtime_error("Fallo al leer la imagen.");
        }
    }

    // Pre: la imagen ya fue leida
    // color: 0 red, 1 green, 2 blue
    int getPixel(uchar* data, int i, int j, int height, int width, int color) {
        if (i > height) {
            throw std::runtime_error("El direccionamiento vertical no puede ser mayor a la altura.");
        }
        if (j > width) {
            throw std::runtime_error("El direccionamiento horizontal no puede ser mayor al ancho.");
        }
        return (unsigned int)(data[i*width*3 + j*3 + color]);
    }
    /* ----------------------------------------- */
};

#endif