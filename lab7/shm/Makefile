CC = gcc
CFLAGS = -Wall -g -O0
SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}

all:$(OBJS)

%:%.c
	    $(CC) $(CFLAGS)  -o $@ $^
clean:
	    $(RM) $(OBJS) .*.sw? *.txt
