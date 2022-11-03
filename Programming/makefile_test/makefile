
scr=$(wildcard ./scr/*.c)
obj=$(patsubst ./scr%.c, ./obj%.o, $(scr))

Inc=./inc

Arg=-Wall -g

all:a.out

a.out:$(obj)
	gcc $^ -o $@ -I $(Inc) $(Arg) 

./obj/%.o:./scr/%.c
	gcc -c $< -o $@ -I $(Inc) $(Arg)

clean:
	rm -f $(obj) a.out
