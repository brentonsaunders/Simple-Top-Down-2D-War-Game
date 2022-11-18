#pragma once

class Random {
public:
	Random();
	Random(int);
	~Random();
	int nextInt();
	int nextInt(int);
	double nextDouble();

private:
	unsigned int seed;
	unsigned int last;
};
