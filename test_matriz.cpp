#ifndef TESTMATRICES_CPP
#define TESTMATRICES_CPP

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

    try{
        Matriz producto2 = id.productoM(rectangular2x3);
    }
    catch (const std::runtime_error& error) {
        std::cout << "Producto indefinido detectado\n";
        return;
    }

    std::cout  << "\n" << "Porducto rectangular3x2 * rectangular2x3 \n" << std::endl;

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


    std::cout << "Trasponer cuadrada: " << std::endl;
    std::cout << "Original: \n" << matr << std::endl;
    matr.trasponerCuadrada();
    std::cout << "Traspuesta: \n" << matr << std::endl;


    std::cout << "Trasponer rectangular: " << std::endl;
    std::cout << "Original: \n" << rectangular2x3 << std::endl;
    rectangular2x3.trasponer();
    std::cout << "Traspuesta: \n" << rectangular2x3 << std::endl;

    std::cout << "Trasponer rectangular: " << std::endl;
    std::cout << "Original: \n" << rectangular3x2 << std::endl;
    rectangular3x2.trasponer();
    std::cout << "Traspuesta: \n" << rectangular3x2 << std::endl;

    std::cout << "Trasponer y mantener original: " << std::endl;
    std::cout << "Original: \n" << rectangular3x2 << std::endl;
    Matriz pepe = rectangular3x2.traspuesta();
    std::cout << "Traspuesta: \n" << pepe << std::endl;
    std::cout << "Original luego de trasponer: \n" << rectangular3x2 << std::endl;

    std::cout << "Traspuesta de traspuesta es original: \n";
    Matriz trasp = matr.traspuesta();
    trasp.trasponer();

    if(matr == trasp){
    	std::cout << "Dio bien" << std::endl;
    }
    else{
    	std::cout << "TODO MAL" << std::endl;
    }





    vector<double> v4 = {1, 2, 3};
    vector<double> v5 = {4, 5, 6};
    vector<double> v6 = {7, 8, 9};

    vector<vector<double> > coeficientes7;
    coeficientes7.push_back(v4);
    coeficientes7.push_back(v5);
    coeficientes7.push_back(v6);

    Matriz m1 = Matriz(coeficientes7);

    std::cout << "Matriz armada: \n" << m1 << std::endl;
    std::cout << "Le agrego el vector nulo" << std::endl;

    m1.AgregarVectorColumna(nulo);

    std::cout << m1 << std::endl;
    std::cout << "Le saco el vector nulo" << std::endl;

    m1.EliminarVectoresColumna(1);

    std::cout << m1 << std::endl;
    std::cout << "Le agrego varios vectores" << std::endl;

    m1.AgregarVectorColumna(nulo);
    m1.AgregarVectorColumna(e1);
    m1.AgregarVectorColumna(v4);
    m1.AgregarVectorColumna(v6);

    std::cout << m1 << std::endl;
    std::cout << "Le saco 6 vectores columna, debería quedar el (1, 4, 7) traspuesto" << std::endl;

    m1.EliminarVectoresColumna(6);

    std::cout << m1 << std::endl;

    std::cout << "Eliminar Vector y Devolver, lo pruebo con el vector de recien" << std::endl;

    vector<double> unocuatrosiete = m1.EliminarUltimaColumnaYDevolver();
    vector<double> oraculo = {1, 4, 7};
    if(unocuatrosiete == oraculo){
        std::cout << "Todo bien\n" << std::endl;
    }
    else{
        std::cout << "Todo mal" << std::endl;
    }
}

#endif