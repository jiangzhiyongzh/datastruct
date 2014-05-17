TGT = a.out
SRCS = test.c
#CROSS_COMPILER = arm-linux-
CC = $(CROSS_COMPILER)gcc
RM = /bin/rm -f    # -号：忽略删除失败的错误，继续执行下去
#CUR_DIR = $(shell pwd)
#HEAD_DIR = $(CUR_DIR)/include
CFLAGS = -Wall -g


$(TGT): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) $< -c

%.d: %.c
	$(CC) $(CFLAGS) -MM $< > $@.$$$$; \
	sed 's/$*.o: /$*.o $*.d: /' $@.$$$$ > $@; \
	$(RM) $@.$$$$

sinclude $(SRCS:.c=.d) 
						 
clean:
	$(RM) $(TGT) $(SRCS:.c=.o) $(SRCS:.c=.d)

.PHONY: clean     #  伪目标
