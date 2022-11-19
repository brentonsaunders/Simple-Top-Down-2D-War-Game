#include <Windows.h>
#include "Obstacle.h"

Obstacle::Obstacle(Type type, int x, int y) {
	this->type = type;
	this->x = x;
	this->y = y;

	if (type == TRENCH) {
		timeLeft = 30000;
	} else if(type == HEDGEHOG) {
		timeLeft = 30000;
	}
}

Obstacle::~Obstacle() {

}

void Obstacle::update(DWORD time) {
	timeLeft -= time;
}

bool Obstacle::isAlive() {
	return timeLeft > 0;
}

int Obstacle::getX() const { return x; }

int Obstacle::getY() const { return y;  }
