#pragma once

#include <stack>
#include "Bitmap.h"
#include "Matrix3.h"
#include "Rect.h"

class Canvas : public Bitmap {
public:
	COLORREF fillColor;
	COLORREF strokeColor;
	int strokeWidth;

	Canvas(HWND, int, int);
	~Canvas();
	void erase();
	void fillRect(int, int, int, int);
	void rect(int, int, int, int);
	void ellipse(int, int, int, int);
	void line(int, int, int, int);
	void drawBitmap(Bitmap*, int, int);
	void drawBitmap(Bitmap*, int, int, int, int);
	void drawBitmap(Bitmap*, int, int, int, int, int, int, int, int);
	void draw();
	void save();
	void restore();
	void rotate(double);
	void scale(double);
	void translate(double, double);
	void shear(double, double);

private:
	struct Paint {
		COLORREF fillColor;
		COLORREF strokeColor;
		int strokeWidth;
		Matrix3 matrix;
	};

	Matrix3 matrix;

	HWND hwnd;
	HDC hdc;
	HDC hdcBackBuffer;
	HBITMAP hbmBackBuffer;
	HBRUSH hBrush, hOldBrush;
	HPEN hPen, hOldPen;
	std::stack<Paint> saved;

	void beginPaint();
	void endPaint();
	Rect getBoundingRectAfterTransform(const Rect&);
};