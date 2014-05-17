TGT := a.out
SRCS := btree.c test.c dlist.c queue.c

C ?= gcc
CFLAGS := -g -Wall
RM := -rm -f

$(TGT):$(SRCS:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $< -c
%.d:%.c
	$(CC) $(CFLAGS) -MM $< > $@
sinclude $(SRCS:.c=.d)

clean:
	$(RM) $(SRCS:.c=.o) $(TGT) $(SRCS:.c=.d)

.PHONY:clean
