#include "InputLoader.h"
#include "Tools.h"
#include "Utilities.h"

void iterateEndPointMethod(InputLoader& loader) {
	//Get requests per end point
	vector<vector<Request>> request_by_endpoint;
	request_by_endpoint.resize(loader.const_endpoints_nb);
	for (int i = 0; i < loader.const_endpoints_nb; i++) {
		for(int j = 0; j <loader.endpoints[i].requests.size();j++){
			request_by_endpoint[i].push_back(loader.requests[loader.endpoints[i].requests[j]]);
		}
	}
	//sort request per point
	for (int i = 0; i < loader.const_endpoints_nb; i++) {
		sort(request_by_endpoint[i].begin(), request_by_endpoint[i].end(), [&](Request r1, Request r2) { return r1.request_nb > r2.request_nb; });
	}

	//iterate through request ids
	vector<int> not_processed_request_ids;
	not_processed_request_ids.resize(loader.const_endpoints_nb);
	for (auto& id : not_processed_request_ids) {
		id = 0;
	}
	for(int round = 0; round <loader.const_request_desc;round++){
		//cout << "round " << round << endl;
		for (int i = 0; i < loader.endpoints.size(); i++) {
				int not_processed_request_id = not_processed_request_ids[i];
			if (not_processed_request_id <= request_by_endpoint[i].size() - 1){
				int video_id = request_by_endpoint[i][not_processed_request_id].video;
				int video_size = loader.videos[video_id].size;

				int min_latency = 9999999999;
				int min_available_cache = -1;
				for (int j = 0; j < loader.endpoints[i].cache_latencies.size(); j++) {
					if (loader.endpoints[i].cache_latencies[j] < min_latency) {
						int cache_id = loader.endpoints[i].cache_ids[j];
						int available_space = cacheAvailableSpace(loader.videos, loader.caches[cache_id]);
						if (cache_id == 0) {
						//	cout << "cache id" << cache_id << " " << available_space << " " << video_id<<" "<<video_size << endl;
						}
						if (available_space >= video_size) {
							min_available_cache = j;
							min_latency = loader.endpoints[i].cache_latencies[j];
						}
					}
				}
				if (min_available_cache != -1) {
					loader.caches[min_available_cache].videos.insert(video_id);
				}
				not_processed_request_ids[i]++;
			}
		}
	}
	int count = 0;
	for (int i = 0; i < loader.const_caches_nb; i++) {
		if (loader.caches[i].videos.size() > 0) {
			count++;
		}

	}
	
	cout << count<<endl;
	for (int i = 0; i < loader.const_caches_nb; i++) {
		if(loader.caches[i].videos.size()>0){
			string str;
			str += to_string(i);
			str+=" ";
			for (auto& id : loader.caches[i].videos) {
				str += to_string(id);
				str += " ";
			}
			cout << str << endl;
		}
	}
}