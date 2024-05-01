#include <iostream>
#include <vector>
#include <thread> // All multithreading will take place in main - Timothy Sokoloff
#include "/public/read.h"
using namespace std;

// John Brereton, responsible for Intergrating everything.

// Not completely sure how this will work yet
// Maybe the function will recieve input from the client, pass it to the server, and output what the server sends back
void ioFunction(char input) {
	static mutex io_mutex;
	lock_guard lock(io_mutex);

	string output = "";
	if (input == 'W') {}
	else if (input == 'A') {}
	//.....
	cout << output << endl;
}

int main(){
	while (true) {
		jthread t1(ioFunction, param); // thread for i/o

		t1.join();
	}
}
