#pragma once

#include "Bitmap.h"
#include "Canvas.h"
#include "GameAssets.h"
#include "Vector2.h"
#include "Random.h"
#include "ObstacleMap.h"
#include "Path.h"

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
	virtual void init();
	void setTeam(Team);
	Team getTeam() const;
	void setPos(Vector2);
	Vector2 getPos() const;
	virtual void update(DWORD, Units *);
	virtual void draw(Canvas*, GameAssets*);
	void drawFlag(Canvas*, GameAssets*);
	void drawHealthBar(Canvas*, GameAssets*);
	virtual double getSpeed() = 0;
	virtual double getTurnSpeed() = 0;
	double getTurnRadius();
	virtual void onArrived() = 0;
	bool isAlive();
	bool isDeadForLongEnough();
	double getHp();
	void damage(double);
	virtual int getTotalHp() const = 0;
	virtual Type getType() const = 0;
	virtual int getRadius() const = 0;
	virtual int getCostToTraverse(Obstacle::Type) const;
	TileMap<int> getTraversalMap(const ObstacleMap&) const;
	void follow(const Path&);
	virtual bool isGroundUnit() const;
	virtual bool isAirUnit() const;

protected:
	Vector2 pos;
	double angle;
	Team team;
	double hp;
	DWORD deadTime;
	Path path;
	static Random random;

	void steer(DWORD, const Vector2&);
};
