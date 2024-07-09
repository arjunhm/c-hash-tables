CC=gcc
CFLAGS=-g
RM=rm
RMFLAGS=-f
LP_OPFILE=lp
OPFILES=$(LP_OPFILE)
HFILE=hash.h
LP_IPFILE=lp_hash.c

format:
	clang-format -style="{IndentWidth: 4}" -i $(LP_IPFILE) $(HFILE)

clean:
	$(RM) $(RMFLAGS) $(OPFILES)

lp:
	$(CC) $(HFILE)
	$(CC) $(CFLAGS) -o $(LP_OPFILE) $(LP_IPFILE)

val_lp:
	valgrind --leak-check=full ./$(LP_OPFILE)

all_lp:
	make clean
	make format
	make lp
	make val_lp

