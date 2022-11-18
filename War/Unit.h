#pragma once

#include "Bitmap.h"
#include "Canvas.h"
#include "GameAssets.h"
#include "Vector2.h"
#include "Random.h"
#include "ObstacleMap.h"

class Units;

class Unit {
public:
	enum Team {
		USA,
		GERMANY,
	};

	enum Type {
		SOLDIER,
		FIGHTER,
		TANK
	};

	Unit(Team);
	~Unit();
	void init();
	void setTeam(Team);
	Team getTeam() const;
	void setPos(Vector2);
	Vector2 getPos() const;
	void setDestination(Vector2);
	Vector2 getDestination() const;
	virtual void update(DWORD, Units *);
	virtual void draw(Canvas*, GameAssets*);
	void drawFlag(Canvas*, GameAssets*);
	void drawHealthBar(Canvas*, GameAssets*);
	virtual double getSpeed() = 0;
	virtual double getTurnSpeed() = 0;
	virtual int getSteeringAccurary();
	virtual void onArrived() = 0;
	bool isAlive();
	bool isDeadForLongEnough();
	double getHp();
	void damage(double);
	virtual int getTotalHp() const = 0;
	virtual Type getType() const = 0;
	virtual int getRadius() const = 0;
	virtual int getCostToTraverse(ObstacleMap::Obstacle) const;
	TileMap getTraversalMap(const ObstacleMap&) const;

protected:
	Vector2 pos;
	Vector2 destination;
	double angle;
	Team team;
	double hp;
	DWORD deadTime;
	static Random random;

	void steer(DWORD);
};
