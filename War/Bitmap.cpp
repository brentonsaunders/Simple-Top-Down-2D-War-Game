#include "Bitmap.h"

Bitmap::Bitmap(int width, int height) {
	this->width = width;
	this->height = height;

	BITMAPINFO bmi;

	ZeroMemory(&bmi, sizeof(BITMAP));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(NULL);

	hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&lpBits, NULL,
		0);

	ReleaseDC(NULL, hdc);

	transparent = false;
	transparentColor = 0;
}

Bitmap::~Bitmap() {
	DeleteObject(hBitmap);
}

Bitmap* Bitmap::fromFile(LPCWSTR file, bool transparent) {
	HBITMAP hbmSrc = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);

	if (!hbmSrc) {
		throw BitmapNotFoundException();
	}

	BITMAP bm;

	GetObject(hbmSrc, sizeof(BITMAP), &bm);

	Bitmap* bitmap = new Bitmap(bm.bmWidth, bm.bmHeight);

	HDC hdcMem = CreateCompatibleDC(NULL);
	HDC hdcMem2 = CreateCompatibleDC(NULL);

	SelectObject(hdcMem, hbmSrc);
	SelectObject(hdcMem2, bitmap->getHbitmap());

	if (transparent) {
		bitmap->transparent = true;
		bitmap->transparentColor = GetPixel(hdcMem, 0, 0);
	}

	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	DeleteObject(hbmSrc);
	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);

	return bitmap;
}

HBITMAP Bitmap::getHbitmap() {
	return hBitmap;
}

int Bitmap::getWidth() {
	return width;
}

int Bitmap::getHeight() {
	return height;
}

COLORREF Bitmap::getPixel(int x, int y) {
	int offset = 4 * width * y + 4 * x;

	BYTE r = lpBits[offset + 2];
	BYTE g = lpBits[offset + 1];
	BYTE b = lpBits[offset];

	return RGB(r, g, b);
}

void Bitmap::setPixel(int x, int y, COLORREF color) {
	int offset = 4 * width * y + 4 * x;

	BYTE r = GetRValue(color);
	BYTE g = GetGValue(color);
	BYTE b = GetBValue(color);

	lpBits[offset] = b;
	lpBits[offset + 1] = g;
	lpBits[offset + 2] = r;
}

bool Bitmap::isTransparent() {
	return transparent;
}

COLORREF Bitmap::getTransparentColor() {
	return transparentColor;
}
