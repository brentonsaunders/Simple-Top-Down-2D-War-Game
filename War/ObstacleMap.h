#pragma once

#include "TerrainMap.h"
#include "GameAssets.h"
#include "Obstacle.h"

class ObstacleMap {
public:
	ObstacleMap(int, int);
	~ObstacleMap();
	int getWidth() const;
	int getHeight() const;
	Obstacle::Type get(int, int) const;
	void draw(Canvas*, GameAssets *);

private:
	TileMap<Obstacle::Type> obstacleMap;
	TerrainMap terrainMap;
	Random random;

	void seedWater();
	void seedTrees();
	void spread(Obstacle::Type);
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
