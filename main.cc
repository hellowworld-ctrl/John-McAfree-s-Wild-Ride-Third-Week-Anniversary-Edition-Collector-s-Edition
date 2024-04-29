#include <iostream>
#include <vector>
#include <thread> // All multithreading will take place in main - Timothy Sokoloff
#include "/public/read.h"
using namespace std;

// John Brereton, responsible for Intergrating everything.

int main(){
	while (true) {
		jthread t1(function, param); // thread for i/o
		jthread t2(function, param); // second thread, maybe for networking?
		jthread t3(function, param); // third thread, maybe for battle system etc.

		t1.close();
		t2.close();
		t3.close();
	}
}
