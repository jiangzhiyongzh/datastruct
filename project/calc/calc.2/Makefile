TGT := a.out
SRCS := dlist.c calc_test.c stack.c calc.c
CC ?= gcc
CFLAGS := -g -Wall -D_DEBUG
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
