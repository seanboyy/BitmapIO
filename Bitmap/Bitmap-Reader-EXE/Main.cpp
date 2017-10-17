#include "BitmapReader.h"

int main(int argc, char** argv) {
	system("pause");
	//BitmapReader reader = BitmapReader(Bitmap("whitepixel.bmp"));
	//reader.read();
	//BitmapReader reader2 = BitmapReader(Bitmap("black2x2.bmp"));
	//reader2.read();
	//BitmapReader reader3 = BitmapReader(Bitmap("red3x3.bmp"));
	//reader3.read();
	//system("pause");
	BitmapReader reader4 = BitmapReader(Bitmap("4x4.bmp"));
	reader4.read();
	return EXIT_SUCCESS;
}