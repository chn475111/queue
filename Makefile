#created by ljk<ljk@xdja.com>
ifndef CC
CC = gcc
endif
CFLAGS := -g -Wall -fPIC
CFLAGS += -D__DEBUG__
CFLAGS += -I./
LDFLAGS += -L./
LIBS += 

SRCS += queue.c main.c

OBJS = $(SRCS:.c=.o)

TARGET = test

all : ${TARGET}
.PHONY : all

${TARGET} : ${OBJS}
	${CC} -o $@ $^ ${LDFLAGS} ${LIBS}
	@echo "$@"

%.o : %.c %.h
	${CC} ${CFLAGS} -o $@ -c $<

.PHONY : clean
clean :
	rm -rf ${OBJS} ${TARGET}
