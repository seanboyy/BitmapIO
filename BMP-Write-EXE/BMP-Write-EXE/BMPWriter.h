#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

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
	//empty constructor (probably won't be used...(making it anyway!!!!))
	BitmapWriter();
	//constructor for height and width, using standard resolution
	BitmapWriter(uint, uint, std::string);
	//constructor for height, width, and x resolution, mirroring for y
	BitmapWriter(uint, uint, uint, std::string);
	//constructor for height, width, and x and y resolutions
	BitmapWriter(uint, uint, uint, uint, std::string);
	//constructor for height, width, x and y resolutions, and pixel data
	BitmapWriter(uint, uint, uint, uint, std::vector<Pixel>, std::string);
	//constructor for height, width, x and y resolutions, and pixel data as char list
	BitmapWriter(uint, uint, uint, uint, std::vector<uchar>, std::string);
	//destructor
	~BitmapWriter();
	//fill whole image with specified pixel color
	void fillOneColor(Pixel);
	//fill whole image with specified RGB channel values
	void fillOneColor(uchar, uchar, uchar);
	//create a bitmap file
	void write();
private:
	//add extra bytes to the end of a row
	//for padding out to 4 divisible row length
	void padRows();
	//convert the pixel vector into a char list
	void fillPixelData();
	//convert big endian short to little endian short
	ushort toLittleEndian(ushort);
	//convert big endian int to little endian int
	uint toLittleEndian(uint);
	//flip image by row
	void invertRows();
	//length of bitmap file (whole thing)
	uint fileLength;
	//offset for start of pixel data
	uint pixelDataOffset;
	//size of second header
	uint imageInfoHeaderLength;
	//width of image
	uint imageWidth;
	//height of image
	uint imageHeight;
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
	//list of pixel data in LE format
	std::vector<uchar> pixelData;
	//vector of pixel structs
	std::vector<Pixel> pixels;
	//length of pixel data
	uint pixelDataLength;
	//length of file header
	uint headerLength;
	//name of image file
	std::string filename;
	//"BM" used for denoting binary file type
	const ushort BITMAP_SIGNATURE = (ushort)0x424D;
	//4 reserved bytes
	const uint RESERVED_BYTES = (uint)0x00000000;
	//plane count bytes
	const ushort PLANE_COUNT = (ushort)0x0001;
	//color complexity
	const ushort COLOR_DEPTH = (ushort)0x0018;
};