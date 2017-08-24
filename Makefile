CPP=g++
FLAGS= -std=c++11
LIBS = Matriz.cpp Imagen.cpp recursos/ppmloader/ppmloader.cpp

all: main
	./main

main: main.cpp $(LIBS)
	$(CPP) $(FLAGS) -o $@ $(LIBS) $<

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f main
