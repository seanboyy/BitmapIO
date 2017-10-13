#pragma once

#include <vector>
//"BM" used for denoting binary file type
#define BITMAP_SIGNATURE = (ushort)0x424D;
//4 reserved bytes
#define RESERVED_BYTES = (ushort)0x0000;
//plane count bytes
#define PLANE_COUNT = (ushort)0x0001

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

class BitmapWriter {
public:
	struct Pixel {
		Pixel();
		Pixel(uchar, uchar, uchar);
		uchar R;
		uchar G;
		uchar B;
	};
	//empty constructor (probably won't be used...)
	BitmapWriter();
	//constructor for height and width, using standard resolution
	BitmapWriter(uint, uint);
	//constructor for height, width, and x resolution, mirroring for y
	BitmapWriter(uint, uint, uint);
	//constructor for height, width, and x and y resolutions
	BitmapWriter(uint, uint, uint, uint);
	//convert big endian short to little endian short
	ushort toLittleEndian(ushort);
	//convert big endian int to little endian int
	uint toLittleEndian(uint);
	//fill whole image with specified pixel color
	std::vector<Pixel> fillOneColor(Pixel);
	//fill whole image with specified RGB channel values
	std::vector<Pixel> fillOneColor(uchar, uchar, uchar);
private:
	//add extra bytes to the end of a row
	//for padding out to 4 divisible row length
	uchar* padRow(uint);
	//convert the pixel vector into a char list
	uchar* fillPixelData();
	//length of bitmap file (whole thing)
	uint fileLength;
	//offset for start of pixel data
	uint pixelOffset;
	//size of second header
	uint imageInfoHeaderSize;
	//width of image
	uint imageWidth;
	//height of image
	uint imageHeight;
	//plane depth
	ushort planeCount;
	//color complexity
	ushort colorDepth;
	//compression scheme if applicable
	//0 for uncompressed
	//1 for RLE-8 (8-bit)
	//2 for RLE-4 (4 bit)
	//3 for Bitfields (16 and 32 bit)
	uint compressionScheme;
	//actual uncompressed image size
	uint imageSizeDelta;
	//preferred x resolution
	//usually 0
	uint xResolution;
	//preferred y resolution
	//usually 0
	uint yResolution;
	//number of colors used from the color table
	uint colorTableValuesUsed;
	//what colors to use for streamlining
	uint colorTableValuesImportant;
	//maybe i'll use it.....maybe i won't.....
	uchar* pixelData;
	//or maybe i'll use this one........
	std::vector<Pixel> pixels;
};