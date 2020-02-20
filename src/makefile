GCC = g++ -std=c++11

run : main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o adjacency_lists.o
	$(GCC) -o run.out main.cpp util_io.o 2_gen.o matrix.o global.o magma_parser.o adjacency_lists.o

util_io.o : util_io.h util_io.cpp util_io.inl
	$(GCC) -c util_io.cpp

2_gen.o : 2_gen.h 2_gen.cpp matrix.o util_io.o global.o
	$(GCC) -c 2_gen.cpp

matrix.o : matrix.h matrix.cpp util_io.o
	$(GCC) -c matrix.cpp

global.o : global.h global.cpp matrix.o
	$(GCC) -c global.cpp

magma_parser.o : magma_parser.h magma_parser.cpp matrix.o util_io.o
	$(GCC) -c magma_parser.cpp

adjacency_lists.o : adjacency_lists.h adjacency_lists.cpp matrix.o global.o
	$(GCC) -c adjacency_lists.cpp

invariants.o : invariants.h graph.o
	$(GCC) -c adjacency_lists.cpp

graph.o : graph.h graph.cpp
	$(GCC) -c graph.cpp

clean : 
	rm *.o *.out
