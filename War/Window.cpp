#include <Windows.h>
#include "Window.h"

using namespace std;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

Window::Window(wstring title, int width, int height) {
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wc;

	this->title = title;
	this->width = width;
	this->height = height;

	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = title.c_str();
	wc.hInstance = hInst;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	RegisterClass(&wc);

	RECT rect = {0, 0, width, height};

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		0, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInst, NULL);

	ShowWindow(hwnd, SW_SHOW);
}

Window::~Window() {

}

HWND Window::getHwnd() {
	return hwnd;
}

std::wstring Window::getTitle() {
	return title;
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
