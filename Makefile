all: sling

sling:
	g++ -I ./include -std=c++0x src/minded_computation.cpp -c -o minded_computation.o
	g++ -I ./include -std=c++0x src/determinacy.cpp -c -o determinacy.o
	g++ -I ./include -std=c++0x main.cpp -c -o main.o
	g++ -pthread minded_computation.o determinacy.o main.o -o sling

clean:
	rm -f *.o
	rm -f sling