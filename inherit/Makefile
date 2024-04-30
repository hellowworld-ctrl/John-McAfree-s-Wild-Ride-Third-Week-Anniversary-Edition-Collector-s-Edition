CC = g++
CCFLAGS = -Wall -Wextra -std=c++2a -fsanitize=address

a.out: main.o actor.o
	$(CC) $(CCFLAGS) main.o actor.o 

main.o: main.cc
	$(CC) $(CCFLAGS) -c main.cc

actor.o: actor.cc actor.h
	$(CC) $(CCFLAGS) -c actor.cc

item.o: item.cc item.h
	$(CC) $(CCFLAGS) -c item.cc

clean:
	rm -f a.out *.o
