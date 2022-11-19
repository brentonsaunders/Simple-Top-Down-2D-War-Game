#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Math.h"

template<class T>
class TileMap {
public:
	TileMap(int width, int height) {
		this->width = width;
		this->height = height;

		for (int y = 0; y < height; ++y) {
			std::vector<T> row;

			for (int x = 0; x < width; ++x) {
				row.push_back(T());
			}

			map.push_back(row);
		}
	}

	~TileMap() {}

	int getWidth() const {
		return width;
	}

	int getHeight() const {
		return height;
	}

	void set(int x, int y, T value) {
		map[y][x] = value;
	}

	T get(int x, int y) const {
		return map[y][x];
	}

	// Returns the number of times the given value is found within a given radius of x, y
	int countWithinRadius(int x, int y, int radius, T value) {
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

	std::string toString() const {
		std::stringstream ss;

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (x > 0) {
					ss << ",";
				}

				ss << map[y][x];
			}

			ss << std::endl;
		}

		return ss.str();
	}


private:
	std::vector<std::vector<T>> map;
	int width, height;
};

