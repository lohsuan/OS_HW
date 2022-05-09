all: main

.PHONY: exec clean

main: ./main.c
	g++ main.c -o main -pthread -std=c++11

exec: 
	./main

clean:
	rm ./main