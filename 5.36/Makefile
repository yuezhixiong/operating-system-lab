# To run, enter 
# make all

all: testpid

testpid: test.o pid.o
	gcc  -lpthread -o testpid test.o pid.o

pid.o: pid.c pid.h
	gcc -c pid.c

test.o: test.c pid.h
	gcc -lpthread -c test.c
