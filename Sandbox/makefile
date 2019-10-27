CXXFLAGS = -std=c++17
FSLIB = -lstdc++fs
GCC = g++

run : main.cpp matrix.o 2_gen.o sanity_checks.o
	$(GCC) -o run $(CXXFLAGS) main.cpp matrix.o 2_gen.o sanity_checks.o

matrix_test : matrix.o
	$(GCC) -o matrix_test $(CXXFLAGS) SanityCheck/matrix_test.cpp $(FSLIB) matrix.o

matrix.o : matrix.h matrix.cpp
	$(GCC) -c $(CXXFLAGS) matrix.cpp

2_gen.o : 2_gen.h 2_gen.cpp
	$(GCC) -c $(CXXFLAGS) 2_gen.cpp

sanity_checks.o : sanity_checks.h sanity_checks.cpp
	$(GCC) -c $(CXXFLAGS) sanity_checks.cpp

clean :
	rm -f *.o a.out matrix_test run
