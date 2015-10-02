main: main.o Converter.o
	g++ -g -std=c++11 main.o Converter.o -o main

main.o: main.cpp Converter.o
	g++ -c -g -std=c++11 main.cpp

Converter.o: Converter.cpp 
	g++ -c -g -std=c++11 Converter.cpp

clean:
	rm -f *~ *.o
