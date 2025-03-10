SRCS = \
	main.c \
	tcp-client.c \
	response.c \
	tcp-server.c \
	parse_json.c	

OBJS = $(SRCS:.c=.o)

EXEC = tcp-app
CFLAGS = -g -O0
LDFLAGS =
LIBS = -lcjson

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

all: $(EXEC)

clean:
	-rm -f *.a *.o $(EXEC)
