// Any sounds, including the soundtrack and various sound design, will be here. - GIANNI 
#include "Bridges.h"
#include <AudioClip.h>
#include <math.h>
#include "rapidjson/stringbuffer.h"
#include "base64.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std; 
using namespace bridges; 

void die() {
	EXIT_FAILURE; 
} 

struct WaveHeader {
		unsigned int sample_rate;
		unsigned int format_type; 
		unsigned int data_size; 
};

int main() {
	ifstream file ("test.wav" , ios::binary);

	if (!file.is_open()) {
		cout << "This shit ain't opening" << endl; 
		die(); 	
	}


}; 
