#include "InputLoader.h"
#include "Tools.h"
#include "Utilities.h"

void iterateEndPointMethod(InputLoader& loader) {
	for (auto& endp : loader.endpoints) {
		sort(endp.requests.begin(), endp.requests.end(), [&](Request r1, Request r2) { return r1.request_nb > r2.request_nb; });
	}
	vector<int> not_processed_request_ids;
	not_processed_request_ids.resize(loader.endpoints.size());
	for (auto& id : not_processed_request_ids) {
		id = 0;
	}
	for (int i = 0; i < loader.endpoints.size(); i++) {
		int video_id = not_processed_request_ids[i];
		int video_size = loader.videos[video_id];

		int min_latency = 9999999999;
		int min_available_cache = -1;
		for (int j = 0; j < loader.endpoints[i].cache_latencies.size(); j++) {
			if (loader.endpoints[i].cache_latencies[j] < min_latency) {
				int cache_id = loader.endpoints[i].cache_ids[j];
				int available_space = cacheAvailableSpace(loader.caches[cache_id]);
			}
		}
	}

}