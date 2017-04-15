.PHONY:clean
CC=gcc
CFLAGS=-g -Wall
BIN=main
OBJS=main.o hash.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)

#$@	规则的目标文件名

#$<	规则的第一个依赖文件名

#$^	规则的所有依赖文件名列表