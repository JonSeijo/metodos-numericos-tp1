#include "Matriz.cpp"
#include "Luces.cpp"
#include "Auxiliares.cpp"

using namespace std;

int main() {

    // Leo el archivo de luces
    bool luces_catedra = false;
    vector<luz> luces = leerLuces(luces_catedra);

    bool tienenLU = true;

    // Pruebo todas las combinaciones posibles de luces y veo si alguna combinacion es LD
    for (int l1 = 0; l1 < 12; l1++) {
        for (int l2 = l1 + 1; l2 < 12; l2++) {
            for (int l3 = l2 + 1; l3 < 12; l3++) {
                Matriz matrizLuces({
                    luces[l1],
                    luces[l2],
                    luces[l3]
                });

                if (!matrizLuces.tieneLU()) {
                    tienenLU = false;
                    cout << "\n\n\nLas luces: " << l1 << " " << l2 << " " << l3 << " NO tienen LU!!\n";

                    debug(luces[l1], "l1");
                    debug(luces[l2], "l2");
                    debug(luces[l3], "l3");
                }
            }
        }
    }

    if (tienenLU) {
        cout << "Toda posible combinacion tiene LU! :D\n";
    }

}