CPP=g++
FLAGS= -std=c++11 -O2
LIBS = Matriz.cpp Imagen.cpp recursos/ppmloader/ppmloader.cpp

all: main calibracion testlu

main: main.cpp MatrizEspecialFunciones.cpp $(LIBS)
	$(CPP) $(FLAGS) -o $@ $(LIBS) $<

calibracion: CalibrarLuces.cpp Imagen.cpp Auxiliares.cpp
	$(CPP) $(FLAGS) -o $@ Imagen.cpp recursos/ppmloader/ppmloader.cpp $<

testlu: TestDependenciaLineal.cpp Matriz.cpp Imagen.cpp
	$(CPP) $(FLAGS) -o $@ Matriz.cpp Imagen.cpp recursos/ppmloader/ppmloader.cpp $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f main
