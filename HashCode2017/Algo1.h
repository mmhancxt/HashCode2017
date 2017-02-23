#include "InputLoader.h"

class Algo
{
    Algo(InputLoader& input) : 
        loader(input),
        requests(loader.requests),
        caches(loader.caches),
        endpoints(loader.endpoints)
    {}

    void Sort()
    {
        for (Request& r : requests)
        {
            EndPoint& e = endpoints[r.endpoint];
            int Ld = e.data_center_lantency;
            int minL = Ld;
            for (int i = 0; i < cache_latencies.size();i++)
            {
                if (cache_latencies[i] < minL)
                {
                    minL = cache_latencies[i];
                }
            }
            r.points = r.request_nb * (Ld - minL);
        }

        sort(request.begin(), request.end(), [](const Request& r1, const Request& r2)
                {
                    r1.points > r2.points;
                });
    }

    void Run()
    {
        Sort();
        for (Request& r : loader.request)
        {
            int cid = findAvailableCache(r);
            if (cid != -1)
            {
                caches[cid].videos.insert(r.video);
            }
        }
    }

    int findAvailableCache(Request& r)
    {
        EndPoint& e = endpints[r.endpoint];
        for (int i = 0 ; i < e.cache_latencies.size(); i++)
        {
            int cid = e.cache_ids[i];
            if (cacheAvailableSpace(caches[cid]) > videos[r.video].size)
            {
                return cid; 
            }
        }
        return -1;
    }

    vector<Cache> caches;
    vector<Request> requests;
    vector<Video> videos;
    vector<EndPoint> endpoints;

    InputLoader& loader;
};
