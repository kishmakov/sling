all: sling

sling:
	g++ -I . -std=c++0x src/minded_computation.cpp -c -o minded_computation.o
	g++ -I . -std=c++0x src/state.cpp -c -o state.o
	g++ -I . -std=c++0x main.cpp -c -o main.o
	g++ -pthread minded_computation.o state.o main.o -o sling

clean:
	rm -f *.o
	rm -f sling