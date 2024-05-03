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
		tcp::endpoint endpoint(tcp::v4(), 2467);
		tcp::acceptor acceptor(io_context, endpoint);
		tcp::iostream stream;
		boost::system::error_code ec;
		cout << "Waiting for client to connect\n";
		acceptor.accept(stream.socket(), ec);
		cout << "client has connected\n";
		if (!ec) {
			stream << "https://www.mcafee.com/en-us/antivirus/free.html" << endl;
		}
		else cout << "Sadge.\n";
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
}
