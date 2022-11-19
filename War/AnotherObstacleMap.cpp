#include <Windows.h>
#include "AnotherObstacleMap.h"

AnotherObstacleMap::AnotherObstacleMap(int width, int height)
	: map(width, height) {
}

AnotherObstacleMap::~AnotherObstacleMap() {

}

int AnotherObstacleMap::getWidth() const {
	return map.getWidth();
}

int AnotherObstacleMap::getHeight() const {
	return map.getHeight();
}
