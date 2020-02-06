run : main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o
	g++ -o run -std=c++11 main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o

util_io.o : util_io.h util_io.cpp util_io.inl
	g++ -c util_io.cpp

2_gen.o : 2_gen.h 2_gen.cpp matrix.o util_io.o
	g++ -c 2_gen.cpp

matrix.o : matrix.h matrix.cpp util_io.o
	g++ -c matrix.cpp

global.o : global.h global.cpp matrix.o
	g++ -c global.cpp

magma_parser.o : magma_parser.h magma_parser.cpp matrix.o util_io.o
	g++ -c magma_parser.cpp

clean : 
	rm *.o run
