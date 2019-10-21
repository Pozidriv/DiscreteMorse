matrix_test : matrix.o
	g++ -o matrix_test -std=c++17 SanityCheck/matrix_test.cpp -lstdc++fs matrix.o

matrix.o : matrix.h matrix.cpp
	g++ -c matrix.cpp

clean :
	rm *.o a.out matrix_test
