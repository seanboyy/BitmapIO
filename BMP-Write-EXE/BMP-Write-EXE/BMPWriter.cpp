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
	filename = ".bmp";
}

BitmapWriter::BitmapWriter(uint height, uint width, string filename) {
	imageHeight = height;
	imageWidth = width;
	xResolution = 0;
	yResolution = 0;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->filename = filename;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint resolution, string filename) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	xResolution = yResolution = resolution;
	this->filename = filename;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution, string filename) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
	this->filename = filename;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution, vector<BitmapWriter::Pixel> pixelData, string filename) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
	pixels = pixelData;
	this->filename = filename;
}

BitmapWriter::BitmapWriter(uint height, uint width, uint xResolution, uint yResolution, uchar* pixelData, string filename) {
	imageHeight = height;
	imageWidth = width;
	compressionScheme = 0;
	imageSizeDelta = 0;
	colorTableValuesUsed = 0;
	colorTableValuesImportant = 0;
	this->xResolution = xResolution;
	this->yResolution = yResolution;
	this->pixelData = pixelData;
	this->filename = filename;
}

BitmapWriter::~BitmapWriter() {
	delete pixelData;
}

BitmapWriter::Pixel::Pixel() {
	R = (uchar)0;
	G = (uchar)0;
	B = (uchar)0;
}

BitmapWriter::Pixel::Pixel(uchar R, uchar G, uchar B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

ushort BitmapWriter::toLittleEndian(ushort in) {
	ushort out = 0;
	uchar b1, b2;
	b1 = (in << 8) >> 8;
	b2 = in >> 8;
	out |= b1;
	out <<= 8;
	out |= b2;
	return out;
}

uint BitmapWriter::toLittleEndian(uint in) {
	uint out = 0;
	uchar b1, b2, b3, b4;
	b1 = (in << 24) >> 24;
	b2 = (in << 16) >> 24;
	b3 = (in << 8) >> 24;
	b4 = in >> 24;
	out |= b1;
	out <<= 8;
	out |= b2;
	out <<= 8;
	out |= b3;
	out <<= 8;
	out |= b4;
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
	ofstream fout;
	fout.open(filename);
	if (fout.fail()) {
		cerr << "FAILED TO OPEN IMAGE FOR WRITING" << endl;
		return;
	}
	if(pixels.size() > 0) fillPixelData();
	padRows();
	//calculate size of image info header (should be 40)
	imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(colorTableValuesUsed) + sizeof(colorTableValuesImportant);
	//calculate size of file header (should be 14)
	headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
	//calculate pixel data offset (should be 54 (unless color table...........))
	pixelDataOffset = imageInfoHeaderLength + headerLength;
	//calculate length of file (should be 54 + pixelDataLength)
	fileLength = headerLength + imageInfoHeaderLength + pixelDataLength;
	//empty string of data to write
	for (uint i = 0; i < sizeof(BITMAP_SIGNATURE); i++) {
		fout << (uchar)((BITMAP_SIGNATURE << (8 * i)) >> ((sizeof(BITMAP_SIGNATURE) - 1) * 8));
	}
	uint fileLengthLE = toLittleEndian(fileLength);
	for (uint i = 0; i < sizeof(fileLengthLE); i++) {
		fout << (uchar)((fileLengthLE << (8 * i)) >> ((sizeof(fileLength) - 1) * 8));
	}
	for (uint i = 0; i < sizeof(RESERVED_BYTES); i++) {
		fout << (uchar)((RESERVED_BYTES << (8 * i)) >> ((sizeof(RESERVED_BYTES) - 1) * 8));
	}
	uint pixelDataOffsetLE = toLittleEndian(pixelDataOffset);
	for (uint i = 0; i < sizeof(pixelDataOffsetLE); i++) {
		fout << (uchar)((pixelDataOffsetLE << (8 * i)) >> ((sizeof(pixelDataOffsetLE) - 1) * 8));
	}
	uint imageInfoHeaderLengthLE = toLittleEndian(imageInfoHeaderLength);
	for (uint i = 0; i < sizeof(imageInfoHeaderLengthLE); i++) {
		fout << (uchar)((imageInfoHeaderLengthLE << (8 * i)) >> ((sizeof(imageInfoHeaderLengthLE) - 1) * 8));
	}
	uint imageWidthLE = toLittleEndian(imageWidth);
	for (uint i = 0; i < sizeof(imageWidthLE); i++) {
		fout << (uchar)((imageWidthLE << (8 * i)) >> ((sizeof(imageWidthLE) - 1) * 8));
	}
	uint imageHeightLE = toLittleEndian(imageHeight);
	for (uint i = 0; i < sizeof(imageHeightLE); i++) {
		fout << (uchar)((imageHeightLE << (8 * i)) >> ((sizeof(imageHeightLE) - 1) * 8));
	}
	ushort planeCountLE = toLittleEndian(PLANE_COUNT);
	for (uint i = 0; i < sizeof(planeCountLE); i++) {
		fout << (uchar)((planeCountLE << (8 * i)) >> ((sizeof(planeCountLE) - 1) * 8));
	}
	ushort colorDepthLE = toLittleEndian(COLOR_DEPTH);
	for (uint i = 0; i < sizeof(colorDepthLE); i++) {
		fout << (uchar)((colorDepthLE << (8 * i)) >> ((sizeof(colorDepthLE) - 1) * 8));
	}
	for (uint i = 0; i < sizeof(compressionScheme); i++) {
		fout << (uchar)((compressionScheme << (8 * i)) >> ((sizeof(compressionScheme) - 1) * 8));
	}
	for (uint i = 0; i < sizeof(imageSizeDelta); i++) {
		fout << (uchar)((imageSizeDelta << (8 * i)) >> ((sizeof(imageSizeDelta) - 1) * 8));
	}
	uint xResolutionLE = toLittleEndian(xResolution);
	for (uint i = 0; i < sizeof(xResolutionLE); i++) {
		fout << (uchar)((xResolutionLE << (8 * i)) >> ((sizeof(xResolutionLE) - 1) * 8));
	}
	uint yResolutionLE = toLittleEndian(yResolution);
	for (uint i = 0; i < sizeof(yResolutionLE); i++) {
		fout << (uchar)((yResolutionLE << (8 * i)) >> ((sizeof(yResolutionLE) - 1) * 8));
	}
	for (uint i = 0; i < sizeof(colorTableValuesUsed); i++) {
		fout << (uchar)((colorTableValuesUsed << (8 * i)) >> ((sizeof(colorTableValuesUsed) - 1) * 8));
	}
	for (uint i = 0; i < sizeof(colorTableValuesImportant); i++) {
		fout << (uchar)((colorTableValuesImportant << (8 * i)) >> ((sizeof(colorTableValuesImportant) - 1) * 8));
	}
	for (uint i = 0; i < pixelDataLength; i++) {
		fout << pixelData[i];
	}
	fout.close();
}

//TODO: MAKE IT WORK!!!!!
void BitmapWriter::padRows() {
	uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
	uint rowCount = 0;
	uchar* paddedPixelData = new uchar[imageHeight * ((imageWidth * 3) + padAmount)];
	for (uint i = 0; i <= imageHeight * (imageWidth * 3); i++) {
		if (i > 0 && i % (imageWidth * 3) == 0) {
			for (uint j = 0; j < padAmount; ++j) {
				paddedPixelData[i + j] = 0xFF;
			}
			rowCount++;
		}
		paddedPixelData[i + rowCount * padAmount] = pixelData[i];
	}
	pixelData = paddedPixelData;
	pixelDataLength += padAmount * rowCount;
}

void BitmapWriter::fillPixelData() {
	pixelData = new uchar[imageHeight * (imageWidth * 3)];
	for (uint i = 0; i < pixels.size(); ++i) {
		pixelData[i] = pixels[i].B;
		pixelData[i + 1] = pixels[i].G;
		pixelData[i + 2] = pixels[i].R;
	}
	pixelDataLength = imageHeight * (imageWidth * 3);
}