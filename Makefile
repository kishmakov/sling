all: sling

sling:
	g++ -I . -std=c++0x src/computation.cpp -c -o computation.o
	g++ -I . -std=c++0x src/state.cpp -c -o state.o
	g++ -I . -std=c++0x main.cpp -c -o main.o
	g++ -pthread computation.o state.o main.o -o sling

clean:
	rm *.o
	rm sling