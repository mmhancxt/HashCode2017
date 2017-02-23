#pragma once
#include "InputLoader.h"

void iterateEndPointMethod(InputLoader& loader);

inline int cacheAvailableSpace(Cache& cache) {
	int sum = 0;
	for (int i = 0; i < cache.videos.size(); i++) {
		sum += cache.videos[i];
	}
	return cache.size - sum;
}