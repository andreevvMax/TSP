output: main.o TSP.o
	gcc main.o TSP.o -o output

main.o: main.cpp
	gcc -c -std=c++20  main.cpp 

TSP.o: TSP.cpp TSP.h
	gcc -c -std=c++20  TSP.cpp

clean:
	rm *.o output
