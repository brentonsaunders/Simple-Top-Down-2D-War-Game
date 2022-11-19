#pragma once

#include <vector>
#include "TerrainMap.h"
#include "GameAssets.h"

class ObstacleMap {
public:
	enum Type {
		NONE,
		GROUND0,
		GROUND1,
		GROUND2,
		GROUND3,
		GROUND4,
		GROUND5,
		TRENCH,
		HEDGEHOG,
		WATER,
		TREES,
	};

	ObstacleMap(int, int);
	~ObstacleMap();
	int getWidth() const;
	int getHeight() const;
	Type get(int, int) const;
	bool addObstacle(Type, int, int);
	void update(DWORD);
	void draw(Canvas*, GameAssets *);

private:
	struct Obstacle {
		int x, y;
		int timeLeft;
	};

	TileMap<Type> obstacleMap;
	TerrainMap terrainMap;
	std::vector<Obstacle> obstacles;
	Random random;

	void seedWater();
	void seedTrees();
	void spread(Type);
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
