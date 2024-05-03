CC = g++
CCFLAGS = -Wall -Wextra -std=c++2a -O0

main: main.o combat.o generate.o party.o inventory.o item.o actor.o point.o tier.o
	$(CC) -g $(CCFLAGS) main.o combat.o generate.o party.o inventory.o item.o actor.o point.o tier.o -o main

main.o: main.cc
	$(CC) $(CCFLAGS) -c main.cc

combat.o: combat.cc combat.h
	$(CC) $(CCFLAGS) -c combat.cc

generate.o: generate.cc generate.h
	$(CC) $(CCFLAGS) -c generate.cc

party.o: party.cc party.h
	$(CC) $(CCFLAGS) -c party.cc

inventory.o: inventory.cc inventory.h
	$(CC) $(CCFLAGS) -c inventory.cc

item.o: item.cc item.h
	$(CC) $(CCFLAGS) -c item.cc

actor.o: actor.cc actor.h
	$(CC) $(CCFLAGS) -c actor.cc

point.o: point.cc point.h
	$(CC) $(CCFLAGS) -c point.cc

tier.o: tier.cc tier.h
	$(CC) $(CCFLAGS) -c tier.cc

clean:
	rm -f main *.o

