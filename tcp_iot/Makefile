SRCS = \
	main.c \
	tcp-client.c \
	tcp-server.c

OBJS = $(SRCS:.c=.o)

EXEC = tcp-app
CFLAGS = -g -O0
LDFLAGS =
LIBS =

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

all: $(EXEC)

clean:
	-rm -f *.a *.o $(EXEC)
