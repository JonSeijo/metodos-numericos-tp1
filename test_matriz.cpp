#include <bits/stdc++.h>
#include "Matriz.cpp"


using std::string;
using std::vector;
using std::ifstream;

void testDeMatrices(){
	vector<double> e1 = {1, 0, 0};
    vector<double> e2 = {0, 1, 0};
    vector<double> e3 = {0, 0, 1};
    vector<double> nulo = {0, 0, 0};
    vector<double> uno = {1, 1, 1};

    vector<vector<double> > coeficientes1;
    vector<vector<double> > coeficientes2;
    vector<vector<double> > coeficientes3;
    vector<vector<double> > coeficientes4;

    //identidad
    coeficientes1.push_back(e1);
    coeficientes1.push_back(e2);
    coeficientes1.push_back(e3);

    Matriz id = Matriz(coeficientes1);

    /*
	1 0 0
	0 1 0
	1 1 1
    */
    coeficientes2.push_back(e1);
    coeficientes2.push_back(e2);
    coeficientes2.push_back(uno);

    Matriz matr = Matriz(coeficientes2);

    //nula
    coeficientes3.push_back(nulo);
    coeficientes3.push_back(nulo);
    coeficientes3.push_back(nulo);

    Matriz nula = Matriz(coeficientes3);

    //uno
    coeficientes4.push_back(uno);
    coeficientes4.push_back(uno);
    coeficientes4.push_back(uno);

    Matriz deUnos = Matriz(coeficientes4);



    std::cout << std::endl << "Test producto matricial" << std::endl;

    std::cout << "Porducto id * unos \n" << std::endl;

    Matriz producto = deUnos.productoM(id);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto << std::endl;


    std::cout << "Test operador '=='' :" << std::endl;

	std::cout << "Id == Id?" << std::endl;
	if(id == id){
		std::cout << "Son iguales" << std::endl;
	}
	else{
		std::cout << "HAY UN PROBLEMA" << std::endl;
	}

}