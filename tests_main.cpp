
    std::cout << "TEST : Resolucion de sistema" << std::endl;
    /*Matriz A({
        {6, 15, 55},
        {15, 55, 225},
       {55, 225, 979}
    });
    */
/*
    Matriz B({
        {1, 1, 0},
        {2, 3, 4},
       {0, 1, 1}
    });
    vector<double> b = {2, 6, 13};

    std::cout << "B: \n" << B;

    B.triangular();

    std::cout << "B triangular normal: \n" << B;

    Matriz B1({
        {1, 1, 0},
        {2, 3, 4},
       {0, 1, 1}
    });

    std::cout << "B1: \n" << B1;

    B1.triangularConPivoteo();

    std::cout << "B1 triangular con pivoteo: \n" << B1;

    Matriz C({
        {1, 1, 0},
        {4, 4, 4},
       {1, 0, 0}
    });

    std::cout << "C: \n" << C;

    C.triangular();

    std::cout << "C: \n" << C;

    Matriz C1({
        {1, 1, 0},
        {4, 4, 4},
       {1, 0, 0}
    });

    std::cout << "C1: \n" << C1;

    C1.triangularConPivoteo();

    std::cout << "C1 triangular con pivoteo: \n" << C1;

    Matriz D({
        {1, 1, 0, 0},
        {4, 4, 4, 1},
       {1, 0, 0, 0, 0}
    });

    std::cout << "D: \n" << D;

    D.triangular();

    std::cout << "D: \n" << D;

    Matriz D1({
        {1, 1, 0, 0},
        {4, 4, 4, 1},
       {1, 0, 0, 0, 0}
    });

    std::cout << "D1: \n" << D1;

    D1.triangularConPivoteo();

    std::cout << "D1 triangular con pivoteo \n" << D1;

    Matriz E({
        {1, 0, 0, 1},
        {0, 0, 7, 8},
        {1, 0, 1, 2},
        {1, 0, 0, 4}
    });

    std::cout << "E: \n" << E;

    E.triangular();

    std::cout << "E: \n" << E;

    Matriz E1({
        {1, 0, 0, 1},
        {0, 0, 7, 8},
        {1, 0, 1, 2},
        {1, 0, 0, 4}
    });

    std::cout << "E1: \n" << E1;

    E1.triangularConPivoteo();

    std::cout << "E1 triangular con pivoteo \n" << E1;

    Matriz F({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    });

    std::cout << "F: \n" << F;

    F.triangular();

    std::cout << "F: \n" << F;

    Matriz F1({
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    });

    std::cout << "F1: \n" << F1;

    F1.triangularConPivoteo();

    std::cout << "F1: \n" << F1;


    //std::cout << "B triangulada \n" << B <<"\n";
    /*cout << A;

    Cholesky decomp = Cholesky(A);

    cout << "L: \n";
    cout << decomp;

    Matriz Lt = decomp.L.traspuesta();
    cout << "Lt: \n";
    cout << Lt;

    cout << "LxLt: \n";

    cout << decomp.L.productoM(Lt);
    // resolverSistema modifica la matriz A
    auto rta = A.resolverSistema(b);
    debug(b, "B");
    debug(rta, "X");


    int filas = 5;
    int columnas = 6;
    vector<vector<double> > normasZ;
    int contador = 1;
    for(int i = 0; i < filas; i++){
        vector<double> f;
        for(int j = 1; j <= columnas; j++){
            if(j != 1){
                contador++;
            }
            f.push_back(contador);
        }
        normasZ.push_back(f);
    }
    Matriz M(normasZ);
    M.trasponer();
    std::cout << "MATRIZ COSMICA M: " << std::endl;
    std::cout << M << std::endl;


    Matriz N = obtenerMatrizEcuaciones(M);
    std::cout << "MATRIZ COSMICA N: " << std::endl;
    std::cout << N << std::endl;

    Matriz A = N.traspuesta().productoM(N);
    std::cout << "MATRIZ COSMICA A: " << std::endl;
    std::cout << A << std::endl;
    */
    Matriz prueba({
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    });
    vector<double> v = {1, 1, 1};
    vector<double> b = prueba.resolverSistemaGauss(v, false);
    MostrarVector(b);