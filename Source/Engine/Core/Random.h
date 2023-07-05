#pragma once
#include <random>

namespace cg
{
	void seedRandom(unsigned int seed) { srand(seed); }
	int random() {
		return rand();
	}
	int random(unsigned int max) {
		return rand() % max;
	}
	int random(unsigned int min, unsigned int max) {
		return min + random(max - min + 1);
	}

}