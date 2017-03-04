//
// Created by zhi on 27/02/17.
//

#ifndef HASHCODE2017_ALGO_H
#define HASHCODE2017_ALGO_H

#include "InputLoader.h"
#include <map>
#include <numeric>
#include <unordered_set>
#include <boost/functional/hash.hpp>

struct pair_hash
{
public:
	size_t operator()(const pair<int, int>& key) const
	{
		size_t seed = 0;
		boost::hash_combine(seed, key.first);
		boost::hash_combine(seed, key.second);
		return seed;
	}

};

class Algo
{
public:
    Algo(InputLoader& loader, const std::string& outFilename) :
            m_loader(loader),
            m_requests(loader.requests),
            m_caches(loader.caches),
            m_videos(loader.videos),
            m_endpoints(loader.endpoints),
            m_ofs(outFilename)
    {}

    void Run()
    {
        // sort endpoints by data center lantency from hight to low
        std::sort(m_endpoints.begin(), m_endpoints.end(), [](const EndPoint* p1, const EndPoint* p2) { return p1->data_center_lantency > p2->data_center_lantency; });

        // sort requests in each endpoint
        for (auto* pEndpoint : m_endpoints)
        {
            std::sort(pEndpoint->requests.begin(), pEndpoint->requests.end(), [](const Request * pReq1, const Request *pReq2)
            {
                //return r1.request_nb * (1000 - videos[r1.video].size) > r2.request_nb*(1000 - videos[r2.video].size);
                return pReq1->request_nb > pReq2->request_nb;
            });
        }

        for (auto* pEndpoint : m_endpoints)
        {
            for(auto* pReq : pEndpoint->requests)
            {
                const Video* pVideo = pReq->pVideo;
                if(isVideoInCaches(pVideo, pEndpoint->caches))
                {
                    continue;  // continue to next request
                }

                int minLatency = std::numeric_limits<int>::max();
                Cache* minLatencyAvailableCache = nullptr;
                for(auto* pCache : pEndpoint->caches)
                {
                    int latency = pCache->endpointId2Lantency[pEndpoint->id];
                    if(latency < minLatency)
                    {
                        if(pCache->hasEnoughSpaceForVideo(pVideo))
                        {
                            minLatencyAvailableCache = pCache;
                            minLatency = latency;
                        }
                    }
                }
                if(minLatencyAvailableCache != nullptr)
                {
                    // put video into cache
                    minLatencyAvailableCache->videos.push_back(pVideo);
                }
            }
        }


        int count = std::count_if(m_caches.begin(), m_caches.end(), [](const Cache* pCache) { return pCache->videos.size() > 0; });

        m_ofs << count<<endl;
        for(const Cache* pCache: m_caches)
        {
            if(pCache->videos.size() > 0)
            {
                string str;
                str += to_string(pCache->id);
                str += " ";
                for (const Video* pVideo : pCache->videos)
                {
                    str += to_string(pVideo->id);
                    str += " ";
                }
                m_ofs << str << endl;
            }
        }

    }


private:
    bool isVideoInCaches(const Video* pVideo, const vector<Cache*>& caches)
    {
        for(const Cache* pCache: caches)
        {
            if(std::find(pCache->videos.begin(), pCache->videos.end(), pVideo) != pCache->videos.end())
            {
                return true;
            }
        }
        return false;
    }


    vector<Cache*>& m_caches;
    vector<Request*>& m_requests;
    vector<Video*>& m_videos;
    vector<EndPoint*>& m_endpoints;

    ofstream m_ofs;
    InputLoader& m_loader;
};

#endif //HASHCODE2017_ALGO_H
