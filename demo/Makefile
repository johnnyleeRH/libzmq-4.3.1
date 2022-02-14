# example demo
CC = g++
CURRENT_PATH = $(shell pwd)
INCLUDE = -I${CURRENT_PATH}/
LIBPATH = -L${CURRENT_PATH}/
LIBS = -lmq

CLIENTSRC = client.cc
SERVERSRC = server.cc

all: client server
client: $(CLIENTSRC)
	${CC} $^ ${INCLUDE} ${LIBPATH} ${LIBS} -o $@
server: $(SERVERSRC)
	${CC} $^ ${INCLUDE} ${LIBPATH} ${LIBS} -o $@
clean:
	-rm -f *.o client server
# all:$(subst .c,.o,$(wildcard *.c))
# %.o:%.c
# 	${CC} $^ -I${INCLUDE} ${LIBS} -o $@