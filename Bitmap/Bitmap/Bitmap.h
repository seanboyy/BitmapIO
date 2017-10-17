#pragma once

#include <vector>
#include <cassert>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

class Bitmap {
public:
	struct Pixel {
		Pixel();
		Pixel(uchar, uchar, uchar);
		//void operator= (const Pixel&);
		//bool operator== (const Pixel&);
		//bool operator!= (const Pixel&);
		uchar R;
		uchar G;
		uchar B;
	};
	Bitmap(const Bitmap&);
	//constructor with defaults used for all except width and height, which must be specified
	Bitmap(const char* filename = "temp.bmp", uint width = 1, uint height = 1, uint xRes = 0, uint yRes = 0, std::vector<Pixel> pixels = std::vector<Pixel>(0), std::vector<uchar> pixelData = std::vector<uchar>(0), bool flagInverted = false, bool flagPadded = false, bool flagPixelsInverted = false, uint compressionScheme = 0, uint imageSizeDelta = 0, uint colorTableValuesUsed = 0, uint colorTableValuesImportant = 0);
	char* toString();
	void fromString(char*);
	std::string getFilename();
	uint getFileSize();
	void fillColor(Pixel);
	void fillColor(uchar, uchar, uchar);
	void operator= (const Bitmap&);
	//bool operator== (const Bitmap&);
	//bool operator!= (const Bitmap&);
private:
	void padRows();
	void unpadRows();
	void uninvertRows();
	void invertRows();
	void fillPixelData();
	void fillPixel();
	ushort toLittleEndian(ushort);
	ushort toBigEndian(ushort);
	uint toLittleEndian(uint);
	uint toBigEndian(uint);
	ushort getShortFromStream(uint, char*);
	uint getIntFromStream(uint, char*);
	const ushort BITMAP_SIGNATURE = (ushort)0x424D;
	const uint RESERVED_BYTES = (uint)0x00000000;
	const ushort PLANE_COUNT = (ushort)0x0001;
	const ushort COLOR_DEPTH = (ushort)0x0018;
	//fields
	uint fileLength;
	uint pixelDataOffset;
	uint imageInfoHeaderLength;
	uint imageWidth;
	uint imageHeight;
	uint compressionScheme;
	uint imageSizeDelta;
	uint xResolution;
	uint yResolution;
	uint colorTableValuesUsed;
	uint colorTableValuesImportant;
	std::vector<uchar> pixelData;
	std::vector<Pixel> pixels;
	const char* filename;
	uint headerLength;
	bool flagInverted;
	bool flagPadded;
	bool flagPixelsInverted;
};