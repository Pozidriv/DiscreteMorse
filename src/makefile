run : main.cpp util_io.o 2_gen.o matrix.o
	g++ -o run -std=c++11 main.cpp util_io.o 2_gen.o matrix.o

util_io.o : util_io.h util_io.cpp util_io.inl
	g++ -c util_io.cpp

2_gen.o : 2_gen.h 2_gen.cpp
	g++ -c 2_gen.cpp

matrix.o : matrix.h matrix.cpp
	g++ -c matrix.cpp

clean : 
	rm *.o run
