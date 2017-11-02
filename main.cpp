#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Imagen.cpp"
#include "Auxiliares.cpp"
#include "Luces.cpp"
#include "test_matriz.cpp"
#include "cholesky.cpp"

#include "MatrizEspecialFunciones.cpp"

#include <iostream>
#include <dirent.h>

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
vector<vector<vector<double> > > calcularNormales(Matriz &S,
                        Imagen &foto1, Imagen &foto2, Imagen &foto3, Imagen &mascara) {

    int min_f = 1e8;
    int max_f = -1;
    int min_c = 1e8;
    int max_c = -1;

    for (int f = 0; f < mascara.alto; f++) {
        for (int c = 0; c < mascara.ancho; c++) {
            if (mascara.prom[f][c] > EPSILON) {
                min_f = min(min_f, f);
                min_c = min(min_c, c);
                max_c = max(max_c, c);
                max_f = max(max_f, f);
            }
        }
    }

    int ancho = max_c - min_c + 1;
    int alto = max_f - min_f + 1;

    vector<vector<vector<double> > > normales(alto, vector<vector<double> > (ancho, vector<double>(3, 0)));

    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++) {

            // Si (x,y) NO esta en la mascara, no resuelvo nada, la normal es 0
            if (abs(mascara.prom[f + min_f][c + min_c]) < EPSILON) {
                normales[f][c] = vector<double>(3, 1);

                // Lo clavo en cero porque no esta en la mascara
                normales[f][c][0] = 0;
                normales[f][c][1] = 0;
                normales[f][c][2] = 0;

                continue;
            }

            // (x,y) esta en la mascara, asi que resuelvo el sistema

            Matriz A = S;
            vector<double> b = {foto1.prom[f + min_f][c + min_c], foto2.prom[f + min_f][c + min_c], foto3.prom[f + min_f][c + min_c]};

            // Esto resuelve usando gauss con pivoteo
            vector<double> X = A.resolverSistemaGauss(b, true);

            // Resuelve el sistema utilizando LU
            // vector<double> X = S.resolverSistemaLU(b);

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

bool pertenece(vector<string>& v, string& s){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == s && v[i] != "." && v[i] != ".."){
            return true;
        }
    }
    return false;
}

int main() {

    bool seguir = true;
    while(seguir){
        cout << "\nEl siguiente programa calcula la profundidad de una imagen mediante el metodo de fotometria estereo.";
            cout << "Para hacerlo, se necesitan 12 imagenes del mismo elemento con iluminaciones distintas entre si, ";
            cout << "pero coincidentes con las de la esfera mate (numeradas del 0 al 12, con la sintaxis nombre.x.ppm";
            cout << "donde 'nombre' debe ser el mismo para cada imagen y 'x' un numero entre 0 y 11) y una imagen mascara.";
            cout << " Los 13 archivos deben encontrarse en la siguiente direccion: '/recursos/ppmImagenes/nombre'. \n" << std::endl;

        // Indices de las luces que voy a usar
        std::cout << "\n Inserte nombre de la imagen (ej: caballo, buho, etc):" << std::endl;
        string nombreImagen;
        std::cin >> nombreImagen;


        //Me hago un vector con las subcarpetas
        vector<string> nombresSubcarpetas;

        const char* pathCarpeta = "recursos/ppmImagenes/";
        DIR *carpeta = opendir(pathCarpeta);
        struct dirent *elementos = readdir(carpeta);

        while(elementos != NULL){
            if(elementos -> d_type == DT_DIR){
                nombresSubcarpetas.push_back(elementos -> d_name);
            }
            elementos = readdir(carpeta);
        }

        //FIJARSE QUE SEA UN NOMBRE VALIDO
        while(!pertenece(nombresSubcarpetas, nombreImagen)){
            std::cout << "\n Nombre incorrecto, inserte alguno de los siguientes:" << std::endl;
            MostrarVectorString(nombresSubcarpetas);
            std::cin >> nombreImagen;
        }

        std::cout << "\n Inserte 3 numeros distintos correspondientes a 3 iluminaciones diferentes de la imagen" << std::endl;
        std::cout << " (Del 0 al 11): " << std::endl;

        //Lo hago con strings porque si el usuario mete cualquier cosa cuando espero un int (ej: "askdjfasklfdj") se rompe
        vector<string> posibles = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};

        string primera; string segunda; string tercera;

        std::cout << "\n Inserte primera iluminacion:" << std::endl;
        std::cin >> primera;
        while(!pertenece(posibles, primera)){
            std::cout << "\n Incorrecto, inserte numero valido (del 0 al 11):" << std::endl;
            std::cin >> primera;
        }

        std::cout << "\n Inserte segunda iluminacion:" << std::endl;
        std::cin >> segunda;
        bool repetida = segunda == primera;
        while(!pertenece(posibles, segunda) || repetida){
            if(repetida){
                std::cout << "\n Elija una iluminacion distinta a la anterior." << std::endl;
            }
            else{
                std::cout << "\n Incorrecto, inserte numero valido (del 0 al 11, sin repetir el anterior):" << std::endl;
            }
            std::cin >> segunda;
            repetida = segunda == primera;
        }

        std::cout << "\n Inserte tercera iluminacion." << std::endl;
        std::cin >> tercera;
        repetida = (tercera == primera) || (tercera == segunda);
        while(!pertenece(posibles, tercera) || repetida){
            if(repetida){
                std::cout << "\n Elija una iluminacion distinta a las anteriores:" << std::endl;
            }
            else{
                std::cout << "\n Incorrecto, inserte numero valido (del 0 al 11, sin repetir anteriores):" << std::endl;
            }
            std::cin >> tercera;
            repetida = (tercera == primera) || (tercera == segunda);
        }

        //Paso strings a int
        int prim = std::stoi(primera);
        int seg = std::stoi(segunda);
        int terc = std::stoi(tercera);

        std::cout << "\n Seteando imagenes..." << std::endl;

        // Leo el archivo de luces
        bool luces_catedra = false;
        vector<luz> luces = leerLuces(luces_catedra);

        // Ahora luces es un vector que tiene todas las luces. S la matriz que las contiene
        Matriz S({
            luces[prim],
            luces[seg],
            luces[terc]
        });

        Imagen foto1(getFotoPath(nombreImagen, prim));
        Imagen foto2(getFotoPath(nombreImagen, seg));
        Imagen foto3(getFotoPath(nombreImagen, terc));
        Imagen mascara(getFotoPath(nombreImagen, "mask"));

        ancho = foto1.ancho;
        alto = foto1.alto;

        std::cout << "\n Calculando normales..." << std::endl;

        S.factorizarLU(false);

        vector<vector<vector<double> > > normales;
        normales = calcularNormales(S, foto1, foto2, foto3, mascara);
        alto = normales.size();
        ancho = normales[0].size();

        std::cout << "\n ¡Listo!" << std::endl;

        std::cout << "\n Calculando profundidad...0%" << std::endl;

        cout << "Armo la matriz de profundidades M usando las normales\n";
        vector<map<int, double> > M = armarMatrizProfundidades(normales);

        std::cout << "\n Calculando profundidad...10%" << std::endl;

        cout << "Traspongo M con las dimensiones adecuadas\n";
        vector<map<int, double> > MT = traspuestaEspecial(M, alto*ancho);

        std::cout << "\n Calculando profundidad...20%" << std::endl;

        cout << "Armo la matriz de profundidades\n";
        vector<map<int, double> > A = armarMatrizProfundidadesPosta(normales);
        // vector<map<int, double> > A = matrizPorMatriz(MT, M, alto*ancho);

        std::cout << "\n Calculando profundidad...30%" << std::endl;

        cout << "Encuentro la L de cholesky";
        vector<map<int, double> > L_choles = dameCholesky(A);

        std::cout << "\n Calculando profundidad...40%" << std::endl;

        cout << "Traspongo la L de cholesky";
        vector<map<int, double> > L_choles_T = traspuestaEspecial(L_choles, L_choles.size());

        std::cout << "\n Calculando profundidad...50%" << std::endl;

        // Creo vector de normales a la derecha de la igualdad
        vector<double> v = vectorNormalesXY(normales);

        std::cout << "\n Calculando profundidad...60%" << std::endl;

        cout << "b = Mt * v\n";
        vector<double> b = matrizPorVector(MT, v);

        std::cout << "\n Calculando profundidad...70%" << std::endl;

        cout << "Resuelvo para L de la izquierda\n";
        vector<double> y = resolverInferior(L_choles, b);

        std::cout << "\n Calculando profundidad...80%" << std::endl;

        cout << "Resuelvo para Lt con el resultado anterior\n";
        vector<double> Z = resolverSuperior(L_choles_T, y);

        std::cout << "\n Calculando profundidad...90%" << std::endl;

        cout << "Guardo mi vector de zetas como una matriz\n";
        vector<vector<double> > zetas = recuperarZetas(Z, alto, ancho);

        std::cout << "\n Calculando profundidad...100%" << std::endl;
        std::cout << "\n ¡Calculado!" << std::endl;

        ofstream outputFile;
        outputFile.open("profundidades.txt");

        std::cout << "\n Escribiendo archivo..." << std::endl;

        if(zetas.size() == 0){
            throw std::runtime_error("Matriz de profundidades vacia.\n");
        }

        outputFile << zetas.size() << " " << zetas[0].size() << "\n";
        for (int i = 0; i < zetas.size(); i++) {
            for (int j = 0; j < zetas[0].size(); j++) {
                outputFile << fixed << zetas[i][j] << (j + 1 == ancho ? "" : ",");
            }
            outputFile << "\n";
        }
        outputFile.close();

        std::cout << "\n ¡Listo!" << std::endl;

        std::cout << "\n\n ¿Volver a calcular profundidades de esta u otra imagen?" << std::endl;
        std::cout << "\n Responder: si/no." << std::endl;

        string Respuesta;
        std::cin >> Respuesta;


        while(Respuesta != "si" && Respuesta != "SI" && Respuesta != "Si" && Respuesta != "no" && Respuesta != "NO" && Respuesta != "No"){
            if(Respuesta == "si/no"){
                std::cout << "\n NO TE PASES DE LISTO/A MUCHACHO/A" << std::endl;
            }

            std::cout << "\n Respuesta invalida." << std::endl;
            std::cin >> Respuesta;
        }


        if(Respuesta == "no" || Respuesta == "NO" || Respuesta == "No"){
            seguir = false;
        }
        else{
            std::cout << "\nTener en cuenta que se sobreescribira el archivo 'profundidades.txt'" << std::endl;
        }

    }
}
