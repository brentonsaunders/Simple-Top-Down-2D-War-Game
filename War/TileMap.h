#pragma once

#include <vector>
#include <string>

class TileMap {
public:
	TileMap(int, int);
	~TileMap();
	int getWidth() const;
	int getHeight() const;
	void set(int, int, int);
	int get(int, int) const;
	int countWithinRadius(int, int, int, int);
	std::string toString() const;

private:
	std::vector<std::vector<int>> map;
	int width, height;
};
