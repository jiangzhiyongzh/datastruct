SUB_DIR :=
SRCS := dlist.c

$(SUB_TGT):$(SRCS:.c=.o) $(SUB_DIR)
	$(LD) $(LDFLAGS) $(SRCS:.c=.o) $(SUB_DIR:=/$(SUB_TGT))  -r -o $@

%.o:%.c
	$(CC) $(CFLAGS) $< -c

%.d:%.c
	$(CC) $(CFLAGS) -MM $< > $@
sinclude $(SRCS:.c=.d)

$(SUB_DIR):
	make -C $@

clean:
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.d) $(SUB_TGT)
	for dir in $(SUB_DIR);do \
		make -C $$dir clean; \
	done

.PHONY:clean $(SUB_DIR)
