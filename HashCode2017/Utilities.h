#pragma once
#include "InputLoader.h"

void iterateEndPointMethod(InputLoader& loader);

inline int cacheAvailableSpace(const vector<Video>& videos, const Cache& cache) {
	int sum = 0;
    for (auto it = cache.videos.begin(); it != cache.videos.end(); ++it)
    {
        sum += videos[(*it)].size;
    }
	//for (int i = 0; i < cache.videos.size(); i++) {
	//	sum += cache.videos[i];
	//}
	return cache.size - sum;
}