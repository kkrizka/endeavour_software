CC=g++

OBJS=main.o FPGACom.o UIOCom.o

all: $(OBJS)
	$(CC) $(LDFLAGS) -o test $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

