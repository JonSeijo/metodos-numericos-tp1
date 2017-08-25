#ifndef MATRIZ_CPP
#define MATRIZ_CPP

#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;

class Matriz {
    public:

    Matriz() {
        filas = 0;
        columnas = 0;
    }

    //Perdón por meterle esos ifs pero no me agradan los seg fault
    Matriz (int _filas, int _columnas) {
        if(_filas < 0 || _columnas < 0){
            throw std::runtime_error("NO SE PUEDEN CREAR MATRICES CON UNA CANTIDAD DE FILAS O COLUMNAS NEGATIVAS");
        }
        filas = _filas;
        columnas = _columnas;
        m.assign(filas, vector<double>(columnas, 0));
    }

    Matriz (vector<vector<double> > _m) {
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

    // Modifica la matriz actual
    // @TODO: Testear con diferentes tamaños
    // @TODO: Faltaria que no se rompa cuando encuentra ceros.
    // @TODO: Faltaria que guarde la factorizacion LU
    void triangular() {
        for (int k = 0; k < filas-1; k++) {

            if (fabs(m[k][k] - 0) <= EPSILON) {
                std::cerr << "k: " << k << "    m[k][k]: " << m[k][k] << "\n";
                std::cerr << *this;
                throw std::runtime_error("CERO EN LA DIAGONAL!");
            }

            for (int i = k+1; i < filas; i++) {
                double mult = m[i][k] / m[k][k];

                // @TODO: Revisar que pasa con el resto de la matriz
                for (int j = k; j < columnas; j++) {
                    m[i][j] -= mult * m[k][j];
                }
            }
        }
    }

    void triangularConPiboteo() {
        for (int k = 0; k < filas-1; k++) {



            double biggest = fabs(m[k][k]);
            int pivot = k;
            for (int i = k+1; i < filas; i++) {
                if(biggest < fabs(m[i][k])){
                    pivot = i;
                    biggest=fabs(m[i][k]);
                }
            }
            std::cout<<"el biggest es" << biggest<<std::endl;
            if (fabs(biggest - 0) <= EPSILON) {
                std::cerr << *this;
                throw std::runtime_error("NO PUDE SALVAR EL 0 EN LA DIAGONAL!");
            }

            if(pivot != k){
                for(int i = k; i < columnas; i++){
                    int temp = m[pivot][i];
                    m[pivot][i] = m[k][i];
                    m[k][i] = temp;
                }
            }

            for (int i = k+1; i < filas; i++) {
                double mult = m[i][k] / m[k][k];
                for (int j = k; j < columnas; j++) {
                    m[i][j] -= mult * m[k][j];
                }
            }
        }
    }

    // Ax = b, devuelve x dado un b
    // @TODO: Ver cuando hay infinitas soluciones
    // retorna: <solucion>, vacio si no existe solucion
    vector<double> resolverSistema(vector<double> &b, bool pivoteo = false) {
        this->AgregarVectorColumna(b);
        if(pivoteo){
            this->triangularConPiboteo();
        }else{
            this->triangular();
        }
        

        // @DEBUG luego de triangular
        // std::cout << *this << "\n";

        if (this->existeAlgunaSolucion()) {
            // La matriz tiene una columna extra por el b
            vector<double> x(columnas-1);
            for (int i = columnas-2; i >= 0; i--) {
                x[i] = m[i][columnas-1] / m[i][i];
                for (int k = i-1; k >= 0; k--) {
                    m[k][columnas-1] -= m[k][i] * x[i];
                }
            }
            return x;
        }

        return vector<double>();
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

    private:
        double EPSILON = 1e-10;
        vector<vector<double> > m;
        int filas, columnas;

        void mostrar(std::ostream& os) const{
            os << std::endl;
            if(filas == 0 || columnas == 0){
                os << "[]" << std::endl;
                return;
            }

            for(int i = 0; i < filas; i++){
                for(int j = 0; j < columnas; j++){
                    os << (m[i][j] >= 0 ? " " : "");
                    os << std::fixed << std::setprecision(10) << m[i][j] << " ";
                }
                os << std::endl;
            }
            os << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matriz &c){
            c.mostrar(os);
            return os;
        };



};

#endif