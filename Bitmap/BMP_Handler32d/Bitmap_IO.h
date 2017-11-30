#pragma once

#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include <iostream>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

namespace bmp {
	class Bitmap {
	public:
		struct Pixel {
			Pixel();
			Pixel(uchar, uchar, uchar);
			uchar R;
			uchar G;
			uchar B;
		};
		//constructor with defaults used for all except width and height, which must be specified
		//default filename = temp.bmp
		//default width = 1
		//default height = 1
		//default xResolution = 0 (machine default)
		//default yResolution = 0 (machine default)
		//default pixel list = empty
		//default pixel data list = empty
		//default flag inverted = false
		//default flag padded = false
		//default flag pixels inverted = false (used if pixel data is not empty and pixels are RGB and not BGR)
		//default compression scheme = 0 (no compression)
		//default image size delta = 0 (no change)
		//default color table values used = 0 (no values)
		//default color table values important = o (none)
		Bitmap(const char* filename = "temp.bmp", uint width = 1, uint height = 1,
			uint xRes = 0, uint yRes = 0, std::vector<Pixel> pixels = std::vector<Pixel>(0),
			std::vector<uchar> pixelData = std::vector<uchar>(0), bool flagInverted = false,
			bool flagPadded = false, bool flagPixelsInverted = false, uint compressionScheme = 0,
			uint imageSizeDelta = 0, uint colorTableValuesUsed = 0, uint colorTableValuesImportant = 0);
		//equals operator for deep assignment
		void operator= (const Bitmap&);
		//outputs bitmap data as a properly formatted bitmap string
		static char* toString(Bitmap&);
		//creates a bitmap object from a properly formatted bitmap string
		static void fromString(Bitmap&, char*);
		//gets filename
		static std::string getFilename(Bitmap&);
		//sets filename
		static void setFilename(Bitmap&, const char*);
		//gets filesize
		static uint getFileSize(Bitmap&);
		//gets height
		static uint getHeight(Bitmap&);
		//gets width
		static uint getWidth(Bitmap&);
		//fills image with specified pixel
		static void fillColor(Bitmap&, Pixel);
		//fills image with specified colors
		static void fillColor(Bitmap&, uchar, uchar, uchar);
		//gets the list of pixel objects
		static std::vector<Pixel> getPixels(Bitmap&);
		//sets the list of pixel objects
		static void setPixels(Bitmap&, std::vector<Pixel>);
		//sets pixel data list
		static void setPixelData(Bitmap&, std::vector<uchar>);
		//graps the padded flag
		static bool getFlagPadded(Bitmap&);
		//grabs the pixel data as a padded list
		static std::vector<uchar> getPaddedPixelData(Bitmap&);
		//grabs the pixel data as an unpadded list
		static std::vector<uchar> getUnpaddedPixelData(Bitmap&);
	private:
		//remove padding from the end of each row
		void unpadRows();
		//add padding to the end of each row
		void padRows();
		//reorient rows so that they are in actual image format
		void uninvertRows();
		//reorient rows so that they are in saved file format
		void invertRows();
		//populate the pixel data list
		void fillPixelData();
		//populate the pixel list
		void fillPixel();
		//flip flop endianness (ushort)
		ushort changeEndianness(ushort);
		//flip flop endianness (uint)
		uint changeEndianness(uint);
		//grab a short from a byte array
		ushort getShortFromStream(uint, char*);
		//grab an int from a byte array
		uint getIntFromStream(uint, char*);
		//constant values: bitmap signature = 'BM'
		const ushort BITMAP_SIGNATURE = (ushort)0x424D;
		//constant values: bitmap reserved bytes = 0
		const uint RESERVED_BYTES = (uint)0x00000000;
		//constant values: plane count = 1
		const ushort PLANE_COUNT = (ushort)0x0001;
		//constant values: color bit depth = 24
		const ushort COLOR_DEPTH = (ushort)0x0018;
		//fields: length of file
		uint fileLength;
		//fields: offset value for pixel data
		uint pixelDataOffset;
		//fields: length of image info header
		uint imageInfoHeaderLength;
		//fields: width of image
		uint imageWidth;
		//fields: height of image
		uint imageHeight;
		//fields: compression scheme to use
		uint compressionScheme;
		//fields: change in image size to expect
		uint imageSizeDelta;
		//fields: pixels per meter in x direction (l/r)
		uint xResolution;
		//fields: pixels per meter in y direction (u/d)
		uint yResolution;
		//fields: color table values used
		uint colorTableValuesUsed;
		//fields: color table values important
		uint colorTableValuesImportant;
		//fields: pixel data list ('R', 'G', 'B', ... or 'B', 'G', 'R', ...)
		std::vector<uchar> pixelData;
		//fields: pixel list. is either in inverted row order or not. use flagInverted for info
		std::vector<Pixel> pixels;
		//fields: name of file
		const char* filename;
		//fields: length of bitmap declaration header (expect to be 14)
		uint headerLength;
		//fields: inversion flag
		//true = rows are in format for writing to file
		//false = rows are in format for reading by human
		bool flagInverted;
		//fields: pad flag
		//true = B G R B G R B G R P P P etc.
		//false = B G R B G R B G R etc.
		bool flagPadded;
		//fields: reversed pixels flag
		//true = 'B', 'G', 'R'
		//false = 'R', 'G', 'B'
		bool flagPixelsInverted;
	};

	class BitmapWriter {
	public:
		//write specified bitmap to file
		static void write(Bitmap&);
		//fill bitmap with spcified pixel
		static void fill(Bitmap&, Bitmap::Pixel);
		//fill bitmap with specified color
		static void fill(Bitmap&, uchar, uchar, uchar);
	};

	class BitmapReader {
	public:
		//read bitmap from specified file
		static Bitmap read(Bitmap&);
	};
}