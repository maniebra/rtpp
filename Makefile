all:
	g++ main.cpp -o main.o
	./main.o > pic.ppm
