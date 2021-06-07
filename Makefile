CC=g++ -std=c++17

CC_FLAG=-Wl,-rpath=.
LD_FLAG=-L.

LIB = -lboost_unit_test_framework
LIB += -llru

all:
	$(CC) -c -fPIC lru.cpp
	$(CC) -shared -o liblru.so lru.o
	make test
	make exe
test:
	$(CC) -o test test.cpp $(LD_FLAG) $(CC_FLAG) $(LIB)
	
run_test:
	./test --log_level=test_suite

exe:
	$(CC) -o lru main.cpp lru.cpp
clean:
	rm *.o *.so test lru
