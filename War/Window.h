#pragma once

#include <string>

class Window {
public:
	Window(std::wstring, int, int);
	~Window();
	HWND getHwnd();
	std::wstring getTitle();
	int getWidth();
	int getHeight();

private:
	HWND hwnd;
	std::wstring title;
	int width;
	int height;
};
