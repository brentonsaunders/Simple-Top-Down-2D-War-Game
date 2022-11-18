#pragma once

#include "Unit.h"
#include "Canvas.h"
#include "GameAssets.h"

class Fighter : public Unit {
public:
	Fighter(Team);
	~Fighter();
	void update(DWORD, Units*);
	void draw(Canvas*, GameAssets*);
	double getSpeed();
	double getTurnSpeed();
	int getSteeringAccurary();
	void onArrived();
	int getTotalHp() const;
	Type getType() const;
	int getRadius() const;

private:
	bool onGuard;
	Vector2 guardingPos;
};
