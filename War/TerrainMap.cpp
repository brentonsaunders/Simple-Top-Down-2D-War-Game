#include <Windows.h>
#include "TerrainMap.h"

using namespace std;

double lerp(double, double, double);
COLORREF lerpColors(COLORREF, COLORREF, double);

TerrainMap::TerrainMap(int width, int height)
	: TileMap(width, height) {
	int area = width * height;

	for (int i = 0; i < 10; ++i) {
		int x = random.nextInt() % width;
		int y = random.nextInt() % height;

		set(x, y, 5);
	}

	for (int i = 0; i < 5; ++i) {
		smooth();
	}
}

TerrainMap::~TerrainMap() {

}

void TerrainMap::draw(Canvas* canvas, int x, int y) {
	COLORREF maxColor = RGB(181, 230, 29);
	COLORREF minColor = RGB(86, 110, 14);
	int value = get(x, y);
	double a = value / 5.0;
	COLORREF color = lerpColors(minColor, maxColor, a);

	canvas->fillColor = canvas->strokeColor = color;

	canvas->fillRect(
		20 * x,
		20 * y,
		20,
		20
	);
}

void TerrainMap::draw(Canvas* canvas) {
	canvas->save();

	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			draw(canvas, x, y);
		}
	}

	canvas->restore();
}

void TerrainMap::smooth() {
	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int neighborsGreaterThan = 0;
			int neighbors = 0;
			int thisValue = get(x, y);

			for (int yy = y - 1; yy <= y + 1; ++yy) {
				for (int xx = x - 1; xx <= x + 1; ++xx) {
					if (xx == x && yy == y) {
						continue;
					}

					if (xx < 0 || yy < 0 || xx >= width || yy >= height) {
						continue;
					}

					++neighbors;

					int value = get(xx, yy);

					if (value > thisValue) {
						++neighborsGreaterThan;
					}
				}
			}

			int rand = random.nextInt() % neighbors;

			if (rand < neighborsGreaterThan) {
				set(x, y, thisValue + 1);
			}
		}
	}
}

double lerp(double v0, double v1, double t) {
	return (1 - t) * v0 + t * v1;
}

COLORREF lerpColors(COLORREF color0, COLORREF color1, double t) {
	return RGB(
		(BYTE)lerp(GetRValue(color0), GetRValue(color1), t),
		(BYTE)lerp(GetGValue(color0), GetGValue(color1), t),
		(BYTE)lerp(GetBValue(color0), GetBValue(color1), t)
	);
}