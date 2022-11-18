#pragma once

#include <Windows.h>

class Bitmap {
public:
	Bitmap(int, int);
	~Bitmap();
	static Bitmap* fromFile(LPCWSTR, bool transparent=false);
	HBITMAP getHbitmap();
	int getWidth();
	int getHeight();
	COLORREF getPixel(int, int);
	void setPixel(int, int, COLORREF);
	bool isTransparent();
	COLORREF getTransparentColor();

protected:
	int width, height;

private:
	HBITMAP hBitmap;
	LPBYTE lpBits;
	bool transparent;
	COLORREF transparentColor;
};

class BitmapNotFoundException {};