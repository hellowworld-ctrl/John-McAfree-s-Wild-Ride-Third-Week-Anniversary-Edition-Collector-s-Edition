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
	//keybinds can change later, this is just a rough draft
	if (input == 'w') {} // move forward
	else if (input == 'a') {} // move left
	else if (input == 's') {} // move right
	else if (input == 'd') {} // move backwards
	else if (input == 'i') {} // open inventory
	else if (input == 'm') {} // open map
	else if (input == '1') {} // attack
	else if (input == '2') {} // use item
	else if (input == '3') {} // flee
	//.....
	cout << output << endl;
}

void networkFunction(string input) {
	static mutex network_mutex;
	lock_guard lock(network_mutex);

	// call to server etc. will be here
}

int main() {
	while (true) {
		jthread t1(ioFunction, param); // thread for i/o
		jthread t2(networkFunction, param); // thread for networking

		t1.join();
		t2.join();
	}
}
