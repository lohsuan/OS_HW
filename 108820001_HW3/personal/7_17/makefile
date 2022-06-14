all: main

.PHONY: exec clean

main: ./main.cpp
	g++ main.cpp -o main -pthread -std=c++11

exec: 
	./main

clean:
	rm ./main