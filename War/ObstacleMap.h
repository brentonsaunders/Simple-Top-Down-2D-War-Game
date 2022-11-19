#pragma once

#include "TerrainMap.h"
#include "GameAssets.h"

class ObstacleMap : public TerrainMap {
public:
	enum Obstacle {
		WATER,
		TREES,
		GROUND0,
		GROUND1,
		GROUND2,
		GROUND3,
		GROUND4,
		GROUND5
	};

	ObstacleMap(int, int);
	~ObstacleMap();
	Obstacle getObstacle(int, int) const;
	void draw(Canvas*, GameAssets *);

private:
	TileMap map;

	void seedWater();
	void seedTrees();
	void spread(int);
};

class TerrainMapGround {
public:
	TerrainMapGround(const TerrainMap*);
	void draw(Canvas*, GameAssets*);

private:
	TerrainMap* terrainMap;
};

class TerrainMapTrees {
public:
	TerrainMapTrees(const TerrainMap*);
	void draw(Canvas*, GameAssets*);

private:
	const TerrainMap* terrainMap;
};
