#include <Windows.h>
#include <iostream>
#include "ObstacleMap.h"

using namespace std;

ObstacleMap::ObstacleMap(int width, int height)
	: terrainMap(width, height), obstacleMap(width, height) {
	seedWater();

	for (int i = 0; i < 5; ++i) {
		spread(Obstacle::WATER);
	}

	seedTrees();

	for (int i = 0; i < 5; ++i) {
		spread(Obstacle::TREES);
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Obstacle::Type type = obstacleMap.get(x, y);

			if (type != Obstacle::TREES && type != Obstacle::WATER) {
				int value = terrainMap.get(x, y);

				switch (value) {
				case 0:
					type = Obstacle::GROUND0;
					break;
				case 1:
					type = Obstacle::GROUND1;
					break;
				case 2:
					type = Obstacle::GROUND2;
					break;
				case 3:
					type = Obstacle::GROUND3;
					break;
				case 4:
					type = Obstacle::GROUND4;
					break;
				}

				obstacleMap.set(x, y, type);
			}
		}
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

Obstacle::Type ObstacleMap::get(int x, int y) const {
	return obstacleMap.get(x, y);
}

void ObstacleMap::draw(Canvas* canvas, GameAssets *assets) {
	canvas->save();

	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Obstacle::Type type = obstacleMap.get(x, y);

			if (type == Obstacle::WATER) {
				canvas->fillColor = canvas->strokeColor = RGB(0, 162, 232);

				canvas->fillRect(
					20 * x,
					20 * y,
					20,
					20
				);
			}
			else if(type == Obstacle::TREES) {
				canvas->drawBitmap(assets->tree, 20 * x, 20 * y);
			}
			else if (type == Obstacle::TRENCH) {
				canvas->drawBitmap(assets->hedgehog, 20 * x, 20 * x);
			}
			else if (type == Obstacle::HEDGEHOG) {
				canvas->drawBitmap(assets->hedgehog, 20 * x, 20 * x);
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
			obstacleMap.set(x, y, Obstacle::WATER);

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

		if (terrainMap.get(x, y) == 0 && obstacleMap.countWithinRadius(x, y, 5, Obstacle::WATER) == 0) {
			obstacleMap.set(x, y, Obstacle::TREES);

			++i;
		}
	}
}

void ObstacleMap::spread(Obstacle::Type type) {
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

			if (type == Obstacle::TREES &&
				obstacleMap.countWithinRadius(x, y, 5, Obstacle::WATER) > 0) {
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
