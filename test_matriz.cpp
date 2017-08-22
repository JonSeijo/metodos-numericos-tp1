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
    vector<double> v1 = {3, 8};
    vector<double> v2 = {5, 12};
    vector<double> v3 = {16, 0};

    vector<vector<double> > coeficientes1;
    vector<vector<double> > coeficientes2;
    vector<vector<double> > coeficientes3;
    vector<vector<double> > coeficientes4;
    vector<vector<double> > coeficientes5;
    vector<vector<double> > coeficientes6;

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

    coeficientes5.push_back(uno); 
    coeficientes5.push_back(e3);

    Matriz rectangular2x3 = Matriz(coeficientes5);

    std::cout << "Matriz rectangular 2x3: " << std::endl << rectangular2x3 << std::endl;

    coeficientes6.push_back(v1);
    coeficientes6.push_back(v2);
    coeficientes6.push_back(v3);

    Matriz rectangular3x2 = Matriz(coeficientes6);

    std::cout << "Matriz rectangular 3x2: " << std::endl << rectangular3x2 << std::endl;


    std::cout << std::endl << "Test producto matricial" << std::endl;

    std::cout << "Porducto id * unos \n" << std::endl;

    Matriz producto = deUnos.productoM(id);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto << std::endl;


    std::cout << "Porducto id * rectangular2x3 \n" << std::endl;

    Matriz producto2 = id.productoM(rectangular2x3);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto2 << std::endl;

    std::cout << "Porducto rectangular3x2 * rectangular2x3 \n" << std::endl;

    Matriz producto3 = rectangular3x2.productoM(rectangular2x3);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto3 << std::endl;

    std::cout << "Porducto rectangular2x3 * rectangular3x2 \n" << std::endl;

    Matriz producto4 = rectangular2x3.productoM(rectangular3x2);
    std::cout << "prod hecho" << std::endl;
    std::cout << producto4 << std::endl;



    std::cout << "Test operador '==', '!=' :" << std::endl;

	std::cout << "Id == Id?" << std::endl;
	if(id == id){
		std::cout << "Son iguales" << std::endl;
	}
	else{
		std::cout << "HAY UN PROBLEMA" << std::endl;
	}

	std::cout << "Id == nula?" << std::endl;
	

	if((id == nula || nula == id) && id != nula && nula != id){
		std::cout << "HAY UN PROBLEMA" << std::endl;
	}
	else{
		std::cout << "Son distintos" << std::endl;
	}


		

}