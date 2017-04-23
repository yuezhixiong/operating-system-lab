# To run, enter
# make all

all: testbarrier 

testbarrier: main.o barrier.o worker.o 
	gcc -lpthread -o testbarrier main.o barrier.o worker.o 

main.o: main.c barrier.h
	gcc -lpthread -c main.c

barrier.o: barrier.c barrier.h
	gcc -lpthread -c barrier.c

worker.o: worker.c barrier.h
	gcc -lpthread -c worker.c
