#include "/public/read.h"
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	try {
		tcp::iostream stream("localhost", "2345");
		if (!stream) {
			cout << "Unable to connect: " << stream.error().message() << endl;
			return EXIT_FAILURE;
		}
		while (true) {
			string s;
			stream >> s;
			if (!stream) break;
			cout << "Read: " << s << endl;
			stream << "PONG!" << endl;
		}
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}//network things Celeste
