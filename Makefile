CC = gcc
CCFLAGS = -Wall -I. -I$(HOME)/local/include
LDFLAGS = -Wall -L$(HOME)/local/lib -lnstdio -lppstream

all: sqb sqf sqi

sqb: sqb.o
	$(CC) $(LDFLAGS) -o sqb sqb.o
sqf: sqf.o
	$(CC) $(LDFLAGS) -o sqf sqf.o
sqi: sqi.o
	$(CC) $(LDFLAGS) -o sqi sqi.o

sqb.o: sqb.c
	$(CC) $(CCFLAGS) -c sqb.c
sqf.o: sqf.c
	$(CC) $(CCFLAGS) -c sqf.c
sqi.o: sqi.c
	$(CC) $(CCFLAGS) -c sqi.c

clean:
	-rm sqb sqf sqi *.o
