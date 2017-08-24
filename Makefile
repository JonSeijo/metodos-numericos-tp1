SOURCES = main.cpp
CXX = g++ -std=c++11
OBJS = $(SOURCES:.cpp=.o)

LIBS = Imagen.cpp Matriz.cpp recursos/ppmloader/ppmloader.cpp

TARGET = main

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	./$(TARGET)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) *.o
