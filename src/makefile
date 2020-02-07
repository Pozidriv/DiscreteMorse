run : main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o adjacency_lists.o
	g++ -o run.out -std=c++11 main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o adjacency_lists.o

util_io.o : util_io.h util_io.cpp util_io.inl
	g++ -c util_io.cpp

2_gen.o : 2_gen.h 2_gen.cpp matrix.o util_io.o global.o
	g++ -c 2_gen.cpp

matrix.o : matrix.h matrix.cpp util_io.o
	g++ -c matrix.cpp

global.o : global.h global.cpp matrix.o
	g++ -c global.cpp

magma_parser.o : magma_parser.h magma_parser.cpp matrix.o util_io.o
	g++ -c magma_parser.cpp

adjacency_lists.o : adjacency_lists.h adjacency_lists.cpp matrix.o global.o
	g++ -c adjacency_lists.cpp

clean : 
	rm *.o *.out
