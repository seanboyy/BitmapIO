#include "Bitmap_IO.h"
#include "BMP_Handler.h"

using namespace std;

int main(int argc, char** argv) {
	system("pause");
	int width = 200, height = 200;
	//Bitmap bitmap = Bitmap("PaintTest.bmp");
	//Bitmap bitmap2 = Bitmap("PaintResult.bmp");
	uchar* bitmapData = BMP_Handler::loadBMP("PaintTest.bmp", width, height);
	BMP_Handler::saveBMP("PaintResult.bmp", bitmapData, width, height);
	system("pause");
	return 0;
}