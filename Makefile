CXXFLAGS=-std=c++17

.PHONY: test clean

test: main
	./main

main: src/main.cpp src/ccc_suite.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o main src/main.cpp

clean:
	rm -f main.o main
