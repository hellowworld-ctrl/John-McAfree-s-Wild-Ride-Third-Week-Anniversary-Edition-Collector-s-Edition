#include "/public/read.h"
#include <ctime>
#include <iostream>
#include <boost/asio.hpp>
#include <unistd.h>
using namespace std;
using boost::asio::ip::tcp;

int main() {
	try {
		boost::asio::io_context io_context;
		tcp::endpoint endpoint(tcp::v4(), 2345);
		tcp::acceptor acceptor(io_context, endpoint);
		tcp::iostream stream;
		boost::system::error_code ec;
		cout << "Waiting for client to connect\n";
		acceptor.accept(stream.socket(), ec);
		cout << "client has connected\n";
		if (!ec) {
			while (true) {
				stream << "Ping!" << endl;
				string s;
				stream >> s;
				if (!stream) break;
				cout << "Read: " << s << endl;
				usleep(333'333);
			}
		}
		else cout << "Sadge.\n";
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
}
