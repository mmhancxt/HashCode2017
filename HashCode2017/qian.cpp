#include "InputLoader.h"
#include "Tools.h"
#include "Utilities.h"
#include <map>

void iterateEndPointMethod(InputLoader& loader)
{
	//Get requests per end point
    auto endPoints = loader.endpoints;

    std::sort(endPoints.begin(), endPoints.end(), [](const EndPoint &e1, const EndPoint &e2) { return e1.data_center_lantency > e2.data_center_lantency; });

    map<int, vector<Request>> endPointId2Requests;
    for (int i = 0; i < endPoints.size(); i++)
    {
        //vector<int> req_ids = endPoints[i].requests;
        vector<Request> reqs;
		for(int j = 0; j <endPoints[i].requests.size();j++)
        {
            reqs.push_back(loader.requests[endPoints[i].requests[j]]);
		}
        sort(reqs.begin(), reqs.end(), 
            [&loader](const Request&r1, const Request&r2)
            { 
                return r1.request_nb * (1000 - loader.videos[r1.video].size) > r2.request_nb*(1000 - loader.videos[r2.video].size);
            }
        );
        endPointId2Requests.insert(make_pair(endPoints[i].id, reqs));
	}

    for (int i = 0; i < endPoints.size(); ++i)
    {
        EndPoint endP = endPoints[i];
        vector<Request> reqs = endPointId2Requests[endP.id];
        for (int j = 0; j < reqs.size(); ++j)
        {
            //cout << i << " " << j << endl;
            int video_id = reqs[j].video;
            int video_size = loader.videos[video_id].size;

            int min_latency = 9999999999;
            int min_available_cache = -1;
            for (int k = 0; k < endP.cache_latencies.size(); k++)
            {
                if (endP.cache_latencies[k] < min_latency) {
                    int cache_id = endP.cache_ids[k];
                    int available_space = cacheAvailableSpace(loader.videos, loader.caches[cache_id]);
                    //if (cache_id == 0) {
                    //    	//cout << "cache id" << cache_id << " " << available_space << " " << video_id<<" "<<video_size << endl;
                    //}
                    if (available_space >= video_size) {
                        min_available_cache = cache_id;
                        min_latency = endP.cache_latencies[k];
                    }
                }
            }
            if (min_available_cache != -1) {
                loader.caches[min_available_cache].videos.insert(video_id);
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
	for (int i = 0; i < loader.const_caches_nb; i++)
    {
		if(loader.caches[i].videos.size()>0)
        {
			string str;
			str += to_string(i);
			str+=" ";
			for (auto& id : loader.caches[i].videos)
            {
				str += to_string(id);
				str += " ";
			}
			cout << str << endl;
		}
	}
}