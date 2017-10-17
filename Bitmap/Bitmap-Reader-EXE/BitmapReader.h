#pragma once

#include <Bitmap.h>
#include <fstream>
#include <iostream>

class BitmapReader {
public:
	BitmapReader(Bitmap);
	void read();
private:
	Bitmap bitmap;
};