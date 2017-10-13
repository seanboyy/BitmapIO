#include "BMPWriter.h"

using namespace std;

BitmapWriter::BitmapWriter() {}

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