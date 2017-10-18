#include "Bitmap_IO.h"

using namespace std;

Bitmap::Bitmap(const Bitmap& other) {
	*this = other;
}

Bitmap::Bitmap(const char* filename, uint width, uint height, uint xRes, uint yRes, vector<Pixel> pixels, vector<uchar> pixelData, bool flagInverted, bool flagPadded, bool flagPixelsInverted, uint compressionScheme, uint imageSizeDelta, uint colorTableValuesUsed, uint colorTableValuesImportant) {
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

char* Bitmap::toString(Bitmap& bitmap) {
	bitmap.padRows();
	bitmap.imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(colorTableValuesUsed) + sizeof(colorTableValuesImportant);
	bitmap.headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
	bitmap.pixelDataOffset = bitmap.imageInfoHeaderLength + bitmap.headerLength;
	bitmap.fileLength = bitmap.headerLength + bitmap.imageInfoHeaderLength + bitmap.pixelData.size();
	char* dataToWrite = new char[bitmap.fileLength];
	uint cursor = 0;
	for (uint i = 0; i < sizeof(bitmap.BITMAP_SIGNATURE); i++) {
		dataToWrite[cursor] = (bitmap.BITMAP_SIGNATURE << (8 * i)) >> ((sizeof(bitmap.BITMAP_SIGNATURE) - 1) * 8);
		cursor++;
	}
	uint fileLengthLE = bitmap.toLittleEndian(bitmap.fileLength);
	for (uint i = 0; i < sizeof(fileLengthLE); i++) {
		dataToWrite[cursor] = (fileLengthLE << (8 * i)) >> ((sizeof(bitmap.fileLength) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < sizeof(bitmap.RESERVED_BYTES); i++) {
		dataToWrite[cursor] = (bitmap.RESERVED_BYTES << (8 * i)) >> ((sizeof(bitmap.RESERVED_BYTES) - 1) * 8);
		cursor++;
	}
	uint pixelDataOffsetLE = bitmap.toLittleEndian(bitmap.pixelDataOffset);
	for (uint i = 0; i < sizeof(pixelDataOffsetLE); i++) {
		dataToWrite[cursor] = (pixelDataOffsetLE << (8 * i)) >> ((sizeof(pixelDataOffsetLE) - 1) * 8);
		cursor++;
	}
	uint imageInfoHeaderLengthLE = bitmap.toLittleEndian(bitmap.imageInfoHeaderLength);
	for (uint i = 0; i < sizeof(imageInfoHeaderLengthLE); i++) {
		dataToWrite[cursor] = (imageInfoHeaderLengthLE << (8 * i)) >> ((sizeof(imageInfoHeaderLengthLE) - 1) * 8);
		cursor++;
	}
	uint imageWidthLE = bitmap.toLittleEndian(bitmap.imageWidth);
	for (uint i = 0; i < sizeof(imageWidthLE); i++) {
		dataToWrite[cursor] = (imageWidthLE << (8 * i)) >> ((sizeof(imageWidthLE) - 1) * 8);
		cursor++;
	}
	uint imageHeightLE = bitmap.toLittleEndian(bitmap.imageHeight);
	for (uint i = 0; i < sizeof(imageHeightLE); i++) {
		dataToWrite[cursor] = (imageHeightLE << (8 * i)) >> ((sizeof(imageHeightLE) - 1) * 8);
		cursor++;
	}
	ushort planeCountLE = bitmap.toLittleEndian(bitmap.PLANE_COUNT);
	for (uint i = 0; i < sizeof(planeCountLE); i++) {
		dataToWrite[cursor] = (planeCountLE << (8 * i)) >> ((sizeof(planeCountLE) - 1) * 8);
		cursor++;
	}
	ushort colorDepthLE = bitmap.toLittleEndian(bitmap.COLOR_DEPTH);
	for (uint i = 0; i < sizeof(colorDepthLE); i++) {
		dataToWrite[cursor] = (colorDepthLE << (8 * i)) >> ((sizeof(colorDepthLE) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < sizeof(bitmap.compressionScheme); i++) {
		dataToWrite[cursor] = (bitmap.compressionScheme << (8 * i)) >> ((sizeof(bitmap.compressionScheme) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < sizeof(bitmap.imageSizeDelta); i++) {
		dataToWrite[cursor] = (bitmap.imageSizeDelta << (8 * i)) >> ((sizeof(bitmap.imageSizeDelta) - 1) * 8);
		cursor++;
	}
	uint xResolutionLE = bitmap.toLittleEndian(bitmap.xResolution);
	for (uint i = 0; i < sizeof(xResolutionLE); i++) {
		dataToWrite[cursor] = (xResolutionLE << (8 * i)) >> ((sizeof(xResolutionLE) - 1) * 8);
		cursor++;
	}
	uint yResolutionLE = bitmap.toLittleEndian(bitmap.yResolution);
	for (uint i = 0; i < sizeof(yResolutionLE); i++) {
		dataToWrite[cursor] = (yResolutionLE << (8 * i)) >> ((sizeof(yResolutionLE) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < sizeof(bitmap.colorTableValuesUsed); i++) {
		dataToWrite[cursor] = (bitmap.colorTableValuesUsed << (8 * i)) >> ((sizeof(bitmap.colorTableValuesUsed) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < sizeof(bitmap.colorTableValuesImportant); i++) {
		dataToWrite[cursor] = (bitmap.colorTableValuesImportant << (8 * i)) >> ((sizeof(bitmap.colorTableValuesImportant) - 1) * 8);
		cursor++;
	}
	for (uint i = 0; i < bitmap.pixelData.size(); i++) {
		dataToWrite[cursor] = bitmap.pixelData[i];
		cursor++;
	}
	assert(cursor == bitmap.fileLength);
	return dataToWrite;
}

void Bitmap::fromString(Bitmap& bitmap, char* bitmapData) {
	uint cursor = 0;
	ushort bmpsig = bitmap.getShortFromStream(cursor, bitmapData);
	assert(bmpsig == bitmap.BITMAP_SIGNATURE);
	cursor += sizeof(bmpsig);
	bitmap.fileLength = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.fileLength);
	uint reserve = bitmap.getIntFromStream(cursor, bitmapData);
	assert(reserve == bitmap.RESERVED_BYTES);
	cursor += sizeof(reserve);
	bitmap.pixelDataOffset = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.pixelDataOffset);
	bitmap.imageInfoHeaderLength = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.imageInfoHeaderLength);
	bitmap.imageWidth = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.imageWidth);
	bitmap.imageHeight = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.imageWidth);
	ushort planes = bitmap.toBigEndian(bitmap.getShortFromStream(cursor, bitmapData));
	assert(planes == bitmap.PLANE_COUNT);
	cursor += sizeof(planes);
	ushort colorbits = bitmap.toBigEndian(bitmap.getShortFromStream(cursor, bitmapData));
	assert(colorbits == bitmap.COLOR_DEPTH);
	cursor += sizeof(colorbits);
	bitmap.compressionScheme = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.compressionScheme);
	bitmap.imageSizeDelta = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.imageSizeDelta);
	bitmap.xResolution = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.xResolution);
	bitmap.yResolution = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.yResolution);
	bitmap.colorTableValuesUsed = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.colorTableValuesUsed);
	bitmap.colorTableValuesImportant = bitmap.toBigEndian(bitmap.getIntFromStream(cursor, bitmapData));
	cursor += sizeof(bitmap.colorTableValuesImportant);
	assert(cursor == bitmap.pixelDataOffset);
	if (bitmap.pixelData.size() > 0) bitmap.pixelData.clear();
	for (; cursor < bitmap.fileLength; cursor++) {
		bitmap.pixelData.push_back(bitmapData[cursor]);
	}
	assert(cursor == bitmap.fileLength);
	bitmap.flagPadded = true;
	bitmap.flagInverted = true;
	bitmap.unpadRows();
	bitmap.fillPixel();
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
	if (pixelData.size() == 0) fillPixelData();
	vector<uchar> paddedPixelData;
	for (uint i = 0; i <= imageHeight * (imageWidth * 3); i++) {
		if (i > 0 && i % (imageWidth * 3) == 0) {
			for (uint j = 0; j < padAmount; j++) {
				paddedPixelData.push_back(0x00);
			}
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
		if (i < imageHeight * ((imageWidth * 3) + padAmount)) unpaddedPixelData.push_back(pixelData[i]);
	}
	pixelData = unpaddedPixelData;
	flagPadded = false;
}

void Bitmap::invertRows() {
	if (flagInverted) return;
	if (pixels.size() != (imageHeight * imageWidth)) fillPixel();
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

string Bitmap::getFilename(Bitmap& bitmap) {
	return bitmap.filename;
}

void Bitmap::setFilename(Bitmap& bitmap, const char* name) {
	bitmap.filename = name;
}

uint Bitmap::getFileSize(Bitmap& bitmap) {
	return bitmap.fileLength;
}

uint Bitmap::getWidth(Bitmap& bitmap) {
	return bitmap.imageWidth;
}

uint Bitmap::getHeight(Bitmap& bitmap) {
	return bitmap.imageHeight;
}

void Bitmap::fillColor(Bitmap& bitmap, Bitmap::Pixel pixel) {
	if (bitmap.pixels.size() > 0) {
		for (uint i = 0; i < bitmap.pixels.size(); i++) {
			bitmap.pixels[i] = pixel;
		}
	}
	else {
		for (uint i = 0; i < bitmap.imageHeight * bitmap.imageWidth; i++) {
			bitmap.pixels.push_back(pixel);
		}
	}
}

void Bitmap::fillColor(Bitmap& bitmap, uchar R, uchar G, uchar B) {
	bitmap.fillColor(bitmap, Pixel(R, G, B));
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

vector<Bitmap::Pixel> Bitmap::getPixels(Bitmap& bitmap) {
	return bitmap.pixels;
}

void Bitmap::setPixels(Bitmap& bitmap, vector<Pixel> other) {
	//assert(bitmap.pixels.size() == other.size());
	///*
	uint currSize = bitmap.pixels.size();
	uint targetSize = other.size();
	bitmap.pixels = other;
	if (currSize > targetSize) {
		for (uint i = 0; i < currSize - targetSize; i++) {
			bitmap.pixels.push_back(Pixel(0x00, 0x00, 0x00));
		}
	}
	if (currSize < targetSize) {
		for (uint i = 0; i < targetSize - currSize; i++) {
			bitmap.pixels.pop_back();
		}
	}
	//*/
}

void Bitmap::setPixelData(Bitmap& bitmap, vector<uchar> other) {
	//assert(bitmap.pixelData.size() == other.size());
	///*
	bitmap.pixelData = other;
	uint currSize = bitmap.pixelData.size();
	uint targetSize = other.size();
	if (currSize > other.size()) {
		for (uint i = 0; i < currSize - targetSize; i++) {
			bitmap.pixelData.push_back(0x00);
		}
	}
	if (currSize < other.size()) {
		for (uint i = 0; i < targetSize - currSize; i++) {
			bitmap.pixelData.pop_back();
		}
	}
	//*/
}

bool Bitmap::getFlagPadded(Bitmap& bitmap) {
	return bitmap.flagPadded;
}

vector<uchar> Bitmap::getPaddedPixelData(Bitmap& bitmap) {
	if (bitmap.flagPadded) return bitmap.pixelData;
	else {
		bitmap.padRows();
		return bitmap.pixelData;
	}
}

vector<uchar> Bitmap::getUnpaddedPixelData(Bitmap& bitmap) {
	if (!bitmap.flagPadded) return bitmap.pixelData;
	else {
		bitmap.unpadRows();
		return bitmap.pixelData;
	}
}

Bitmap BitmapReader::read(Bitmap& bitmap) {
	ifstream fin;
	fin.open(Bitmap::getFilename(bitmap));
	if (fin.fail()) {
		cerr << "FAILED TO OPEN IMAGE FOR READING" << endl;
		return Bitmap();
	}
	char temp;
	int streamSize = 0;
	while (!fin.eof()) {
		temp = fin.get();
		streamSize++;
	}
	streamSize--;
	char* fileData = new char[streamSize];
	fin.close();
	fin.open(Bitmap::getFilename(bitmap));
	fin.read(fileData, streamSize);
	Bitmap::fromString(bitmap, fileData);
	fin.close();
	return bitmap;
}

void BitmapWriter::write(Bitmap& bitmap) {
	ofstream fout(Bitmap::getFilename(bitmap), ios::binary);
	if (fout.fail()) {
		cerr << "FAILED TO OPEN IMAGE FOR WRITING" << endl;
		return;
	}
	char* bitmapDataString = Bitmap::toString(bitmap);
	fout.write(bitmapDataString, Bitmap::getFileSize(bitmap));
	fout.close();
}

void BitmapWriter::fill(Bitmap& bitmap, Bitmap::Pixel pixel) {
	Bitmap::fillColor(bitmap, pixel);
}

void BitmapWriter::fill(Bitmap& bitmap, uchar R, uchar G, uchar B) {
	Bitmap::fillColor(bitmap, R, G, B);
}