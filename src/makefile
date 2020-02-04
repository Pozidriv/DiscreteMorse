run : main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o
	g++ -o run -std=c++11 main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o

util_io.o : util_io.h util_io.cpp util_io.inl
	g++ -c util_io.cpp

2_gen.o : 2_gen.h 2_gen.cpp
	g++ -c 2_gen.cpp

matrix.o : matrix.h matrix.cpp
	g++ -c matrix.cpp

global.o : global.h matrix.o
	g++ -c global.cpp matrix.o

magma_parser.o : magma_parser.h magma_parser.cpp
	g++ -c magma_parser.cpp

clean : 
	rm *.o run
