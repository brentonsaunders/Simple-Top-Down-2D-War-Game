#pragma once

#include "Unit.h"
#include "Canvas.h"
#include "GameAssets.h"
#include "BulletEmitter.h"

class Tank : public Unit {
public:
	Tank(Team);
	~Tank();
	void update(DWORD, Units*);
	void draw(Canvas*, GameAssets*);
	double getSpeed();
	double getTurnSpeed();
	void onArrived();
	int getTotalHp() const;
	Type getType() const;
	int getRadius() const;

private:
	double turretAngle;
	Unit* opponent;
	BulletEmitter bulletEmitter;

	void turnToFaceOpponent(DWORD);
	bool isFacingOpponent();
};
