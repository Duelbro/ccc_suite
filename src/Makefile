CXXFLAGS=-std=c++17

.PHONY: test clean

test: main
	./main

main: main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o main main.cpp 

clean:
	rm -f main.o main
