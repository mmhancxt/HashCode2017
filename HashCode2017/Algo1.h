#include "InputLoader.h"

class Algo
{
    Algo(InputLoader& input) : loader(input) {}

    void Sort()
    {
        vector<Request>& requests = loader.requests;
        vector<Cache> caches = loader.cashes;
        vector<Video> videos = loader.videos;
        vector<EndPoint> endpoints = loader.endpoints;

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

    InputLoader& loader;
};
