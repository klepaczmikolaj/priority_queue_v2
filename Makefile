CC = g++

all: test simulation

simulation: priority_queue.o main.o
	$(CC) priority_queue.cpp simulation.cpp -o simulation

test: priority_queue.o test.o
	$(CC) priority_queue.cpp test.cpp -o test

clean: 
	-rm *.o test simulation