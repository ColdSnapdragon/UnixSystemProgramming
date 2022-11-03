
src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src)) 

all:$(obj)

%.o:%.c
	gcc -c $< -o $@ -Wall -fPIC
