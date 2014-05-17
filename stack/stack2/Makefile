TGT := a.out
SUB_DIR := dlist stack
export SUB_TGT := built-in.o
export CURDIR := $(shell pwd)
export CC ?= gcc
export HEADER_DIR := $(CURDIR)/include
export CFLAGS := -g -Wall -I $(HEADER_DIR)
export RM := -rm -f
export LD := ld
export LDFLAGS := -g
$(TGT): $(SUB_DIR)

	$(CC) $(CFLAGS) $(^:=/$(SUB_TGT)) -o $@


$(SUB_DIR):
	make -C $@


%.d:%.c
	$(CC) $(CFLAGS) -MM $< > $@
sinclude $(SRCS:.c=.d)

clean:
	$(RM) $(TGT)
	for dir in $(SUB_DIR);do \
		make -C $$dir clean; \
	done

.PHONY:clean $(SUB_DIR)
