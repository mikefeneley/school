#
# Makefile for server project
#

CC = gcc
CFLAGS =-D_GNU_SOURCE -Wall -g -Werror

LDLIBS=-lpthread -lrt
SHARED_OBJS = csapp.o ip_help.o app_help.o
OBJS = $(SHARED_OBJS) server.o

sysstatd: $(OBJS)
	$(CC) $(CFLAGS) -o sysstatd $(OBJS) $(LDLIBS)

all: $(OBJS)
	$(CC) $(CFLAGS) -o sysstatd $(OBJS) $(LDLIBS)

clean:
		rm -f *~ *.o sysstatd

