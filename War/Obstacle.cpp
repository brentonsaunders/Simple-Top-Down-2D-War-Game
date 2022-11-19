#include <Windows.h>
#include "Obstacle.h"

Obstacle::Obstacle(Type type, Vector2 pos) {
	this->type = type;
	this->pos = Vector2(
		(int)(pos.x / 20.0) * 20 + 10,
		(int)(pos.y / 20.0) * 20 + 10
	);

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

void Obstacle::draw(Canvas* canvas, GameAssets* assets) {
	canvas->save();

	canvas->translate(pos.x, pos.y);

	if (type == TRENCH) {
		canvas->drawBitmap(assets->hedgehog, -10, -10);
	} else if (type == HEDGEHOG) {
		canvas->drawBitmap(assets->hedgehog, -11, -11);
	}

	canvas->restore();
}

bool Obstacle::isAlive() {
	return timeLeft > 0;
}

Vector2 Obstacle::getPos() const {
	return pos;
}