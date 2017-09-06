#ifndef TESTMATRICES_CPP
#define TESTMATRICES_CPP

#include <bits/stdc++.h>
#include "Matriz.cpp"
#include "Luces.cpp"
#include <ctime>

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

double myRand(){
  return ((double)rand() / RAND_MAX);
}

void testTriangularVSLU(){

    vector<int> indexes = {4, 5, 6};

    // Leo el archivo de luces
    bool luces_catedra = true;
    vector<luz> luces = leerLuces(luces_catedra);

    // Ahora luces es un vector que tiene todas las luces. S la matriz que las contiene
    Matriz S({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });

    Matriz LU({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });




    int N;
    string path;
    string path2;
    std::cout<<"Ingrese la cantidad de pixeles"<<std::endl;
    std::cin>>N;
    std::cout<<"Ingrese el archivo de salida NOLU"<<std::endl;
    std::cin>>path;
    std::cout<<"Ingrese el archivo de salida LU"<<std::endl;
    std::cin>>path2;

    std::fstream fs("experimentos/TriangVSLU/" + path , std::ios::out | std::ios::app);
    std::fstream fsLU("experimentos/TriangVSLU/" + path2 , std::ios::out | std::ios::app);

    if(!fs.is_open()){
        cout<<"no se habrio wacho"<<endl;
    }
    
    
    
    vector< vector<double> > bs(N, vector<double>(3,0));
    srand(N);

    for(int i =0; i<N ; i++){
        bs[i][0] = myRand();
        bs[i][1] = myRand();
        bs[i][2] = myRand();
    }

    
    vector<double> tiemposNOLU((N),0);
    vector<double> tiemposLU((N),0);

    LU.factorizarLU(false);

    for(int j=10; j<N ; j+=100){
        double tiempoLU = 0;
        double tiempoNOLU = 0;
        for(int k =0; k<100; k++){
            for(int i =1; i<j ; i++){

                
                Matriz noLU = S;
                clock_t start = clock();
                noLU.resolverSistemaGauss(bs[i],false);
                clock_t end = clock();
                double segs = (double)(end-start) / CLOCKS_PER_SEC;
                tiempoNOLU+=segs;
            


                clock_t start2 = clock();
                LU.resolverSistemaLU(bs[i]);
                clock_t end2 = clock();
                double segs2 = (double)(end2-start2) / CLOCKS_PER_SEC;
                tiempoLU+=segs2;


            }
        }      
        fs<<tiempoNOLU/100<<endl;
        fsLU<<tiempoLU/100<<endl;
    }



    fs.close();
    fsLU.close();


}


void testTriangularVSLUEnDimension(){

    vector<int> indexes = {4, 5, 6};

    // Leo el archivo de luces
    bool luces_catedra = true;
    vector<luz> luces = leerLuces(luces_catedra);

    // Ahora luces es un vector que tiene todas las luces. S la matriz que las contiene

    Matriz S({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });

    Matriz LU({
        luces[ indexes[0] ],
        luces[ indexes[1] ],
        luces[ indexes[2] ]
    });




    int N;
    string path;
    string path2;
    std::cout<<"Ingrese la cantidad de pixeles"<<std::endl;
    std::cin>>N;
    std::cout<<"Ingrese el archivo de salida NOLU"<<std::endl;
    std::cin>>path;
    std::cout<<"Ingrese el archivo de salida LU"<<std::endl;
    std::cin>>path2;

    std::fstream fs("experimentos/TriangVSLUEnDim/" + path , std::ios::out | std::ios::app);
    std::fstream fsLU("experimentos/TriangVSLUEnDim/" + path2 , std::ios::out | std::ios::app);

    if(!fs.is_open()){
        cout<<"no se habrio wacho"<<endl;
    }
    
    
    int po=0;
    cout<<po++<<endl;
    
    srand(N);
cout<<po++<<endl;
    for(int j=10; j<N ; j+=10){
        vector< double> bs(j, 0);
        vector<vector<double> > m(j, vector<double>(j,0));  
cout<<po++<<endl;

        for(int i =0; i<j ; i++){
            cout<<"insertando bs: "<<i<<endl;
            bs[i] = myRand();
            for(int k =0; k <=i ; k++){
                cout<<"insertando m: "<<i<<", "<<k<<endl;
                m[i][k] = myRand()+1;
            }
        }
cout<<po++<<endl;
        Matriz S(m);
        Matriz LU(m);
        cout<<po++<<endl;
cout<<po++<<endl;
        LU.factorizarLU(false);
cout<<po++<<endl;
        double tiempoLU = 0;
        double tiempoNOLU = 0;
        cout<<po++<<endl;
        for(int k =0; k<100; k++){

                
            Matriz noLU = S;
            clock_t start = clock();
            noLU.resolverSistemaGauss(bs,false);
            clock_t end = clock();
            double segs = (double)(end-start) / CLOCKS_PER_SEC;
            tiempoNOLU+=segs;
        cout<<po++<<endl;


            clock_t start2 = clock();
            LU.resolverSistemaLU(bs);
            clock_t end2 = clock();
            double segs2 = (double)(end2-start2) / CLOCKS_PER_SEC;
            tiempoLU+=segs2;


        }      
        cout<<po++<<endl;
        fs<<tiempoNOLU/100<<endl;
        fsLU<<tiempoLU/100<<endl;

        cout<<"ciclo: " <<j<<endl;
    }



    fs.close();
    fsLU.close();


}

#endif