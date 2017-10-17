#include "BMP_Handler.h"
#include "Bitmap_IO.h"

unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height) {
	Bitmap bitmap = Bitmap(filename, width, height);
	BitmapReader::read(bitmap);
	std::vector<unsigned char> pixelData = Bitmap::Bitmap::getUnpaddedPixelData(bitmap);
	unsigned char* pixelDataSimple = new unsigned char[pixelData.size()];
	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		pixelDataSimple[i] = pixelData[i];
	}
	return pixelDataSimple;
}

void BMP_Handler::saveBMP(const char* filename, const unsigned char* data, int width, int height) {
	std::vector<unsigned char> pixelData;
	for (int i = 0; i < ((width * 3) * height); ++i) {
		pixelData.push_back(data[i]);
	}
	Bitmap bitmap = Bitmap(filename, width, height, 0, 0, std::vector<Bitmap::Pixel>(0), pixelData, true, false, true);
	BitmapWriter::write(bitmap);
}