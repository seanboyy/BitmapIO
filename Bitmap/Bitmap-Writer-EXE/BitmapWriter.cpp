#include "BitmapWriter.h"

using namespace std;

BitmapWriter::BitmapWriter(Bitmap bitmap) {
	this->bitmap = Bitmap(bitmap);
}

void BitmapWriter::write() {
	ofstream fout;
	fout.open(bitmap.getFilename());
	if (fout.fail()) {
		cerr << "FAILED TO OPEN IMAGE FOR WRITING" << endl;
		return;
	}
	char* bitmapDataString = bitmap.toString();
	for (uint i = 0; i < bitmap.getFileSize(); i++) {
		fout << bitmapDataString[i];
	}
	fout.close();
}

void BitmapWriter::fill(Bitmap::Pixel pixel) {
	bitmap.fillColor(pixel);
}

void BitmapWriter::fill(uchar R, uchar G, uchar B) {
	bitmap.fillColor(R, G, B);
}