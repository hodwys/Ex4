CC = gcc
FLAGS = -Wall -g
AR = ar
.PHONY: clean all

graph: main.o graphlib.a
	$(CC) $(FLAGS) -o graph main.o graphlib.a

main.o: main.c graph.h 
	$(CC) $(FLAGS) -c main.c 

Dijkstra.o: Dijkstra.c graph.h
	$(CC) $(FLAGS) -c Dijkstra.c

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

graphlib.a: Dijkstra.o graph.o
	$(AR) -rcs graphlib.a Dijkstra.o graph.o

all: graph
clean: 
	rm -f *.o *.a graph
