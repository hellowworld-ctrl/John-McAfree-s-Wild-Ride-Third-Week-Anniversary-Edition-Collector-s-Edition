CC = g++
CCFLAGS = -Wall -Wextra -std=c++2a -fsanitize=address

a.out: main.o
	$(CC) $(CCFLAGS) main.o

main.o: main.cc
	$(CC) $(CCFLAGS) -c main.cc

clean:
	rm -f a.out *.o
