CC = g++
CCFLAGS = -Wall -Wextra -std=c++2a -O0
INHERIT_DIR = ./inherit/
MAP_DIR = ./MapStuff/

a.out: MainGameFile.o combat.o generate.o party.o inventory.o item.o actor.o point.o tier.o  
	$(CC) -g $(CCFLAGS) MainGameFile.o -lncurses combat.o generate.o party.o inventory.o item.o actor.o point.o tier.o 

MainGameFile.o: MainGameFile.cc
	$(CC) $(CCFLAGS) -c  MainGameFile.cc -lncurses
 
combat.o: $(INHERIT_DIR)combat.cc $(INHERIT_DIR)combat.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)combat.cc

generate.o: $(INHERIT_DIR)generate.cc $(INHERIT_DIR)generate.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)generate.cc

party.o: $(INHERIT_DIR)party.cc $(INHERIT_DIR)party.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)party.cc

inventory.o: $(INHERIT_DIR)inventory.cc $(INHERIT_DIR)inventory.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)inventory.cc

item.o: $(INHERIT_DIR)item.cc $(INHERIT_DIR)item.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)item.cc

actor.o: $(INHERIT_DIR)actor.cc $(INHERIT_DIR)actor.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)actor.cc

point.o: $(INHERIT_DIR)point.cc $(INHERIT_DIR)point.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)point.cc

tier.o: $(INHERIT_DIR)tier.cc $(INHERIT_DIR)tier.h
	$(CC) $(CCFLAGS) -c $(INHERIT_DIR)tier.cc

clean:
	rm -f a.out *.o
