main: main.o
	g++ -Wall -pedantic -g -o main main.o

main.o: main.cpp 
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

clean:
	rm -rf main.o main
