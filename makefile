main.out : main.o termigine.o
	g++ -std=c++23 main.o termigine.o -o main.out

main.o: main.cpp 
	g++ -c -std=c++23 main.cpp -o main.o

termigine.o: termigine.cpp
	g++ -c -std=c++23 termigine.cpp -o termigine.o
