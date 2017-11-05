#ifndef CHOLESKY_CPP
#define CHOLESKY_CPP


#include "Matriz.cpp"
#include <math.h>
#include <stdio.h>

using namespace std;

class Cholesky{
	public:
		Matriz L;

		Cholesky(Matriz m){
			for(int i = 0; i < m.cantFilas(); i++){
				for(int j = 0; j < m.cantColumnas();j++){
                    double suma1 = sumatoria1(m, j);
                    if (m[i][j] - suma1 <= 0) {
                        cout << "RAIZ CEROATIVA\n";
                        cout << m[i][j] << "    " << suma1 << "\n";
                    }
					if(i == j) m[i][j] = sqrt(m[i][j] - suma1);
					if(i > j) m[i][j] = (1/m[j][j]) * (m[i][j] - sumatoria2(m,i,j));
					if(i < j) m[i][j] = 0;
				}
			}
			L = m;
		}
	private:

		double sumatoria1(Matriz m, int j){
			double res = 0;
			for(int k = 0; k < j; k++){
				res += pow (m[j][k], 2.0);
			}
            return res;
		}

		double sumatoria2(Matriz m, int i, int j){
			double res = 0;
			for(int k = 0; k < j; k++){
				res += m[i][k] * m[j][k];
			}
            return res;
		}

		void mostrar(std::ostream& os){
            os << std::endl;
            for(int i = 0; i < L.cantFilas(); i++){
                for(int j = 0; j < L.cantColumnas(); j++){
                    os << (L[i][j] >= 0 ? " " : "");
                    os << std::fixed << std::setprecision(10) << L[i][j] << " ";
                }
                os << std::endl;
            }
            os << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os,  Cholesky &c){
            c.mostrar(os);
            return os;
        };
};

#endif