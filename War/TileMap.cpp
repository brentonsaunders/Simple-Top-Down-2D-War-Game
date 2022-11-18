#include <Windows.h>
#include <iostream>
#include <sstream>
#include "TileMap.h"
#include "Math.h"

using namespace std;

TileMap::TileMap(int width, int height) {
	this->width = width;
	this->height = height;

	for (int y = 0; y < height; ++y) {
		vector<int> row;

		for (int x = 0; x < width; ++x) {
			row.push_back(0);
		}

		map.push_back(row);
	}
}

TileMap::~TileMap() {

}

int TileMap::getWidth() const {
	return width;
}

int TileMap::getHeight() const {
	return height;
}

void TileMap::set(int x, int y, int value) {
	map[y][x] = value;
}

int TileMap::get(int x, int y) const {
	return map[y][x];
}

// Returns the number of times the given value is found within a given radius of x, y
int TileMap::countWithinRadius(int x, int y, int radius, int value) {
	int left = x - radius;
	int top = y - radius;
	int right = x + radius;
	int bottom = y + radius;
	int count = 0;

	int points = 0;

	for (int yy = top; yy < bottom; ++yy) {
		for (int xx = left; xx < right; ++xx) {
			if (yy < 0 || xx < 0 || yy >= height || xx >= width) {
				continue;
			}

			++points;

			if (Math::euclidean(x, y, xx, yy) > radius) {
				continue;
			}

			if (map[yy][xx] == value) {
				++count;
			}
		}
	}

	return count;
}

string TileMap::toString() const {
	stringstream ss;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (x > 0) {
				ss << ",";
			}

			ss << map[y][x];
		}

		ss << endl;
	}

	return ss.str();
}
