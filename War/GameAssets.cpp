#include <Windows.h>
#include "GameAssets.h"

GameAssets::GameAssets() {
	soldier = NULL;
	tank = NULL;
	fighter = NULL;
	usaFlag = NULL;
	germanFlag = NULL;
	tree = NULL;
}

GameAssets::~GameAssets() {
	delete soldier;
	delete tank;
	delete fighter;
	delete usaFlag;
	delete germanFlag;
	delete tree;
}

bool GameAssets::load() {
	soldier = Bitmap::fromFile(L"assets\\soldier.bmp", true);
	tank = Bitmap::fromFile(L"assets\\tank.bmp", true);
	fighter = Bitmap::fromFile(L"assets\\fighter.bmp", true);
	usaFlag = Bitmap::fromFile(L"assets\\us-flag.bmp");
	germanFlag = Bitmap::fromFile(L"assets\\german-flag.bmp");
	tree = Bitmap::fromFile(L"assets\\tree.bmp", true);

	return true;
}
