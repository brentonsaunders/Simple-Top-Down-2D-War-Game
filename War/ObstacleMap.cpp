#include <Windows.h>
#include <iostream>
#include "ObstacleMap.h"

using namespace std;

ObstacleMap::ObstacleMap(int width, int height)
	: terrainMap(width, height), obstacleMap(width, height) {
	seedWater();

	for (int i = 0; i < 5; ++i) {
		spread(WATER);
	}

	seedTrees();

	for (int i = 0; i < 5; ++i) {
		spread(TREES);
	}
}

ObstacleMap::~ObstacleMap() {

}

int ObstacleMap::getWidth() const {
	return obstacleMap.getWidth();
}

int ObstacleMap::getHeight() const {
	return obstacleMap.getHeight();
}

ObstacleMap::Type ObstacleMap::get(int x, int y) const {
	Type type = obstacleMap.get(x, y);

	if (type != NONE) {
		return type;
	}

	int value = terrainMap.get(x, y);

	switch (value) {
	case 0:
		return GROUND0;
	case 1:
		return GROUND1;
	case 2:
		return GROUND2;
	case 3:
		return GROUND3;
	case 4:
		return GROUND4;
	}

	return NONE;
}

bool ObstacleMap::inBounds(int x, int y) const {
	return x >= 0 && y >= 0 && x < getWidth() && y < getHeight();
}

bool ObstacleMap::addObstacle(Type type, int x, int y) {
	if (obstacleMap.get(x, y) != NONE) {
		return false;
	}

	Obstacle obstacle;

	obstacle.x = x;
	obstacle.y = y;
	obstacle.timeLeft = 30000;

	obstacles.push_back(obstacle);

	obstacleMap.set(x, y, type);

	return true;
}

void ObstacleMap::update(DWORD time) {
	vector<Obstacle>::iterator it = obstacles.begin();

	while (it != obstacles.end()) {
		if (it->timeLeft <= 0) {
			obstacleMap.set(it->x, it->y, NONE);

			it = obstacles.erase(it);
		}
		else {
			it->timeLeft -= time;

			++it;
		}
	}
}

void ObstacleMap::draw(Canvas* canvas, GameAssets *assets) {
	canvas->save();

	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Type type = obstacleMap.get(x, y);

			if (type == WATER) {
				canvas->fillColor = canvas->strokeColor = RGB(0, 162, 232);

				canvas->fillRect(
					20 * x,
					20 * y,
					20,
					20
				);
			}
			else if(type == TREES) {
				canvas->drawBitmap(assets->tree, 20 * x, 20 * y);
			}
			else if (type == TRENCH) {
				canvas->drawBitmap(assets->hedgehog, 20 * x, 20 * y);
			}
			else if (type == HEDGEHOG) {
				canvas->drawBitmap(assets->hedgehog, 20 * x, 20 * y);
			}
			else {
				terrainMap.draw(canvas, x, y);
			}
		}
	}

	canvas->restore();
}

void ObstacleMap::seedWater() {
	int width = getWidth();
	int height = getHeight();
	int area = width * height;
	int i = 0;

	while(i < 10) {
		int x = random.nextInt() % width;
		int y = random.nextInt() % height;

		int value = get(x, y);

		if (get(x, y) == 0) {
			obstacleMap.set(x, y, WATER);

			++i;
		}
	}
}

void ObstacleMap::seedTrees() {
	int width = getWidth();
	int height = getHeight();
	int area = width * height;
	int i = 0;

	while (i < 10) {
		int x = random.nextInt() % width;
		int y = random.nextInt() % height;

		int value = get(x, y);

		if (terrainMap.get(x, y) == 0 && obstacleMap.countWithinRadius(x, y, 5, WATER) == 0) {
			obstacleMap.set(x, y, TREES);

			++i;
		}
	}
}

void ObstacleMap::spread(Type type) {
	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int neighbors = 0;
			int nonzeroNeighbors = 0;
			int thisValue = obstacleMap.get(x, y);
			int terrainMapValue = terrainMap.get(x, y);

			if (terrainMapValue != 0) {
				continue;
			}

			if (type == TREES &&
				obstacleMap.countWithinRadius(x, y, 5, WATER) > 0) {
				continue;
			}

			for (int yy = y - 1; yy <= y + 1; ++yy) {
				for (int xx = x - 1; xx <= x + 1; ++xx) {
					if (xx == x && yy == y) {
						continue;
					}

					if (xx < 0 || yy < 0 || xx >= width || yy >= height) {
						continue;
					}

					++neighbors;

					int value = obstacleMap.get(xx, yy);

					if (value == type) {
						++ nonzeroNeighbors;
					}
				}
			}

			int rand = random.nextInt() % neighbors;

			if (rand < nonzeroNeighbors) {
				obstacleMap.set(x, y, type);
			}
		}
	}
}
