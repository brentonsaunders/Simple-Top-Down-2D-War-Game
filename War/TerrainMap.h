#pragma once

#include "TileMap.h"
#include "Random.h"
#include "Canvas.h"

class TerrainMap : public TileMap<int> {
public:
	TerrainMap(int, int);
	~TerrainMap();
	void draw(Canvas*, int, int);
	void draw(Canvas*);

protected:
	Random random;

private:
	void smooth();
};
