#include "BMPWriter.h"

using namespace std;

BitmapWriter::BitmapWriter() {
	imageHeight = 0;
	imageWidth = 0;
	xResolution = 0;
	yResolution = 0;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
}

BitmapWriter::BitmapWriter(uint height, uint width) {
	imageHeight = height;
	imageWidth = width;
	xResolution = 0;
	yResolution = 0;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint resolution) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	xResolution = yResolution = resolution;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution, vector<BitmapWriter::Pixel> pixelData) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
	pixels = pixelData;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution, uchar* pixelData) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
	this->pixelData = pixelData;
}

BitmapWriter::~BitmapWriter() {
	delete pixelData;
}

BitmapWriter::Pixel::Pixel() {
	R = 0;
	G = 0;
	B = 0;
}

BitmapWriter::Pixel::Pixel(uchar R, uchar G, uchar B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

ushort BitmapWriter::toLittleEndian(ushort in) {
	ushort out = 0;
	return out;
}

uint BitmapWriter::toLittleEndian(uint in) {
	uint out = 0;
	return out;
}

void BitmapWriter::fillOneColor(BitmapWriter::Pixel target) {
	if (pixels.size() < imageHeight * imageWidth) {
		pixels.clear();
		for (uint x = 0; x < imageHeight; x++) {
			for (uint y = 0; y < imageWidth; y++) {
				pixels.push_back(target);
			}
		}
	}
	else {
		for (uint i = 0; i < pixels.size(); i++) {
			pixels[i] = target;
		}
	}
}

void BitmapWriter::fillOneColor(uchar R, uchar G, uchar B) {
	fillOneColor(BitmapWriter::Pixel(R, G, B));
}

void BitmapWriter::write() {

}

void BitmapWriter::padRows() {
	uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
	uint rowCount = 0;
	uchar* paddedPixelData = new uchar[imageHeight * ((imageWidth * 3) + padAmount)];
	for (uint i = 0; i < imageHeight * (imageWidth * 3); ++i) {
		if ((imageWidth * 3) % i == 0 && i != 0) {
			for (uint j = 0; j < padAmount; ++j) {
				paddedPixelData[i + j] = 0x00;
			}
			rowCount++;
		}
		paddedPixelData[i + rowCount * padAmount] = pixelData[i];
	}
	pixelData = paddedPixelData;
}

void BitmapWriter::fillPixelData() {
	pixelData = new uchar[imageHeight * (imageWidth * 3)];
	for (uint i = 0; i < pixels.size(); ++i) {
		pixelData[i] = pixels[i].B;
		pixelData[i + 1] = pixels[i].G;
		pixelData[i + 2] = pixels[i].R;
	}
}