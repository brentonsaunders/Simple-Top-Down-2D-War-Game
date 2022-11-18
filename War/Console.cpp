#include <windows.h>
#include <cstdio>
#include <iostream>
#include "Console.h"

using namespace std;

void Console::init() {
	FILE* stream;

	AllocConsole();

	freopen_s(&stream, "CONOUT$", "w", stdout);
}
