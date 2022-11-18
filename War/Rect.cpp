#include "Rect.h"

Rect::Rect() {
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

Rect::Rect(int left, int top, int right, int bottom) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}

Rect::~Rect() {

}

int Rect::width() const {
	return right - left;
}

int Rect::height() const {
	return bottom - top;
}