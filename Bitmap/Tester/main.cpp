#include "Bitmap_IO.h"
#include "BMP_Handler.h"

using namespace std;
using namespace bmp;

int main(int argc, char** argv) {
	system("pause");
	int width = 0;
	int height = 0;
	uchar* bitmapData = BMP_Handler::loadBMP("PaintTest.bmp", width, height);
	BMP_Handler::saveBMP("PaintResult.bmp", bitmapData, width, height);
	system("pause");
	return 0;
}