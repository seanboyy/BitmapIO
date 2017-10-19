#include "BMP_Handler.h"
#include "Bitmap_IO.h"

using namespace bmp;

//load a bitmap image
unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height) {
	//create a bitmap object with name filename
	Bitmap bitmap = Bitmap(filename, width, height);
	//construct the bitmap from a file
	BitmapReader::read(bitmap);
	//set width
	width = Bitmap::getWidth(bitmap);
	//set height
	height = Bitmap::getHeight(bitmap);	
	//unpadded pixel data array from bitmap
	std::vector<uchar> pixelData = Bitmap::getUnpaddedPixelData(bitmap);
	//dynamically allocated primitive array of size (image size)
	unsigned char* pixelDataSimple = new unsigned char[pixelData.size()];
	//convert from vector to primitive array
	for (unsigned int i = 0; i < pixelData.size(); ++i) {
		pixelDataSimple[i] = pixelData[i];
	}
	//return string
	return pixelDataSimple;
}

//save bitmap to file
void BMP_Handler::saveBMP(const char* filename, const unsigned char* data, int width, int height) {
	//pixel data holder
	std::vector<uchar> pixelData;
	//convert from primitive array to vector
	for (int i = 0; i < ((width * 3) * height); ++i) {
		pixelData.push_back(data[i]);
	}
	//create bitmap object with
	//filename = filename
	//width = width
	//height = height
	//x & y resolution = 0
	//pixel list = empty
	//pixel data list = pixelData
	//inverted = true
	//padded = false
	//pixels inverted (BGR not RGB) true
	Bitmap bitmap = Bitmap(filename, width, height, 0, 0, std::vector<Bitmap::Pixel>(0), pixelData, true, false, true);
	//write to file
	BitmapWriter::write(bitmap);
}