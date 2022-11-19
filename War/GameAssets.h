#pragma once

#include "Bitmap.h"

class GameAssets {
public:
	Bitmap* soldier;
	Bitmap* tank;
	Bitmap* fighter;
	Bitmap* usaFlag;
	Bitmap* germanFlag;
	Bitmap* tree;
	Bitmap* hedgehog;
	Bitmap* trench;

	GameAssets();
	~GameAssets();
	bool load();
};
