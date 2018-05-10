CC=g++

OBJS=main.o DeviceCom.o UIOCom.o EndeavourRaw.o

all: $(OBJS)
	$(CC) $(LDFLAGS) -o test $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm test *.o
