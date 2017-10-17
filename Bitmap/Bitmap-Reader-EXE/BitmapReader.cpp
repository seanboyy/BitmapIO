#include "BitmapReader.h"

using namespace std;

BitmapReader::BitmapReader(Bitmap bitmap) {
	this->bitmap = bitmap;
}

void BitmapReader::read() {
	ifstream fin;
	fin.open(bitmap.getFilename());
	if (fin.fail()) {
		cerr << "FAILED TO OPEN IMAGE FOR READING" << endl;
		return;
	}
	char temp;
	int streamSize = 0;
	while (!fin.eof()) {
		temp = fin.get();
		streamSize++;
	}
	streamSize--;
	char* fileData = new char[streamSize];
	fin.close();
	fin.open(bitmap.getFilename());
	fin.read(fileData, streamSize);
	bitmap.fromString(fileData);
	fin.close();
}