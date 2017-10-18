#include "Bitmap_IO.h"

using namespace std;
namespace bmp {
	//copy constructor
	Bitmap::Bitmap(const Bitmap& other) {
		*this = other;
	}

	//default constructor
	Bitmap::Bitmap(const char* filename, uint width, uint height, uint xRes, uint yRes, vector<Pixel> pixels, vector<uchar> pixelData, bool flagInverted, bool flagPadded, bool flagPixelsInverted, uint compressionScheme, uint imageSizeDelta, uint colorTableValuesUsed, uint colorTableValuesImportant) {
		//make sure that the bitmap's size is greater than 0 on both axes
		assert(width > 0 && height > 0);
		//set fields to their relevant data
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
		//calculate header length (EXPECT 14)
		headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
		//calculate image info header length (EXPECT 40)
		imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(this->compressionScheme) + sizeof(this->imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(this->colorTableValuesImportant) + sizeof(this->colorTableValuesUsed);
		//calculate pixel data offset (EXPECT 54)
		pixelDataOffset = headerLength + imageInfoHeaderLength;
	}

	//pull all data from all fields and output a formatted bitmap data string
	char* Bitmap::toString(Bitmap& bitmap) {
		//populate the pixel data array
		bitmap.fillPixelData();
		//pad rows as necessary
		bitmap.padRows();
		//recalculate image info header length
		bitmap.imageInfoHeaderLength = sizeof(imageInfoHeaderLength) + sizeof(imageWidth) + sizeof(imageHeight) + sizeof(PLANE_COUNT) + sizeof(COLOR_DEPTH) + sizeof(compressionScheme) + sizeof(imageSizeDelta) + sizeof(xResolution) + sizeof(yResolution) + sizeof(colorTableValuesUsed) + sizeof(colorTableValuesImportant);
		//recalculate header length
		bitmap.headerLength = sizeof(BITMAP_SIGNATURE) + sizeof(fileLength) + sizeof(RESERVED_BYTES) + sizeof(pixelDataOffset);
		//recalculate pixel data offset
		bitmap.pixelDataOffset = bitmap.imageInfoHeaderLength + bitmap.headerLength;
		//calculate file size
		bitmap.fileLength = bitmap.headerLength + bitmap.imageInfoHeaderLength + bitmap.pixelData.size();
		//empty string to write to
		char* dataToWrite = new char[bitmap.fileLength];
		//string position holder
		uint cursor = 0;

		//all following loops (except last one) have some form of
		//dataToWrite[cursor] = (<data> << (8 * i)) >> ((sizeof(<data>) - 1) * 8)
		//this does the following:
		//i = 0:
		//AABBCCDD -> AABBCCDD -> 000000AA
		//dataToWrite[cursor] = AA
		//i = 1:
		//AABBCCDD -> BBCCDD00 -> 000000BB
		//dataToWrite[cursor + 1] = BB
		//i = 2:
		//AABBCCDD -> CCDD0000 -> 000000CC
		//dataToWrite[cursor + 2] = CC
		//i = 3:
		//AABBCCDD -> DD000000 -> 000000DD
		//dataToWrite[cursor + 3] = DD
		//above example is for INT. SHORT uses 4 bytes as opposed to 8

		//write 'B' and 'M' to string (bitmap signature), and advance the cursor
		for (uint i = 0; i < sizeof(bitmap.BITMAP_SIGNATURE); i++) {
			dataToWrite[cursor] = (bitmap.BITMAP_SIGNATURE << (8 * i)) >> ((sizeof(bitmap.BITMAP_SIGNATURE) - 1) * 8);
			cursor++;
		}
		//rearrange file length to little endian (was big endian) and write to string and advance cursor
		uint fileLengthLE = bitmap.changeEndianness(bitmap.fileLength);
		for (uint i = 0; i < sizeof(fileLengthLE); i++) {
			dataToWrite[cursor] = (fileLengthLE << (8 * i)) >> ((sizeof(bitmap.fileLength) - 1) * 8);
			cursor++;
		}
		//write reserved bytes to string and advance cursor
		for (uint i = 0; i < sizeof(bitmap.RESERVED_BYTES); i++) {
			dataToWrite[cursor] = (bitmap.RESERVED_BYTES << (8 * i)) >> ((sizeof(bitmap.RESERVED_BYTES) - 1) * 8);
			cursor++;
		}
		//convert pixel data offset to little endian (was big endian), write to string, and advance cursor
		uint pixelDataOffsetLE = bitmap.changeEndianness(bitmap.pixelDataOffset);
		for (uint i = 0; i < sizeof(pixelDataOffsetLE); i++) {
			dataToWrite[cursor] = (pixelDataOffsetLE << (8 * i)) >> ((sizeof(pixelDataOffsetLE) - 1) * 8);
			cursor++;
		}
		//convert image info header length to little endian (was big endian), write to string, and advance cursor
		uint imageInfoHeaderLengthLE = bitmap.changeEndianness(bitmap.imageInfoHeaderLength);
		for (uint i = 0; i < sizeof(imageInfoHeaderLengthLE); i++) {
			dataToWrite[cursor] = (imageInfoHeaderLengthLE << (8 * i)) >> ((sizeof(imageInfoHeaderLengthLE) - 1) * 8);
			cursor++;
		}
		//convert image width to little endian (was big endian), write to string, and advance cursor
		uint imageWidthLE = bitmap.changeEndianness(bitmap.imageWidth);
		for (uint i = 0; i < sizeof(imageWidthLE); i++) {
			dataToWrite[cursor] = (imageWidthLE << (8 * i)) >> ((sizeof(imageWidthLE) - 1) * 8);
			cursor++;
		}
		//convert image height to little endian (was big endian), write to string, and advance cursor
		uint imageHeightLE = bitmap.changeEndianness(bitmap.imageHeight);
		for (uint i = 0; i < sizeof(imageHeightLE); i++) {
			dataToWrite[cursor] = (imageHeightLE << (8 * i)) >> ((sizeof(imageHeightLE) - 1) * 8);
			cursor++;
		}
		//convert plane count to little endian (was big endian), write to string, and advance cursor
		ushort planeCountLE = bitmap.changeEndianness(bitmap.PLANE_COUNT);
		for (uint i = 0; i < sizeof(planeCountLE); i++) {
			dataToWrite[cursor] = (planeCountLE << (8 * i)) >> ((sizeof(planeCountLE) - 1) * 8);
			cursor++;
		}
		//convert color bit depth to little endian (was big endian), write to string, and advance cursor
		ushort colorDepthLE = bitmap.changeEndianness(bitmap.COLOR_DEPTH);
		for (uint i = 0; i < sizeof(colorDepthLE); i++) {
			dataToWrite[cursor] = (colorDepthLE << (8 * i)) >> ((sizeof(colorDepthLE) - 1) * 8);
			cursor++;
		}
		//write compression scheme to string and advance cursor
		for (uint i = 0; i < sizeof(bitmap.compressionScheme); i++) {
			dataToWrite[cursor] = (bitmap.compressionScheme << (8 * i)) >> ((sizeof(bitmap.compressionScheme) - 1) * 8);
			cursor++;
		}
		//write image size delta to string and advance cursor
		for (uint i = 0; i < sizeof(bitmap.imageSizeDelta); i++) {
			dataToWrite[cursor] = (bitmap.imageSizeDelta << (8 * i)) >> ((sizeof(bitmap.imageSizeDelta) - 1) * 8);
			cursor++;
		}
		//convert x resolution to little endian (was big endian), write to string, and advance cursor
		uint xResolutionLE = bitmap.changeEndianness(bitmap.xResolution);
		for (uint i = 0; i < sizeof(xResolutionLE); i++) {
			dataToWrite[cursor] = (xResolutionLE << (8 * i)) >> ((sizeof(xResolutionLE) - 1) * 8);
			cursor++;
		}
		//convert y resolution to little endian (was big endian), write to string, and advance cursor
		uint yResolutionLE = bitmap.changeEndianness(bitmap.yResolution);
		for (uint i = 0; i < sizeof(yResolutionLE); i++) {
			dataToWrite[cursor] = (yResolutionLE << (8 * i)) >> ((sizeof(yResolutionLE) - 1) * 8);
			cursor++;
		}
		//write the number of color table values used to string and advance cursor
		for (uint i = 0; i < sizeof(bitmap.colorTableValuesUsed); i++) {
			dataToWrite[cursor] = (bitmap.colorTableValuesUsed << (8 * i)) >> ((sizeof(bitmap.colorTableValuesUsed) - 1) * 8);
			cursor++;
		}
		//write the number of color table values important to string and advance cursor
		for (uint i = 0; i < sizeof(bitmap.colorTableValuesImportant); i++) {
			dataToWrite[cursor] = (bitmap.colorTableValuesImportant << (8 * i)) >> ((sizeof(bitmap.colorTableValuesImportant) - 1) * 8);
			cursor++;
		}
		//write all data in pixel data array to string (pixels and padding)
		for (uint i = 0; i < bitmap.pixelData.size(); i++) {
			dataToWrite[cursor] = bitmap.pixelData[i];
			cursor++;
		}
		//cursor should be at end of file
		assert(cursor == bitmap.fileLength);
		//return the bitmap data string
		return dataToWrite;
	}

	//read in a bitmap object from a bitmap data string
	void Bitmap::fromString(Bitmap& bitmap, char* bitmapData) {
		//set string position cursor to 0
		uint cursor = 0;
		//grab the first two bytes (bitmap signature)
		ushort bmpsig = bitmap.getShortFromStream(cursor, bitmapData);
		//make sure file is signed as bitmap
		assert(bmpsig == bitmap.BITMAP_SIGNATURE);
		//advance cursor
		cursor += sizeof(bmpsig);
		//grab next four bytes (file size) and convert to big endian (was little endian)
		bitmap.fileLength = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.fileLength);
		//grab next four bytes (reserved bytes)
		uint reserve = bitmap.getIntFromStream(cursor, bitmapData);
		//make sure they are correct
		assert(reserve == bitmap.RESERVED_BYTES);
		//advance cursor
		cursor += sizeof(reserve);
		//grab next four bytes (pixel data offset) and convert to big endian (was little endian)
		bitmap.pixelDataOffset = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.pixelDataOffset);
		//grab next four bytes (info header length) and convert to big endian (was little endian)
		bitmap.imageInfoHeaderLength = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.imageInfoHeaderLength);
		//grab next four bytes (width) and convert to big endian (was little endian)
		bitmap.imageWidth = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//make sure width > 0
		assert(bitmap.imageWidth > 0U);
		//advance cursor
		cursor += sizeof(bitmap.imageWidth);
		//grab next four bytes (height) and convert to big endian (was little endian)
		bitmap.imageHeight = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//make sure height > 0
		assert(bitmap.imageHeight > 0U);
		//advance cursor
		cursor += sizeof(bitmap.imageHeight);
		//grab next two bytes (plane count) and convert to big endian (was little endian)
		ushort planes = bitmap.changeEndianness(bitmap.getShortFromStream(cursor, bitmapData));
		//make sure plane count is correct
		assert(planes == bitmap.PLANE_COUNT);
		//advance cursor
		cursor += sizeof(planes);
		//grab next two bytes (color bit depth) and convert to big endian (was little endian)
		ushort colorbits = bitmap.changeEndianness(bitmap.getShortFromStream(cursor, bitmapData));
		//make sure color bit depth is correct
		assert(colorbits == bitmap.COLOR_DEPTH);
		//advance cursor
		cursor += sizeof(colorbits);
		//grab next four bytes (compression scheme) and convert to big endian (was little endian)
		bitmap.compressionScheme = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.compressionScheme);
		//grab next four bytes (image size delta) and convert to big endian (was little endian)
		bitmap.imageSizeDelta = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.imageSizeDelta);
		//grab next four bytes (x resolution) and convert to big endian (was little endian)
		bitmap.xResolution = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.xResolution);
		//grab next four bytes (y resolution) and convert to big endian (was little endian)
		bitmap.yResolution = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.yResolution);
		//grab next four bytes (number of color table values used) and convert to big endian (was little endian)
		bitmap.colorTableValuesUsed = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.colorTableValuesUsed);
		//grab next four bytes (number of color table values important) and convert to big endian (was little endian)
		bitmap.colorTableValuesImportant = bitmap.changeEndianness(bitmap.getIntFromStream(cursor, bitmapData));
		//advance cursor
		cursor += sizeof(bitmap.colorTableValuesImportant);
		//make sure cursor is at the end of all headers and is at beginning of pixel data
		assert(cursor == bitmap.pixelDataOffset);
		//clear the pixel data array if it is not empty
		if (bitmap.pixelData.size() > 0) bitmap.pixelData.clear();
		//grab each byte of pixel data one by one and put it in the pixel data array, and advance cursor
		for (; cursor < bitmap.fileLength; cursor++) {
			bitmap.pixelData.push_back(bitmapData[cursor]);
		}
		//make sure cursor is at end of file
		assert(cursor == bitmap.fileLength);
		//data was grabbed from a file, so it is padded. set flag to true
		bitmap.flagPadded = true;
		//data was grabbed from a file, so it is inverted. set flag to true
		bitmap.flagInverted = true;
		//unpad pixel data
		bitmap.unpadRows();
		//fill pixel array
		bitmap.fillPixel();
	}

	//grab two bytes from a string and interpret them as a short
	ushort Bitmap::getShortFromStream(uint start, char* stream) {
		//grab the first character
		ushort out = stream[start];
		//move the bytes up (00FF -> FF00)
		out <<= 8;
		//grab the next character
		out |= stream[start + 1];
		//return the short
		return out;
	}

	//grab four bytes from a string and interpret them as an integer
	uint Bitmap::getIntFromStream(uint start, char* stream) {
		//grab first byte
		uint out = stream[start];
		//move up (000000FF -> 0000FF00)
		out <<= 8;
		//grab next byte
		out |= stream[start + 1];
		//move up (0000FFEE -> 00FFEE00)
		out <<= 8;
		//grab next byte
		out |= stream[start + 2];
		//move up (00FFEEDD -> FFEEDD00)
		out <<= 8;
		//grab last byte
		out |= stream[start + 3];
		//return the result
		return out;
	}

	//fill pixel data array
	void Bitmap::fillPixelData() {
		//invert the rows if necessary
		if (!flagInverted) invertRows();
		//check to see if pixel data is already populated, if the pixels are in RGB order, and it isn't padded
		if (pixelData.size() > 0 && !flagPixelsInverted && !flagPadded) {
			//if pixels is not empty, clear pixel data to make sure they match
			if (pixels.size() > 0) {
				pixelData.clear();
			}
			else {
				//change pixels from RGB to BGR
				for (uint i = 0; i < pixelData.size(); ++i) {
					uchar temp = pixelData[i + (3 * i)];
					pixelData[i + (3 * i)] = pixelData[i + 2 + (3 * i)];
					pixelData[i + 2 + (3 * i)] = temp;
				}
				flagPixelsInverted = true;
				//end early
				return;
			}
		}
		//populate pixel data in BGR order
		for (uint i = 0; i < pixels.size(); ++i) {
			pixelData.push_back(pixels[i].B);
			pixelData.push_back(pixels[i].G);
			pixelData.push_back(pixels[i].R);
		}
		flagPixelsInverted = true;
	}

	//fill pixel array
	void Bitmap::fillPixel() {
		//clear pixels to make sure it will be correct
		//TODO: add safeties to make sure data isn't deleted forever
		if (pixels.size() > 0) pixels.clear();
		//populate pixel array with data from pixel data
		for (uint i = 0; i < pixelData.size();) {
			//i + 2 = R, i + 1 = G, i = B
			pixels.push_back(Pixel(pixelData[i + 2], pixelData[i + 1], pixelData[i]));
			//advance counter
			i += 3;
		}
		//uninvert data rows for ease of reading
		if (flagInverted) uninvertRows();
	}

	//add extra bytes to the end of each row
	void Bitmap::padRows() {
		//make sure this is necessary
		if (flagPadded) return;
		//calculate the pad amount
		//will be 0, 1, 2, or 3, depending on how wide the image is
		uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
		//temporary array for storing padded data
		vector<uchar> paddedPixelData;
		//loop from start of array until 1 past end (for adding padding)
		for (uint i = 0; i <= imageHeight * (imageWidth * 3); i++) {
			//check if at end of a row (but not at zero)
			if (i > 0 && i % (imageWidth * 3) == 0) {
				//add pad to end of row
				for (uint j = 0; j < padAmount; j++) {
					//pad can be literally anything 0x00-0xFF: using 0x00 here
					paddedPixelData.push_back(0x00);
				}
			}
			//if within image, add pixel data
			if (i < imageHeight * (imageWidth * 3)) paddedPixelData.push_back(pixelData[i]);
		}
		//set pixel data to be padded
		pixelData = paddedPixelData;
		//change flag to true
		flagPadded = true;
	}

	//remove extra bytes from the end of each row
	void Bitmap::unpadRows() {
		//make sure this is necessary
		if (!flagPadded) return;
		//calculate pad amount
		//will be 0, 1, 2, or 3 depending on image width
		uint padAmount = (imageWidth * 3) % 4 == 0 ? 0 : 4 - ((imageWidth * 3) % 4);
		//temporary storage for unpadded data
		vector<uchar> unpaddedPixelData;
		//row counter
		//set to 1 initially (there will always be at least one row....)
		uint rowCount = 1;
		//loop through pixel data and go one past end (for funsies)
		for (uint i = 0; i <= (imageHeight * ((imageWidth * 3) + padAmount)); i++) {
			//check to see if position is at the beginning of a pad section
			//example:
			//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
			//B G R B G R B G R P P  P  B  G  R  B  G  R  B  G  R  P  P  P  B  G  R  B  G  R  B  G  R  P  P  P (length = 36)
			//image width = 3, pad amount = 3
			//first time: row count = 1
			//((((3 * 3) + 3) * 1) - 3) = (((9 + 3) * 1) - 3) = 12 - 3 = 9. if i == 9, we're in a pad
			//second time: row count = 2
			//((((3 * 3) + 3) * 2) - 3) = (((9 + 3) * 2) - 3) = 24 - 3 = 21. if i == 21, we're in a pad
			//third (and last) time: row count = 3
			//((((3 * 3) + 3) * 3) - 3) = (((9 + 3) * 3) - 3) = 36 - 3 = 33. if i = 33, we're in a pad
			if (padAmount > 0 && i > 0 && i % ((((imageWidth * 3) + padAmount) * rowCount) - padAmount) == 0) {
				//skip over pad
				i += padAmount;
				//move on to next row
				rowCount++;
			}
			//if still in image, populate temporary array
			if (i < imageHeight * ((imageWidth * 3) + padAmount)) unpaddedPixelData.push_back(pixelData[i]);
		}
		//set pixel data array to unpadded temporary array
		pixelData = unpaddedPixelData;
		//data is not padded anymore. set flag to false
		flagPadded = false;
	}

	//invert rows
	void Bitmap::invertRows() {
		//make sure this is necessary
		if (flagInverted) return;
		//ensure there is something to invert and that it is of the correct size
		if (pixels.size() != (imageHeight * imageWidth)) fillPixel();
		//temporary storage for inverted data
		vector<Pixel> tempPixelVector;
		//loop through each row starting at the bottom
		for (int i = ((imageHeight - 1) * imageWidth); i > -1; i -= imageWidth) {
			//loop through the row
			for (uint j = 0; j < imageWidth; ++j) {
				tempPixelVector.push_back(pixels[i + j]);
			}
		}
		//set pixels to temporary inverted storage
		pixels = tempPixelVector;
		//data is inverted. set flag to true
		flagInverted = true;
	}

	//uninvert rows
	//this method is virtually identical to invertRows, except for the flag checking and setting
	void Bitmap::uninvertRows() {
		//make sure this is necessary
		if (!flagInverted) return;
		//temporary rectified pixel storage
		vector<Pixel> tempPixelVector;
		//loop through each row, stating at the bottom
		for (int i = ((imageHeight - 1) * imageWidth); i > -1; i -= imageWidth) {
			//loop through the row
			for (uint j = 0; j < imageWidth; ++j) {
				tempPixelVector.push_back(pixels[i + j]);
			}
		}
		//set pixels to temporary rectified storage
		pixels = tempPixelVector;
		//data is uninverted. set flag to false
		flagInverted = false;
	}

	//flip flop endianness (ushort)
	ushort Bitmap::changeEndianness(ushort in) {
		//blank unsigned short for outputting
		ushort out = 0;
		//bytes
		uchar b1, b2;
		//grab LSB (1122 -> 2200 -> 0022)
		b1 = (in << 8) >> 8;
		//grab MSB (1122 -> 0011)
		b2 = in >> 8;
		//put LSB in out (0000 -> 0022)
		out |= b1;
		//move up (0022 -> 2200)
		out <<= 8;
		//put MSP in out (2200 -> 2211) [yay]
		out |= b2;
		//return result
		return out;
	}

	//flip flop endinness (uint)
	uint Bitmap::changeEndianness(uint in) {
		//blank unsigned int
		uint out = 0;
		//bytes
		uchar b1, b2, b3, b4;
		//grab LSB (11223344 -> 44000000 -> 00000044)
		b1 = (in << 24) >> 24;
		//grab next most significant byte (11223344 -> 33440000 -> 00000033)
		b2 = (in << 16) >> 24;
		//grab next most significant byte (11223344 -> 22334400 -> 00000022)
		b3 = (in << 8) >> 24;
		//grab most significant byte (11223344 -> 00000011)
		b4 = in >> 24;
		//put LSB in out (00000000 -> 00000044)
		out |= b1;
		//move up (00000044 -> 00004400)
		out <<= 8;
		//put next byte in out (00004400 -> 00004433)
		out |= b2;
		//move up (00004433 -> 00443300)
		out <<= 8;
		//put next byte in out (00443300 -> 00443322)
		out |= b3;
		//move up (00443322 -> 44332200)
		out <<= 8;
		//put MSB in out (44332200 -> 44332211) [yay]
		out |= b4;
		//return result
		return out;
	}

	//default constructor
	Bitmap::Pixel::Pixel() {
		//set all color values to 0 (black)
		R = 0x00;
		B = 0x00;
		G = 0x00;
	}

	//data heavy constructor
	Bitmap::Pixel::Pixel(uchar R, uchar G, uchar B) {
		//set colors to inputs
		this->R = R;
		this->G = G;
		this->B = B;
	}

	//get specified bitmap object's filename
	string Bitmap::getFilename(Bitmap& bitmap) {
		return bitmap.filename;
	}

	//set specified bitmap object's filename to be name
	void Bitmap::setFilename(Bitmap& bitmap, const char* name) {
		bitmap.filename = name;
	}

	//get specified bitmap object's filesize
	uint Bitmap::getFileSize(Bitmap& bitmap) {
		return bitmap.fileLength;
	}

	//get specified bitmap object's width
	uint Bitmap::getWidth(Bitmap& bitmap) {
		return bitmap.imageWidth;
	}

	//get specified bitmap object's height
	uint Bitmap::getHeight(Bitmap& bitmap) {
		return bitmap.imageHeight;
	}

	//fill specified bitmap's pixels with specified pixel
	void Bitmap::fillColor(Bitmap& bitmap, Bitmap::Pixel pixel) {
		//pixels is not empty; assume correct size
		if (bitmap.pixels.size() > 0) {
			//push the target pixel into the array
			for (uint i = 0; i < bitmap.pixels.size(); i++) {
				bitmap.pixels[i] = pixel;
			}
		}
		//pixels is empty
		else {
			//add target pixel (height * width) times
			for (uint i = 0; i < bitmap.imageHeight * bitmap.imageWidth; i++) {
				bitmap.pixels.push_back(pixel);
			}
		}
	}

	//fill specified bitmap's pixels with specified color values
	void Bitmap::fillColor(Bitmap& bitmap, uchar R, uchar G, uchar B) {
		//call other fillColor method
		bitmap.fillColor(bitmap, Pixel(R, G, B));
	}

	//deep assignment operator
	void Bitmap::operator= (const Bitmap& rhs) {
		//set EVERYTHING to be equal
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
		//not entirely necessary to set filename....
		//this->filename = rhs.filename;
		this->compressionScheme = rhs.compressionScheme;
		this->imageSizeDelta = rhs.imageSizeDelta;
		this->colorTableValuesUsed = rhs.colorTableValuesUsed;
		this->colorTableValuesImportant = rhs.colorTableValuesImportant;
		this->fileLength = rhs.fileLength;
		this->pixelDataOffset = rhs.pixelDataOffset;
		this->headerLength = rhs.headerLength;
		this->imageInfoHeaderLength = rhs.imageInfoHeaderLength;
	}

	//get target bitmap's pixel array
	vector<Bitmap::Pixel> Bitmap::getPixels(Bitmap& bitmap) {
		return bitmap.pixels;
	}

	//set target bitmap's pixel array to something else
	void Bitmap::setPixels(Bitmap& bitmap, vector<Pixel> other) {
		//ensure same size.... doesn't have to be this way tho
		//assert(bitmap.pixels.size() == other.size());
		///*
		//current pixel array size
		uint currSize = bitmap.pixels.size();
		//target pixel array size
		uint targetSize = other.size();
		//set one to be the other
		bitmap.pixels = other;
		//underfill
		if (currSize > targetSize) {
			//until at original size, push black pixels
			for (uint i = 0; i < currSize - targetSize; i++) {
				bitmap.pixels.push_back(Pixel(0x00, 0x00, 0x00));
			}
		}
		//overfill
		if (currSize < targetSize) {
			//until at original size, delete pixels
			for (uint i = 0; i < targetSize - currSize; i++) {
				bitmap.pixels.pop_back();
			}
		}
		//*/
	}

	//set target bitmap's pixel data array to something else
	//exactly the same as setPixels, except different arrays are used
	void Bitmap::setPixelData(Bitmap& bitmap, vector<uchar> other) {
		//make sure the sizes are equal....doesn't have to be done this way....
		//assert(bitmap.pixelData.size() == other.size());
		///*
		//swap data
		bitmap.pixelData = other;
		//current size of pixel data array
		uint currSize = bitmap.pixelData.size();
		//target size of pixel data array
		uint targetSize = other.size();
		//underfill
		if (currSize > other.size()) {
			//until at correct size, push black data
			for (uint i = 0; i < currSize - targetSize; i++) {
				bitmap.pixelData.push_back(0x00);
			}
		}
		//overfill
		if (currSize < other.size()) {
			//until at correct size, delete data
			for (uint i = 0; i < targetSize - currSize; i++) {
				bitmap.pixelData.pop_back();
			}
		}
		//*/
	}

	//get target bitmap's padded flag
	bool Bitmap::getFlagPadded(Bitmap& bitmap) {
		return bitmap.flagPadded;
	}

	//get target bitmap's pixel data padded
	vector<uchar> Bitmap::getPaddedPixelData(Bitmap& bitmap) {
		//see if we need to pad the data
		if (bitmap.flagPadded) return bitmap.pixelData;
		else {
			bitmap.padRows();
			return bitmap.pixelData;
		}
	}

	//get target bitmap's pixel data unpadded
	vector<uchar> Bitmap::getUnpaddedPixelData(Bitmap& bitmap) {
		//check if we need to unpad the data
		if (!bitmap.flagPadded) return bitmap.pixelData;
		else {
			bitmap.unpadRows();
			return bitmap.pixelData;
		}
	}

	//--------------------END OF BITMAP CLASS--------------------//

	//read bitmap object from file
	Bitmap BitmapReader::read(Bitmap& bitmap) {
		//file input stream
		ifstream fin;
		//open file based on filename (FOR READING)
		fin.open(Bitmap::getFilename(bitmap));
		//check if it failed
		if (fin.fail()) {
			//output a failure message
			cerr << "FAILED TO OPEN IMAGE FOR READING" << endl;
			//return empty bitmap using default values
			return Bitmap();
		}
		//temporary character
		char temp;
		//size of file
		int streamSize = 0;
		//loop until end of file, incrementing filesize
		while (!fin.eof()) {
			temp = fin.get();
			streamSize++;
		}
		//decrement file size (eof is one past actual end of file)
		streamSize--;
		//string of file data
		char* fileData = new char[streamSize];
		//exit the file (reset the stream)
		fin.close();
		//reopen the file (if it didn't fail before, it shouldn't now....)
		fin.open(Bitmap::getFilename(bitmap));
		//read (streamSize) characters into the data string
		fin.read(fileData, streamSize);
		//generate bitmap object
		Bitmap::fromString(bitmap, fileData);
		//exit file
		fin.close();
		//return created object for good measure
		return bitmap;
	}

	//--------------------END OF BITMAPREADER CLASS--------------------//

	//write bitmap object to file
	void BitmapWriter::write(Bitmap& bitmap) {
		//open binary file of name (filename) (FOR WRITING)
		ofstream fout(Bitmap::getFilename(bitmap), ios::binary);
		//check if it actually opened
		if (fout.fail()) {
			//log error message
			cerr << "FAILED TO OPEN IMAGE FOR WRITING" << endl;
			//end function here
			return;
		}
		//write data of length (filesize) to file
		char* bitmapDataString = Bitmap::toString(bitmap);
		fout.write(bitmapDataString, Bitmap::getFileSize(bitmap));
		//exit file
		fout.close();
	}
	
	//utility for testing
	//fill bitmap with color
	void BitmapWriter::fill(Bitmap& bitmap, Bitmap::Pixel pixel) {
		Bitmap::fillColor(bitmap, pixel);
	}

	//utility for testing
	//fill bitmap with color
	void BitmapWriter::fill(Bitmap& bitmap, uchar R, uchar G, uchar B) {
		Bitmap::fillColor(bitmap, R, G, B);
	}
}