CC = g++

all: test simulation

simulation: priority_queue.o simulation.o
	$(CC) -std=c++11 -pthread priority_queue.cpp simulation.cpp -o simulation

test: priority_queue.o test.o
	$(CC) priority_queue.cpp test.cpp -o test

clean: 
	-rm *.o test simulation