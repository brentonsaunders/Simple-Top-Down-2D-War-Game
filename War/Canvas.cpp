#include <Windows.h>
#include <vector>
#include "Canvas.h"
#include "Vector2.h"

using namespace std;

Canvas::Canvas(HWND hwnd, int width, int height)
	: Bitmap(width, height) 
{
	this->hwnd = hwnd;

	hdc = GetDC(hwnd);

	hdcBackBuffer = CreateCompatibleDC(hdc);
	hbmBackBuffer = getHbitmap();

	SelectObject(hdcBackBuffer, hbmBackBuffer);

	strokeColor = RGB(0, 0, 0);
	fillColor = RGB(255, 255, 255);
	strokeWidth = 1;
}

Canvas::~Canvas() {
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteDC(hdcBackBuffer);
	DeleteObject(hbmBackBuffer);
	ReleaseDC(hwnd, hdc);
}

void Canvas::erase() {
	beginPaint();

	RECT rect = { 0, 0, width, height };

	FillRect(hdcBackBuffer, &rect, hBrush);

	endPaint();
}

void Canvas::fillRect(int x, int y, int width, int height) {
	beginPaint();

	RECT rect = { x, y, x + width, y + height };

	FillRect(hdcBackBuffer, &rect, hBrush);

	endPaint();
}

void Canvas::rect(int x, int y, int width, int height) {
	beginPaint();

	vector<Vector2> points;

	points.push_back(Vector2(x, y));
	points.push_back(Vector2(x + width, y));
	points.push_back(Vector2(x + width, y + height));
	points.push_back(Vector2(x, y + height));

	points = matrix.apply(points);

	POINT* pts = new POINT[4];

	for (int i = 0; i < 4; ++i) {
		pts[i].x = (int)points[i].x;
		pts[i].y = (int)points[i].y;
	}

	Polygon(hdcBackBuffer, pts, 4);

	delete [] pts;

	endPaint();
}

void Canvas::ellipse(int x, int y, int width, int height) {
	beginPaint();

	Ellipse(hdcBackBuffer, x, y, x + width, y + height);

	endPaint();
}

void Canvas::line(int startX, int startY, int endX, int endY) {
	beginPaint();

	MoveToEx(hdcBackBuffer, startX, startY, NULL);

	LineTo(hdcBackBuffer, endX, endY);

	endPaint();
}

void Canvas::drawBitmap(Bitmap*bitmap, int dstX, int dstY, int dstWidth, int dstHeight,
	int srcX, int srcY, int srcWidth, int srcHeight) {
	if (matrix == Matrix3::IDENTITY) {
		HDC hdcMem = CreateCompatibleDC(NULL);

		SelectObject(hdcMem, bitmap->getHbitmap());

		StretchBlt(hdcBackBuffer, dstX, dstY, dstWidth, dstHeight, hdcMem, srcX, srcY,
			srcWidth, srcHeight, SRCCOPY);

		DeleteDC(hdcMem);

		return;
	}


	Rect rect(dstX, dstY, dstX + dstWidth, dstY + dstHeight);

	rect = getBoundingRectAfterTransform(rect);

	int actualWidth = bitmap->getWidth();
	int actualHeight = bitmap->getHeight();

	double xScale = (double)dstWidth / (double)srcWidth;
	double yScale = (double)dstHeight / (double)srcHeight;

	for (int y = rect.top; y < rect.bottom; ++y) {
		for (int x = rect.left; x < rect.right; ++x) {
			if (x < 0 || y < 0 || x >= width || y >= height) {
				continue;
			}

			Vector2 source(x, y);

			source = matrix.inverse().apply(source);

			int sx = (int)((source.x - dstX) / xScale);
			int sy = (int)((source.y - dstY) / yScale);

			sx += srcX;
			sy += srcY;

			if (sx < 0 || sy < 0 || sx >= actualWidth || sy >= actualHeight ||
				sx >= srcX + srcWidth || sy >= srcY + srcHeight || sx < srcX || sy < srcY) {
				continue;
			}

			COLORREF color = bitmap->getPixel(sx, sy);

			if (bitmap->isTransparent() && color == bitmap->getTransparentColor()) {
				continue;
			}

			setPixel(x, y, color);
		}
	}
}

void Canvas::drawBitmap(Bitmap* bitmap, int x, int y) {
	int width = bitmap->getWidth();
	int height = bitmap->getHeight();

	drawBitmap(bitmap, x, y, width, height, 0, 0, width, height);
}

void Canvas::drawBitmap(Bitmap* bitmap, int x, int y, int width, int height) {
	drawBitmap(bitmap, x, y, width, height, 0, 0, width, height);
}

void Canvas::draw() {
	BitBlt(hdc, 0, 0, width, height, hdcBackBuffer, 0, 0, SRCCOPY);
}

void Canvas::save() {
	Paint paint;

	paint.fillColor = fillColor;
	paint.strokeColor = strokeColor;
	paint.strokeWidth = strokeWidth;
	paint.matrix = matrix;

	saved.push(paint);
}

void Canvas::restore() {
	if (saved.empty()) {
		return;
	}

	Paint paint = saved.top();

	saved.pop();

	fillColor = paint.fillColor;
	strokeColor = paint.strokeColor;
	strokeWidth = paint.strokeWidth;
	matrix = paint.matrix;
}

void Canvas::beginPaint() {
	hPen = CreatePen(PS_SOLID, strokeWidth, strokeColor);
	hBrush = CreateSolidBrush(fillColor);
	hOldPen = (HPEN)SelectObject(hdcBackBuffer, hPen);
	hOldBrush = (HBRUSH)SelectObject(hdcBackBuffer, hBrush);
}

void Canvas::endPaint() {
	DeleteObject(hPen);
	DeleteObject(hBrush);
	SelectObject(hdcBackBuffer, hOldPen);
	SelectObject(hdcBackBuffer, hOldBrush);
}

void Canvas::rotate(double angle) {
	matrix = matrix.rotate(angle);
}

void Canvas::scale(double scale) {
	matrix = matrix.scale(scale, scale);
}

void Canvas::translate(double x, double y) {
	matrix = matrix.translate(x, y);
}

void Canvas::shear(double x, double y) {
	matrix = matrix.shear(x, y);
}

Rect Canvas::getBoundingRectAfterTransform(const Rect& rect) {
	vector<Vector2> corners;

	corners.push_back(Vector2(rect.left, rect.top));
	corners.push_back(Vector2(rect.right, rect.top));
	corners.push_back(Vector2(rect.right, rect.bottom));
	corners.push_back(Vector2(rect.left, rect.bottom));

	corners = matrix.apply(corners);

	Rect bounding(INT_MAX, INT_MAX, INT_MIN, INT_MIN);

	for (int i = 0; i < 4; ++i) {
		bounding.left = (int)min(bounding.left, corners[i].x);
		bounding.top = (int)min(bounding.top, corners[i].y);
		bounding.right = (int)max(bounding.right, corners[i].x);
		bounding.bottom = (int)max(bounding.bottom, corners[i].y);
	}

	return bounding;
}
