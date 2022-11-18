#pragma once

class Rect {
public:
	int left, top, right, bottom;

	Rect();
	Rect(int, int, int, int);
	~Rect();
	int width() const;
	int height() const;
};
