#include "BitmapWriter.h"

int main(int argc, char** argv) {
	system("pause");
	//BitmapWriter writer = BitmapWriter(Bitmap("whitepixel.bmp", 1, 1, 3780, 3780));
	//writer.fill(0xFF, 0xFF, 0xFF);
	//writer.write();
	//BitmapWriter writer2 = BitmapWriter(Bitmap("black2x2.bmp", 2, 2, 3780, 3780));
	//writer2.fill(0x00, 0x00, 0x00);
	//writer2.write();
	//BitmapWriter writer3 = BitmapWriter(Bitmap("red3x3.bmp", 3, 3, 3780, 3780));
	//writer3.fill(0xFF, 0x00, 0x00);
	//writer3.write();
	std::vector<Bitmap::Pixel> pixels;
	pixels.push_back(Bitmap::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(Bitmap::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(Bitmap::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(Bitmap::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(Bitmap::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(Bitmap::Pixel(0xFF, 0xFF, 0xFF));
	pixels.push_back(Bitmap::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(Bitmap::Pixel(0xFF, 0x00, 0x00));
	pixels.push_back(Bitmap::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(Bitmap::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(Bitmap::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(Bitmap::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(Bitmap::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(Bitmap::Pixel(0x00, 0xFF, 0x00));
	pixels.push_back(Bitmap::Pixel(0x00, 0x00, 0xFF));
	pixels.push_back(Bitmap::Pixel(0x00, 0x00, 0xFF));
	BitmapWriter writer4 = BitmapWriter(Bitmap("4x4.bmp", 4, 4, 3780, 3780, pixels));
	writer4.write();
	//BitmapWriter writer5 = BitmapWriter(1024, 1024, 3780, 3780, "1024x1024.bmp");
	//writer5.fill(255, 135, 104);
	//writer5.write();
	system("pause");
	return EXIT_SUCCESS;
}