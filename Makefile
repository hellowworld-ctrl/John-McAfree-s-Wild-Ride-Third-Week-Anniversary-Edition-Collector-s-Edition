CC = g++

test: test.cc
	$(CC) -o test test.cc -lgtest

clean:
	rm -f a.out test core *.o  
