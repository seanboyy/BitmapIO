#include "Bitmap.h"

using namespace std;

Bitmap::Bitmap(const Bitmap& other) {
	*this = other;
}

Bitmap::Bitmap(const char* filename, uint width, uint height, uint xRes, uint yRes, vector<Pixel> pixels, vector<uchar> pixelData, bool flagInverted, bool flagPadded, bool flagPixelsInverted, uint compressionScheme, uint imageSizeDelta, uint colorTableValuesUsed, uint colorTableValuesImportant){
	assert(width > 0 && height > 0);
	imageWidth = width;
	imageHeight = height;
	xResolution = xRes;
	yResolution = yRes;
	this->pixels = pixels;
	this->pixelData = pixelData;
	this->flagInverted = flagInverted;
	this->flagPadded = flagPadded;
	this->flagPixelsInverted = flagPixelsInverted;
	this->filename = filename;
	this->compressionScheme = compressionScheme;
	this->imageSizeDelta = imageSizeDelta;
	this->colorTableValuesImportant = colorTableValuesImportant;
	this->colorTableValuesUsed = colorTableValuesUsed;
	headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
	imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(this->compressionScheme) + sizeof(this->imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(this->colorTableValuesImportant) + sizeof(this->colorTableValuesUsed);
	pixelDataOffset = headerLength + imageInfoHeaderLength;
}

char* Bitmap::toString() {
	fillPixelData();
	padRows();
	imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(colorTableValuesUsed) + sizeof(colorTableValuesImportant);
	headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
	pixelDataOffset = imageInfoHeaderLength + headerLength;
	fileLength = headerLength + imageInfoHeaderLength + pixelData.size();
	char* dataToWrite = new char[fileLength];
	for (uint i = 0; i < sizeof(BITMAP_SIGNATURE); i++) {
		dataToWrite[i] = (BITMAP_SIGNATURE << (8 * i)) >> ((sizeof(BITMAP_SIGNATURE) - 1) * 8);
	}
	uint fileLengthLE = toLittleEndian(fileLength);
	for (uint i = 0; i < sizeof(fileLengthLE); i++) {
		dataToWrite[sizeof(BITMAP_SIGNATURE) + i] = (fileLengthLE << (8 * i)) >> ((sizeof(fileLength) - 1) * 8);
	}
	for (uint i = 0; i < sizeof(RESERVED_BYTES); i++) {
		dataToWrite[sizeof(BITMAP_SIGNATURE) + sizeof(fileLengthLE) + i] = (RESERVED_BYTES << (8 * i)) >> ((sizeof(RESERVED_BYTES) - 1) * 8);
	}
	uint pixelDataOffsetLE = toLittleEndian(pixelDataOffset);
	for (uint i = 0; i < sizeof(pixelDataOffsetLE); i++) {
		dataToWrite[sizeof(BITMAP_SIGNATURE) + sizeof(fileLengthLE) + sizeof(RESERVED_BYTES) + i] = (pixelDataOffsetLE << (8 * i)) >> ((sizeof(pixelDataOffsetLE) - 1) * 8);
	}
	uint imageInfoHeaderLengthLE = toLittleEndian(imageInfoHeaderLength);
	for (uint i = 0; i < sizeof(imageInfoHeaderLengthLE); i++) {
		dataToWrite[headerLength + i] = (imageInfoHeaderLengthLE << (8 * i)) >> ((sizeof(imageInfoHeaderLengthLE) - 1) * 8);
	}
	uint imageWidthLE = toLittleEndian(imageWidth);
	for (uint i = 0; i < sizeof(imageWidthLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + i] = (imageWidthLE << (8 * i)) >> ((sizeof(imageWidthLE) - 1) * 8);
	}
	uint imageHeightLE = toLittleEndian(imageHeight);
	for (uint i = 0; i < sizeof(imageHeightLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + i] = (imageHeightLE << (8 * i)) >> ((sizeof(imageHeightLE) - 1) * 8);
	}
	ushort planeCountLE = toLittleEndian(PLANE_COUNT);
	for (uint i = 0; i < sizeof(planeCountLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + i] = (planeCountLE << (8 * i)) >> ((sizeof(planeCountLE) - 1) * 8);
	}
	ushort colorDepthLE = toLittleEndian(COLOR_DEPTH);
	for (uint i = 0; i < sizeof(colorDepthLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + i] = (colorDepthLE << (8 * i)) >> ((sizeof(colorDepthLE) - 1) * 8);
	}
	for (uint i = 0; i < sizeof(compressionScheme); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + i] = (compressionScheme << (8 * i)) >> ((sizeof(compressionScheme) - 1) * 8);
	}
	for (uint i = 0; i < sizeof(imageSizeDelta); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + sizeof(compressionScheme) + i] = (imageSizeDelta << (8 * i)) >> ((sizeof(imageSizeDelta) - 1) * 8);
	}
	uint xResolutionLE = toLittleEndian(xResolution);
	for (uint i = 0; i < sizeof(xResolutionLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + i] = (xResolutionLE << (8 * i)) >> ((sizeof(xResolutionLE) - 1) * 8);
	}
	uint yResolutionLE = toLittleEndian(yResolution);
	for (uint i = 0; i < sizeof(yResolutionLE); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolutionLE) + i] = (yResolutionLE << (8 * i)) >> ((sizeof(yResolutionLE) - 1) * 8);
	}
	for (uint i = 0; i < sizeof(colorTableValuesUsed); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolutionLE) + sizeof(yResolutionLE) + i] = (colorTableValuesUsed << (8 * i)) >> ((sizeof(colorTableValuesUsed) - 1) * 8);
	}
	for (uint i = 0; i < sizeof(colorTableValuesImportant); i++) {
		dataToWrite[headerLength + sizeof(imageInfoHeaderLengthLE) + sizeof(imageWidthLE) + sizeof(imageHeightLE) + sizeof(planeCountLE) + sizeof(colorDepthLE) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolutionLE) + sizeof(yResolutionLE) + sizeof(colorTableValuesUsed) + i] = (colorTableValuesImportant << (8 * i)) >> ((sizeof(colorTableValuesImportant) - 1) * 8);
	}
	for (uint i = 0; i < pixelData.size(); i++) {
		dataToWrite[pixelDataOffset + i] = pixelData[i];
	}
	return dataToWrite;
} 

void Bitmap::fromString(char* bitmapData) {
	uint cursor = 0;
	ushort bmpsig = getShortFromStream(cursor, bitmapData);
	assert(bmpsig == BITMAP_SIGNATURE);
	cursor += sizeof(bmpsig);
	fileLength = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(fileLength);
	uint reserve = getIntFromStream(cursor, bitmapData);
	assert(reserve == RESERVED_BYTES);
	cursor += sizeof(reserve);
	pixelDataOffset = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(pixelDataOffset);
	imageInfoHeaderLength = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(imageInfoHeaderLength);
	imageWidth = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(imageWidth);
	imageHeight = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(imageWidth);
	ushort planes = toBigEndian(getShortFromStream(cursor, bitmapData));
	assert(planes == PLANE_COUNT);
	cursor += sizeof(planes);
	ushort colorbits = toBigEndian(getShortFromStream(cursor, bitmapData));
	assert(colorbits == COLOR_DEPTH);
	cursor += sizeof(colorbits);
	compressionScheme = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(compressionScheme);
	imageSizeDelta = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(imageSizeDelta);
	xResolution = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(xResolution);
	yResolution = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(yResolution);
	colorTableValuesUsed = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(colorTableValuesUsed);
	colorTableValuesImportant = toBigEndian(getIntFromStream(cursor, bitmapData));
	cursor += sizeof(colorTableValuesImportant);
	assert(cursor == pixelDataOffset);
	if (pixelData.size() > 0) pixelData.clear();
	for (; cursor < fileLength; cursor++) {
		pixelData.push_back(bitmapData[cursor]);
	}
	assert(cursor == fileLength);
	flagPadded = true;
	flagInverted = true;
	unpadRows();
	fillPixel();
}

ushort Bitmap::getShortFromStream(uint start, char* stream) {
	ushort out = stream[start];
	out <<= 8;
	out |= stream[start + 1];
	return out;
}

uint Bitmap::getIntFromStream(uint start, char* stream) {
	uint out = stream[start];
	out <<= 8;
	out |= stream[start + 1];
	out <<= 8;
	out |= stream[start + 2];
	out <<= 8;
	out |= stream[start + 3];
	return out;
}

void Bitmap::fillPixelData() {
	if (!flagInverted) invertRows();
	if (pixelData.size() > 0 && !flagPixelsInverted && !flagPadded) {
		if (pixels.size() > 0) {
			pixelData.clear();
		}
		else {
			for (uint i = 0; i < pixelData.size(); ++i) {
				uchar temp = pixelData[i + (3 * i)];
				pixelData[i + (3 * i)] = pixelData[i + 2 + (3 * i)];
				pixelData[i + 2 + (3 * i)] = temp;
			}
			return;
		}
	}
	for (uint i = 0; i < pixels.size(); ++i) {
		pixelData.push_back(pixels[i].B);
		pixelData.push_back(pixels[i].G);
		pixelData.push_back(pixels[i].R);
	}
}

void Bitmap::fillPixel() {
	if (pixels.size() > 0) pixels.clear();
	for (uint i = 0; i < pixelData.size();) {
		pixels.push_back(Pixel(pixelData[i + 2], pixelData[i + 1], pixelData[i]));
		i += 3;
	}
	if (flagInverted) uninvertRows();
}

void Bitmap::padRows() {
	if (flagPadded) return;
	uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
	uint rowCount = 0;
	vector<uchar> paddedPixelData;
	for (uint i = 0; i <= imageHeight * (imageWidth * 3); i++) {
		if (i > 0 && i % (imageWidth * 3) == 0) {
			for (uint j = 0; j < padAmount; j++) {
				paddedPixelData.push_back(0x00);
			}
			rowCount++;
		}
		if (i < imageHeight * (imageWidth * 3)) paddedPixelData.push_back(pixelData[i]);
	}
	pixelData = paddedPixelData;
	flagPadded = true;
}

void Bitmap::unpadRows() {
	if (!flagPadded) return;
	uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
	vector<uchar> unpaddedPixelData;
	uint rowCount = 1;
	for (uint i = 0; i <= (imageHeight * ((imageWidth * 3) + padAmount)); i++) {
		if (padAmount > 0 && i > 0 && i % ((((imageWidth * 3) + padAmount) * rowCount) - padAmount) == 0) {
			i += padAmount;
			rowCount++;
		}
		if(i < imageHeight * ((imageWidth * 3) + padAmount)) unpaddedPixelData.push_back(pixelData[i]);
	}
	pixelData = unpaddedPixelData;
	flagPadded = false;
}

void Bitmap::invertRows() {
	if (flagInverted) return;
	vector<Pixel> tempPixelVector;
	for (int i = ((imageHeight - 1) * imageWidth); i > -1; i -= imageWidth) {
		for (uint j = 0; j < imageWidth; ++j) {
			tempPixelVector.push_back(pixels[i + j]);
		}
	}
	pixels = tempPixelVector;
	flagInverted = true;
}

void Bitmap::uninvertRows() {
	if (!flagInverted) return;
	vector<Pixel> tempPixelVector;
	for (int i = ((imageHeight - 1) * imageWidth); i > -1; i -= imageWidth) {
		for (uint j = 0; j < imageWidth; ++j) {
			tempPixelVector.push_back(pixels[i + j]);
		}
	}
	pixels = tempPixelVector;
	flagInverted = false;
}

ushort Bitmap::toLittleEndian(ushort in) {
	ushort out = 0;
	uchar b1, b2;
	b1 = (in << 8) >> 8;
	b2 = in >> 8;
	out |= b1;
	out <<= 8;
	out |= b2;
	return out;
}

ushort Bitmap::toBigEndian(ushort in) {
	ushort out = 0;
	uchar b1, b2;
	b1 = (in << 8) >> 8;
	b2 = in >> 8;
	out |= b1;
	out <<= 8;
	out |= b2;
	return out;
}

uint Bitmap::toLittleEndian(uint in) {
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

uint Bitmap::toBigEndian(uint in) {
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

Bitmap::Pixel::Pixel() {
	R = 0x00;
	B = 0x00;
	G = 0x00;
}

Bitmap::Pixel::Pixel(uchar R, uchar G, uchar B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

string Bitmap::getFilename() {
	return filename;
}

uint Bitmap::getFileSize() {
	return fileLength;
}

void Bitmap::fillColor(Bitmap::Pixel pixel) {
	if (pixels.size() > 0) {
		for (uint i = 0; i < pixels.size(); i++) {
			pixels[i] = pixel;
		}
	}
	else {
		for (uint i = 0; i < imageHeight * imageWidth; i++) {
			pixels.push_back(pixel);
		}
	}
}

void Bitmap::fillColor(uchar R, uchar G, uchar B) {
	fillColor(Pixel(R, G, B));
}

void Bitmap::operator= (const Bitmap& rhs) {
	this->imageWidth = rhs.imageWidth;
	this->imageHeight = rhs.imageHeight;
	this->xResolution = rhs.xResolution;
	this->yResolution = rhs.yResolution;
	this->pixels.clear();
	for (uint i = 0; i < rhs.pixels.size(); i++) {
		this->pixels.push_back(rhs.pixels[i]);
	}
	this->pixelData.clear();
	for (uint i = 0; i < rhs.pixelData.size(); i++) {
		this->pixelData.push_back(rhs.pixelData[i]);
	}
	this->flagInverted = rhs.flagInverted;
	this->flagPadded = rhs.flagPadded;
	this->flagPixelsInverted = rhs.flagPixelsInverted;
	this->filename = rhs.filename;
	this->compressionScheme = rhs.compressionScheme;
	this->imageSizeDelta = rhs.imageSizeDelta;
	this->colorTableValuesUsed = rhs.colorTableValuesUsed;
	this->colorTableValuesImportant = rhs.colorTableValuesImportant;
	this->fileLength = rhs.fileLength;
	this->pixelDataOffset = rhs.pixelDataOffset;
	this->headerLength = rhs.headerLength;
	this->imageInfoHeaderLength = rhs.imageInfoHeaderLength;
}
/*
bool Bitmap::operator== (const Bitmap& rhs) {
	return
		this->imageWidth == rhs.imageWidth &&
		this->imageHeight == rhs.imageHeight &&
		this->xResolution == rhs.xResolution &&
		this->yResolution == rhs.yResolution &&
		this->pixels == rhs.pixels &&
		this->pixelData == rhs.pixelData &&
		this->flagInverted == rhs.flagInverted &&
		this->flagPadded == rhs.flagPadded &&
		this->flagPixelsInverted == rhs.flagPixelsInverted &&
		this->filename == rhs.filename &&
		this->compressionScheme == rhs.compressionScheme &&
		this->imageSizeDelta == rhs.imageSizeDelta &&
		this->colorTableValuesUsed == rhs.colorTableValuesUsed &&
		this->colorTableValuesImportant == rhs.colorTableValuesImportant &&
		this->fileLength == rhs.fileLength &&
		this->pixelDataOffset == rhs.pixelDataOffset &&
		this->headerLength == rhs.headerLength &&
		this->imageInfoHeaderLength == rhs.imageInfoHeaderLength;
}

bool Bitmap::operator!= (const Bitmap& rhs) {
	return !(*this == rhs);
}

void Bitmap::Pixel::operator= (const Bitmap::Pixel& rhs) {
	this->R = rhs.R;
	this->B = rhs.B;
	this->G = rhs.G;
}

bool Bitmap::Pixel::operator== (const Bitmap::Pixel& rhs) {
	return this->R == rhs.R && this->G == rhs.G && this->B == rhs.B;
}

bool Bitmap::Pixel::operator!= (const Bitmap::Pixel& rhs) {
	return !(*this == rhs);
}
*/