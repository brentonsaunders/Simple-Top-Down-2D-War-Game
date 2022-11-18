#pragma once

#include "Unit.h"
#include "Canvas.h"
#include "GameAssets.h"
#include "BulletEmitter.h"

class Soldier : public Unit {
public:
	Soldier(Team);
	~Soldier();
	void update(DWORD, Units*);
	void draw(Canvas*, GameAssets*);
	double getSpeed();
	double getTurnSpeed();
	void onArrived();
	int getTotalHp() const;
	Type getType() const;
	int getRadius() const;

private:
	Unit* opponent;
	BulletEmitter bulletEmitter;

	void turnToFaceOpponent(DWORD);
	bool isFacingOpponent();
};
