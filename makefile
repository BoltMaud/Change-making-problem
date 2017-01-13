coins.o:coins.cpp
	g++ -Wall -std=c++11 *.cpp -o run

clean:
	rm -rf *.o  run