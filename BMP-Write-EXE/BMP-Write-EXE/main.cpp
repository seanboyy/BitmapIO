#include "BMPWriter.h"

int main(int argc, char** argv) {
	system("pause");
	BitmapWriter writer = BitmapWriter(1, 1, 3780, "writeTest.bmp");
	writer.fillOneColor(0xFF, 0xFF, 0xFF);
	writer.write();
	BitmapWriter writer2 = BitmapWriter(2, 2, 3780, "black2x2.bmp");
	writer2.fillOneColor(0x00, 0x00, 0x00);
	writer2.write();
	BitmapWriter writer3 = BitmapWriter(3, 3, 3780, "3x3.bmp");
	writer3.fillOneColor(0xFF, 0x00, 0x00);
	writer3.write();
	std::vector<BitmapWriter::Pixel> pixels;
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(BitmapWriter::Pixel(0x00, 0x00, 0xFF));
	BitmapWriter writer4 = BitmapWriter(4, 4, 3780, 3780, pixels, "4x4.bmp");
	writer4.write();
	system("pause");
	return EXIT_SUCCESS;
}