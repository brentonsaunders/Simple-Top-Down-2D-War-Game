#include <Windows.h>
#include <iostream>
#include "ObstacleMap.h"

using namespace std;

ObstacleMap::ObstacleMap(int width, int height)
	: TerrainMap(width, height), map(width, height) {
	seedWater();

	for (int i = 0; i < 5; ++i) {
		spread(1);
	}

	seedTrees();

	for (int i = 0; i < 5; ++i) {
		spread(2);
	}
}

ObstacleMap::~ObstacleMap() {

}


ObstacleMap::Obstacle ObstacleMap::getObstacle(int x, int y) const {
	int value = map.get(x, y);

	if (value == 1) {
		return WATER;
	}
	else if (value == 2) {
		return TREES;
	}

	value = get(x, y);

	switch (value) {
	case 1:
		return GROUND1;
	case 2:
		return GROUND2;
	case 3:
		return GROUND3;
	case 4:
		return GROUND4;
	case 5:
		return GROUND5;
	}

	return GROUND0;
}

void ObstacleMap::draw(Canvas* canvas, GameAssets *assets) {
	canvas->save();

	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int value = map.get(x, y);

			if (value == 1) {
				canvas->fillColor = canvas->strokeColor = RGB(0, 162, 232);

				canvas->fillRect(
					20 * x,
					20 * y,
					20,
					20
				);
			}
			else if(value == 2) {
				canvas->drawBitmap(assets->tree, 20 * x, 20 * y);
			}
			else {
				TerrainMap::draw(canvas, x, y);
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
			map.set(x, y, 1);

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

		if (get(x, y) == 0 && countWithinRadius(x, y, 5, 1) == 0) {
			map.set(x, y, 2);

			++i;
		}
	}
}

void ObstacleMap::spread(int spreadValue) {
	int width = getWidth();
	int height = getHeight();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int neighbors = 0;
			int nonzeroNeighbors = 0;
			int thisValue = map.get(x, y);
			int elevationMapValue = get(x, y);

			if (elevationMapValue != 0) {
				continue;
			}

			if (spreadValue == 2 && countWithinRadius(x, y, 5, 1) > 0) {
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

					int value = map.get(xx, yy);

					if (value == spreadValue) {
						++ nonzeroNeighbors;
					}
				}
			}

			int rand = random.nextInt() % neighbors;

			if (rand < nonzeroNeighbors) {
				map.set(x, y, spreadValue);
			}
		}
	}
}
