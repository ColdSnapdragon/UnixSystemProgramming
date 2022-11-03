
scr=$(wildcard *.c) #scr为所有后缀为.c的文件的名字(空格分开),makefile里头没有ls
obj=$(patsubst %c,%o,$(scr)) #在makefile里，$不加括号，匹配的是s而非scr 

ALL:a.out

a.out:$(obj)
	gcc $^ -o $@
#如果用$<, 其表示$(scr)中的第一个文件(我们要把scr看作展开的)

%.o:%.c
	gcc -c $< -o $@
#模式规则下, $<可以逐个表示文件

clean:
	-rm -rf $(obj) a.out
