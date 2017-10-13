#include "BMPWriter.h"

int main(int argc, char** argv) {
	system("pause");
	BitmapWriter writer = BitmapWriter(1, 1, 3870, "writeTest.bmp");
	writer.fillOneColor(0xFF, 0xFF, 0xFF);
	writer.write();
	BitmapWriter writer2 = BitmapWriter(2, 2, 3870, "black2x2.bmp");
	writer2.fillOneColor(0x00, 0x00, 0x00);
	writer2.write();
	system("pause");
	return EXIT_SUCCESS;
}