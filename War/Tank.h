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
	int getCostToTraverse(Obstacle::Type) const;
	bool isGroundUnit() const;

private:
	double turretAngle;
	BulletEmitter bulletEmitter;

	void turnToFaceOpponent(DWORD, Unit*);
	bool isFacingOpponent(Unit*);
	void doRollOverDamage(DWORD, Units*);
};
