run : main.cpp matrix.o 2_gen.o sanity_checks.o
	g++ -o run -std=c++17 main.cpp matrix.o 2_gen.o sanity_checks.o

matrix_test : matrix.o
	g++ -o matrix_test -std=c++17 SanityCheck/matrix_test.cpp -lstdc++fs matrix.o

matrix.o : matrix.h matrix.cpp
	g++ -c matrix.cpp

2_gen.o : 2_gen.h 2_gen.cpp
	g++ -c 2_gen.cpp

sanity_checks.o : sanity_checks.h sanity_checks.cpp
	g++ -c sanity_checks.cpp

clean :
	rm *.o a.out matrix_test run
