#pragma once
#pragma comment(lib, "Bitmap.lib")

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <Bitmap.h>

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

class BitmapWriter {
public:
	BitmapWriter(Bitmap);
	void write();
	void fill(Bitmap::Pixel);
	void fill(uchar, uchar, uchar);
private:
	Bitmap bitmap;
};