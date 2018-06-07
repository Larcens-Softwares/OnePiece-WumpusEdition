all:
	g++	main.cpp	-o main
	./main

clean:
	rm -f main main.o