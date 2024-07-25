CC=gcc
CFLAGS=-g

RM=rm
RMFLAGS=-f

H_FILES=hash.h
IP_FILES=hash.c main.c
OP_FILES=main

clean:
	$(RM) $(RMFLAGS) $(OP_FILES)

format:
	clang-format -style="{IndentWidth: 4}" -i $(IP_FILES) $(H_FILES)

main:
	make clean
	make format
	$(RM) $(RMFLAGS) $(OP_FILES)
	$(CC) $(H_FILES)
	$(CC) $(CFLAGS) $(IP_FILES) -o $(OP_FILES)
	valgrind --track-origins=yes --leak-check=full ./$(OP_FILES)

