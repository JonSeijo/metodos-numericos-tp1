#ifndef MATRIZ_CPP
#define MATRIZ_CPP

#include <bits/stdc++.h>


using std::string;
using std::vector;
using std::ifstream;
using std::cout;

class Matriz {
    public:

    Matriz() : permutacion(vector<int>()) {
        filas = 0;
        columnas = 0;
    }

    //Perdón por meterle esos ifs pero no me agradan los seg fault
    Matriz (int _filas, int _columnas) : permutacion(vector<int>()) {
        if(_filas < 0 || _columnas < 0){
            throw std::runtime_error("NO SE PUEDEN CREAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
    }

    Matriz multiplicacionEscalar(int x){
        Matriz res = Matriz(this->cantFilas(), this->cantColumnas());
        for(int i=0; i<this->cantFilas();i++){
            for(int j=0; j < this->cantColumnas();j++){
                res[i][j] = m[i][j] * x;
            }
        }
        return res;
    }

    // CONSTRUCTOR DE MATRICES CON CAPACIDADES ESPECIALES
    Matriz (int _filas, int _columnas, string tipo) : permutacion(vector<int>()) {
        if(_filas < 0 || _columnas < 0){
            throw std::runtime_error("NO SE PUEDEN CREAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
        if(tipo == "identidad"){
            for(int i=0; i<this->cantFilas();i++){
                for(int j=0; j < this->cantColumnas();j++){
                    if(i == j) m[i][j] = 1;
                    else m[i][j] = 0;
                }
            }
        }
    }

    Matriz (vector<vector<double> > _m) : permutacion(vector<int>()) {
        m = _m;
        filas = m.size();
        columnas = filas != 0 ? m[0].size() : 0;
    }

    vector<double> &operator [] (int fila) {
        if(fila < 0 || fila >= filas){
            throw std::runtime_error("FILA FUERA DE RANGO");
        }
        return m[fila];
    }

    //Perdón por meterle esos ifs pero no me agradan los seg fault
    void redimensionar(int _filas, int _columnas) {
        if(_filas < 0 || _columnas < 0){
            throw std::runtime_error("NO SE PUEDEN REDIMENSIONAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
    }


    void factorizarLU(bool pivoteo){
    	if(filas <= 0 || columnas <= 0 || filas != columnas){
            throw std::runtime_error("No se puede factorizar esta matriz");
        }
        if(pivoteo){
        	this->triangularConPivoteo(true);
        }
        else{
        	this->triangular(true);
        }
    }
    // Modifica la matriz actual
    // @TODO: Testear con diferentes tamaños
    void triangular(bool LU){
		if(filas <= 0 || columnas <= 0){
            throw std::runtime_error("No se puede triangular esta matriz");
        }
        for (int k = 0; k < filas-1; k++) {
            bool TodoCero = false;
            if (fabs(m[k][k]) < EPSILON) {
            	//Tengo un 0 en la diagonal
            	//Busco primero si puedo hacer una permutacion
            	for(int l = k+1; l < filas; l++){
            		if(fabs(m[l][k]) > EPSILON){
            			//Encontre una fila con la cual hacer permutacion
            			//Si es la primera permutacion que hago, seteo el vector permutacion
            			if(permutacion.size() == 0){
            				for(int numeroFila = 0; numeroFila < filas; numeroFila++){
            					permutacion.push_back(numeroFila);
            				}
            			}
            			//Hago el swap de filas en el vector permutacion
            			int tmpFila = permutacion[k];
            			permutacion[k] = permutacion[l];
            			permutacion[l] = tmpFila;
            			//Hago el swap en la matriz
            			//Si es factorizacion LU entonces tengo que swappear tambien los coeficientes que
            			//estaban siendo guardados, si fuesen todos 0 podría swappear a partir de la columna k-ésima
            			int indice = k;
            			if(LU){
            				indice = 0;
            			}
            			for(int columnaEnLaQueEstoy = indice; columnaEnLaQueEstoy < columnas; columnaEnLaQueEstoy++){
            				double tmpNum = m[k][columnaEnLaQueEstoy];
            				m[k][columnaEnLaQueEstoy] = m[l][columnaEnLaQueEstoy];
            				m[l][columnaEnLaQueEstoy] = tmpNum;
            			}
            			TodoCero = false;
            			break;
            		}
            		else{
            			TodoCero = true;
            		}
            	}
            }
            if(!TodoCero){
           		for(int i = k+1; i < filas; i++){
               		double mult = m[i][k] / m[k][k];

               		// @TODO: Revisar que pasa con el resto de la matriz
               		for (int j = k; j < columnas; j++){
                   		m[i][j] -= mult * m[k][j];
               		}
               		if(LU){
               			m[i][k] = mult;
               		}
                }
            }
       	}
    }
    //LALALALALALALALALALALALALALALALALALALA
    void triangSinPivoteo(bool LU = false){
		if(filas <= 0 || columnas <= 0){
            throw std::runtime_error("No se puede triangular esta matriz");
        }
        for (int k = 0; k < filas-1; k++) {
            bool TodoCero = false;

            if(!TodoCero){
                for(int i = k+1; i < filas; i++){
                    double mult = m[i][k] / m[k][k];

                    if (fabs(mult) < EPSILON) {
                        throw std::runtime_error("TriangSinPivoteo, DIVISION POR CERO");
                    }

               		// @TODO: Revisar que pasa con el resto de la matriz
               		for (int j = k; j < columnas; j++){
                   		m[i][j] -= mult * m[k][j];
               		}
               		if(LU){
               			m[i][k] = mult;
               		}
                }
            }
       	}
    }

    vector<double> GAUSSLOCO(vector<double> &b, bool pivoteo = false) {
        this->AgregarVectorColumna(b);
        this->triangSinPivoteo();
        // @DEBUG luego de triangular
        // std::cout << *this << "\n";
        if (this->existeAlgunaSolucion()) {
            return solTriangSup();
        }

        return vector<double>();
    }


    //LALALALALALALALALALALALALALALALALALLALALA

    void triangularConPivoteo(bool LU) {
        if(filas <= 0 || columnas <= 0){
            throw std::runtime_error("No se puede triangular esta matriz");
        }
        for(int k = 0; k < filas-1; k++) {
            bool TodoCero = false;
            double biggest = fabs(m[k][k]);
            int pivot = k;
            for (int i = k+1; i < filas; i++) {
                if(biggest < fabs(m[i][k])){
                    pivot = i;
                    biggest=fabs(m[i][k]);
                }
            }
            if(pivot != k){
                for(int i = k; i < columnas; i++){
                    vector<double> temp = m[pivot];
                    m[pivot] = m[k];
                    m[k] = temp;
                }
                //SI ES LA PRIMER PERMUTACION SETEO VECTOR
                if(permutacion.size() == 0){
                    for(int numeroFila = 0; numeroFila < filas; numeroFila++){
                        permutacion.push_back(numeroFila);
                    }
                }
                //SWAP EN EL VECTOR PERMUTACION
                int tmpFila = permutacion[k];
                permutacion[k] = permutacion[pivot];
                permutacion[pivot] = tmpFila;
            }
            else{
                if(fabs(m[k][k]) < EPSILON){
                    TodoCero = true;
                }
            }

            if(!TodoCero){
                //GAUSS
                for(int i = k+1; i < filas; i++) {
                    double mult = m[i][k] / m[k][k];
                    for (int j = k; j < columnas; j++) {
                        m[i][j] -= mult * m[k][j];
                    }
                    if(LU){
               			m[i][k] = mult;
               		}
                }
            }
        }
    }

    // Ax = b, devuelve x dado un b
    // @TODO: Ver cuando hay infinitas soluciones
    // retorna: <solucion>, vacio si no existe solucion
    vector<double> resolverSistemaGauss(vector<double> &b, bool pivoteo) {
        this->AgregarVectorColumna(b);
        if(pivoteo){
            this->triangularConPivoteo(false);
        }
        else{
            this->triangular(false);
        }
        // @DEBUG luego de triangular
        // std::cout << *this << "\n";
        if (this->existeAlgunaSolucion()) {
            return solTriangSup();
        }

        return vector<double>();
    }

    //Aplicada para una matriz que ya fue factorizada como LU
    //Se supone que no modifica la matriz
    //Si tiene permutaciones, que sea cuadrada plox
    vector<double> resolverSistemaLU(vector<double>& b){
        //INFORME: Si está peromutada, entonces permuto el b y ya está
        // PLUx = b
        // PPLUx = Pb
        // LUx = Pb
        // LUx = b'
        if(this->permutacion.size() > 0){
        	if(filas <= 0 || columnas <= 0 || filas != columnas){
            	throw std::runtime_error("Casos no contemplados");
        	}
			//Funcion de ordenamiento mala, muy mala
			MergeSortLoco(this->permutacion, b);
        }
        this->AgregarVectorColumna(b);
        vector<double> y = this->solTriangInf();
        this->EliminarVectoresColumna(1);
        this->AgregarVectorColumna(y);
        vector<double> x = this->solTriangSup();
        this->EliminarVectoresColumna(1);

        return x;
    }

    


    bool existeAlgunaSolucion() {
        for (int f = 0; f < filas; f++) {
            bool filaCero = true;

            for (int c = 0; c < columnas-1; c++) {
                if (fabs(m[f][c] - 0) > EPSILON) {  // Si no es cero
                    filaCero = false;
                    break;
                }
            }

            // Si toda la fila es 0 y el b no es cero, entonce no hay solucion
            if (filaCero && fabs(m[f][columnas-1] - 0) > EPSILON) {
                return false;
            }
        }

        return true;
    }

    //Traspone en la misma matriz OJO!!
    void trasponerCuadrada(){
        if(filas != columnas){
            throw std::runtime_error("LA MATRIZ NO ES CUADRADA");
        }
        if(this->filas > 1){
            for(int i = 1; i < filas; i++){
                for(int j = 0; j < i; j++){
                    double temp = this->m[i][j];
                    this->m[i][j] = this->m[j][i];
                    this->m[j][i] = temp;
                }
            }
        }
    }

    //La matriz original se pierde OJO!!
    void trasponer(){
        vector<vector<double> > coeficientes;
        for(int c = 0; c < columnas; c++){
            vector<double> NuevaFila;
            for(int f = 0; f < filas; f++){
                NuevaFila.push_back(this->m[f][c]);
            }
        coeficientes.push_back(NuevaFila);
        }
        this->m = coeficientes;
        int temp = this->filas;
        this->filas = this->columnas;
        this->columnas = temp;
    }

    //La matriz original se mantiene, y retorna otra (que es la traspuesta de la original)
    Matriz traspuesta(){
        vector<vector<double> > coeficientes;
        for(int c = 0; c < columnas; c++){
            vector<double> NuevaFila;
            for(int f = 0; f < filas; f++){
                NuevaFila.push_back(this->m[f][c]);
            }
        coeficientes.push_back(NuevaFila);
        }
        return Matriz(coeficientes);
    }

    Matriz productoM(const Matriz B){
        if(this->columnas != B.filas || this->filas <= 0 || this->columnas <= 0 || B.columnas <= 0){
            throw std::runtime_error("PRODUCTO MATRICIAL INDEFINIDO");
        }
        else{
            vector<vector<double> > coeficientes;
            for(int i = 0; i < this->filas; i++){
                vector<double> vectorFila;
                for(int j = 0; j < B.columnas; j++){
                    double suma = this->m[i][0] * B.m[0][j];
                    for(int k = 1; k < this->columnas; k++){
                        suma += this->m[i][k] * B.m[k][j];
                    }
                    vectorFila.push_back(suma);
                }
                coeficientes.push_back(vectorFila);
            }
            return Matriz(coeficientes);
        }
    }

    Matriz sumaM(const Matriz B){
        Matriz res = Matriz(this->filas, this->columnas);
        if(this->columnas != B.filas || this->filas <= 0 || this->columnas <= 0 || B.columnas <= 0){
            throw std::runtime_error("PRODUCTO MATRICIAL INDEFINIDO");
        }
        else{
            for(int i = 0; i < this->filas; i++){
                for(int j = 0; j < this->columnas; j++){
                       res[i][j] = this->m[i][j] + B.m[i][j];
                    }
                }
            }
            return res;
        }

    //Modifica la matriz original OJO!!!
    void AgregarVectorColumna(vector<double> v) {
        if(this->filas == 0 || this->columnas == 0 || v.size() == 0 || v.size() != this->filas){
            throw std::runtime_error("Tamaño de matriz/vector indefinido para esta operación");
        }
        else{
            this->columnas++;
            for(int k = 0; k < v.size(); k++){
                this->m[k].push_back(v[k]);
            }
        }
    }

    vector<double> EliminarUltimaColumnaYDevolver(){
        if(this->filas <= 0 || this->columnas <= 0){
            throw std::runtime_error("No se puede eliminar una columna de esta matriz");
        }
        else{
            vector<double> ult_col;
            for(int i = 0; i < this->filas; i++){
                ult_col.push_back(this->m[i][this->columnas - 1]);
                this->m[i].pop_back();
            }
            return ult_col;
        }
    }

    //Modifica la matriz OJO!!!
    //Elimina los vectores de DERECHA a IZQUIERDA i.e. empieza a eliminar desde la ÚLTIMA COLUMNA
    void EliminarVectoresColumna(int cantVectores){
        if(cantVectores > this->columnas || cantVectores < 0 || this->filas <= 0 || this->columnas <= 0){
            throw std::runtime_error("No se puede eliminar esa cantidad de columnas en esta matriz");
        }
        else{
            if(cantVectores != 0){ //Para no iterar al pedo por las filas
                for(int l = 0; l < this->filas; l++){
                    for(int k = 0; k < cantVectores; k++){
                        this->m[l].pop_back();
                    }
                }
                this->columnas -= cantVectores;
            }
        }
    }

    // Modifica la matriz
    bool tieneLU() {
        try {
            this->triangSinPivoteo();
        } catch (const std::runtime_error& error) {
            cout << "Error en triangSinPivoteo, posible division por cero\n";
            return false;
        }
        // Si quedo alguna fila con ceros es porque no tiene LU
        for (int f = 0; f < filas; f++) {
            bool conFilaCero = true;
            for (int c = 0; c < columnas; c++) {
                if (fabs(m[f][c] - 0) > EPSILON) {
                    conFilaCero = false;
                }
            }
            if (conFilaCero) {
                return false;
            }
        }

        return true;
    }

    void cholesky(){
            for(int i = 0; i < this->cantFilas(); i++){
                for(int j = 0; j < this->cantColumnas();j++){
                    double suma1 = sumatoria1(j);
                    /*if (m[i][j] - suma1 <= 0) {
                        cout << "RAIZ CEROATIVA\n";
                        cout << m[i][j] << "    " << suma1 << "\n";
                    }*/
                    if(i == j) this->m[i][j] = sqrt(this->m[i][j] - suma1);
                    if(i > j) this->m[i][j] = (1/this->m[j][j]) * (this->m[i][j] - sumatoria2(i,j));
                    if(i < j) this->m[i][j] = 0;
                }
            }
        }


        double sumatoria1(int j){
            double res = 0;
            for(int k = 0; k < j; k++){
                res += pow (this->m[j][k], 2.0);
            }
        }

        double sumatoria2(int i, int j){
            double res = 0;
            for(int k = 0; k < j; k++){
                res += this->m[i][k] * this->m[j][k];
            }
        }

    bool operator==(const Matriz B){
        if(this->filas != B.filas || this->columnas != B.columnas){
            return false;
        }
        else{
            for(int i = 0; i < this->filas; i++){
                for(int j = 0; j < this->columnas; j++){
                    if(fabs(this->m[i][j] - B.m[i][j]) > EPSILON){
                        return false;
                    }
                }
            }
            return true;
        }
    }

    bool operator!=(const Matriz B){
        return !(*this == B);
    }

    int cantFilas(){
        return filas;
    }

    int cantColumnas(){
        return columnas;
    }

    vector<int> DamePermutacion(){
    	return permutacion;
    }

    private:
        double EPSILON = 1e-10;
        vector<vector<double> > m;
        int filas, columnas;
        vector<int> permutacion;

        vector<double> solTriangSup(){
            vector<double> x(columnas-1);
            for (int i = columnas-2; i >= 0; i--) {
                x[i] = m[i][columnas-1] / m[i][i];
                for (int k = i-1; k >= 0; k--) {
                    m[k][columnas-1] -= m[k][i] * x[i];
                }
            }
            return x;
        }

        vector<double> solTriangInf(){
            vector<double> x(columnas-1);
            for (int i = 0; i <= columnas-2; i++) {
                x[i] = m[i][columnas-1];
                for (int k = i+1; k < filas; k++) {
                    m[k][columnas-1] -= m[k][i] * x[i];
                }
            }
            return x;
        }

        void mostrar(std::ostream& os) const{
            os << std::endl;
            if(filas == 0 || columnas == 0){
                os << "[]" << std::endl;
                return;
            }

            for(int i = 0; i < filas; i++){
                for(int j = 0; j < columnas; j++){
                    //Arreglar esto, no hacer caso a los comentarios de abajo, pero volver a dejar como estaba, plox
                    //Lo cambié para testear
                    /*
                    if(m[i][j] == 0){ //CAMBIO, SACAR EL "0"
                        os << "0   " << " ";
                    }
                    else if(m[i][j] < 10){ //CAMBIO, SACAR EL "0"
                        os << "000" << std::setprecision(10) << m[i][j] << " ";
                    }
                    else if(m[i][j] < 100){ //CAMBIO, SACAR EL "0"
                        os << "00" << std::setprecision(100) << m[i][j] << " ";
                    }
                    else if(m[i][j] < 1000){ //CAMBIO, SACAR EL "0"
                        os << "0" << std::setprecision(1000) << m[i][j] << " ";
                    }
                    else{ //CAMBIO: SACAR ESTA RAMA
                        os << std::setprecision(10000) << m[i][j] << " ";
                    }

                    //CAMBIO: DEVOLVER A 10
                    //os << std::fixed << std::setprecision(0) << m[i][j] << " ";
                    */
                    //COMENTO ESTO POR SI ALGUIEN QUIERE USARLO PARA TESTEAR Y DEJO EL
                    //CODIGO ORIGINAL
                    
                    os << (m[i][j] >= 0 ? " " : "");
                    // os << std::fixed << std::setprecision(4) << m[i][j] << " ";
                    if (m[i][j] == 0) {
                        os << "   ";
                    } else {
                        os << std::fixed << std::setprecision(4) << m[i][j] << (m[i][j] > 9 ? " " : "  " );
                    }
                }
                os << std::endl;
            }
            os << std::endl;

            os << "Vector permutacion: \n";
            if(permutacion.size() == 0){
            	os << "Sin permutacion \n";
            }
            else{
            	os << "(";
            	for(int k = 0; k < permutacion.size(); k++){
            		os << permutacion[k] << (k != permutacion.size() -1 ? ", " : ")\n");
            	}
            }
            os << "\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const Matriz &c){
            c.mostrar(os);
            return os;
        };

        //Pre perm y b tienen el mismo tamaño
    void MergeSortLoco(vector<int>& perm, vector<double>& b){
    	for(int actual = 1; actual < perm.size(); actual = 2*actual){
    		for(int inicio = 0; inicio < perm.size() - 1; inicio += 2*actual){
    			int medio = inicio + actual - 1;
    			int fin = minimo(inicio + 2*actual - 1, perm.size() -1);
    			Merge(perm, b, inicio, medio, fin);
    		}
    	}
    }

    int minimo(int a, int b){return (a<b) ? a : b;}

    void Merge(vector<int>& perm, vector<double>& b, int inicio, int medio, int fin){
    	int tam1 = medio - inicio + 1;
    	int tam2 = fin - medio;
    	vector<int> izq(tam1);
    	vector<double> izqD(tam1);
    	vector<int> der(tam2);
    	vector<double> derD(tam2);

    	for(int i = 0; i < tam1; i++){
    		izq[i] = perm[inicio + i];
    		izqD[i] = b[inicio + i];
    	}

    	for(int j = 0; j < tam2; j++){
    		der[j] = perm[1 + medio + j];
    		derD[j] = b[1 + medio + j];
    	}

    	int a = 0; int c = 0; int k = inicio;
    	while(a < tam1 && c < tam2){
    		if(izq[a] <= der[c]){
    			perm[k] = izq[a];
    			b[k] = izqD[a];
    			a++;
    		}
    		else{
    			perm[k] = der[c];
    			b[k] = derD[c];
    			c++;
    		}
    		k++;
    	}

    	while(a < tam1){
    		perm[k] = izq[a];
    		b[k] = izqD[a];
    		a++;
    		k++;
    	}
    	while(c < tam2){
    		perm[k] = der[c];
    		b[k] = derD[c];
    		c++;
    		k++;
    	}
    }
};

#endif