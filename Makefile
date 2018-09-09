# GPL v2.0
CC = gcc
CFLAGS = -Wall
RM = rm -f

all:
  $(CC) $(CFLAGS) ./server.c -o ./server
  $(CC) $(CFLAGS) ./client.c -o ./client

clean:
  $(RM) ./server
  $(RM) ./client
