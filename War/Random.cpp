#include <Windows.h>
#include "Random.h"

Random::Random() {
	seed = timeGetTime();
	last = seed;
	srand(seed);
}

Random::Random(int seed) {
	this->seed = seed;
	last = seed;
}

Random::~Random() {

}

int Random::nextInt() {
	/*
	unsigned int next = (97 * last + 61) % RAND_MAX;

	last = next;

	return next;
	*/

	return rand();
}

int Random::nextInt(int max) {
	return nextInt() % max;
}

double Random::nextDouble() {
	return (double)nextInt() / (double)RAND_MAX;
}
