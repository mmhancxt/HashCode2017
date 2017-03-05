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
            m_outputFilename(outFilename)
    {}

    void Run()
    {
        // sort endpoints by data center latency from high to low
        std::sort(m_endpoints.begin(), m_endpoints.end(), [](const EndPoint* p1, const EndPoint* p2) { return p1->data_center_latency > p2->data_center_latency; });

        // sort requests in each endpoint
        for (auto* pEndpoint : m_endpoints)
        {
            std::sort(pEndpoint->requests.begin(), pEndpoint->requests.end(), [](const Request * pReq1, const Request *pReq2)
            {
                return pReq1->request_nb * (1000 - pReq1->pVideo->size) > pReq2->request_nb*(1000 - pReq2->pVideo->size);
                //return pReq1->request_nb > pReq2->request_nb;
            });
        }

        for (auto* pEndpoint : m_endpoints)
        {
            for(auto* pReq : pEndpoint->requests)
            {
                const Video* pVideo = pReq->pVideo;
                if(isVideoInCaches(pVideo, pEndpoint->caches))
                {
                    updatePotentialCharge(pEndpoint, pReq);
                    pReq->videoInCache = true;
                    continue;  // continue to next request
                }

                Cache * pCache = getCacheForVideo(pEndpoint, pVideo);

                if(pCache != nullptr)
                {
                    // put video into cache
                    //minLatencyAvailableCache->videos.push_back(pVideo);
                    pCache->pushBackVideo(pVideo);
                    updatePotentialCharge(pEndpoint, pReq);
                    pReq->videoInCache = true;
                }
            }
        }


        ofstream ofs(m_outputFilename);
        int count = std::count_if(m_caches.begin(), m_caches.end(), [](const Cache* pCache) { return pCache->videos.size() > 0; });

        ofs << count<<endl;
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
                ofs << str << endl;
            }
        }

        analyzeResult();

    }


private:
    Cache* getCacheForVideo(const EndPoint* pEndpoint, const Video* pVideo)
    {
        //Cache* pCache2 = getMinLatencyCache(pEndpoint, pVideo);

        Cache* pCache = getMaxScoreCache(pEndpoint, pVideo);
        return pCache;
    }

    Cache* getMinLatencyCache(const EndPoint* pEndpoint, const Video* pVideo)
    {
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
        return minLatencyAvailableCache;
    }

    Cache* getMaxScoreCache(const EndPoint* pEndpoint, const Video* pVideo)
    {
        auto it = std::max_element(pEndpoint->caches.cbegin(), pEndpoint->caches.cend(),
                                          [pEndpoint, pVideo, this](const Cache* pCache1, const Cache* pCache2)  // true == pCache1 < pCache2
                                          {
                                              if(pCache1 == nullptr || pCache2 == nullptr)
                                              {
                                                  cout << "pCache is null!" << endl;
                                              }
                                              if(!pCache1->hasEnoughSpaceForVideo(pVideo) && pCache2->hasEnoughSpaceForVideo(pVideo))
                                                  return true;

                                              if (pCache1->hasEnoughSpaceForVideo(pVideo) && pCache2->hasEnoughSpaceForVideo(pVideo))
                                              {
                                                  const int id = pEndpoint->id;
                                                  int latency1 = pCache1->endpointId2Lantency.find(id)->second;
                                                  int latency2 = pCache2->endpointId2Lantency.find(id)->second;
                                                  // the latency is greater, the available size is smaller, the cache has a smaller score
                                                  return latency1 * (500000 - pCache1->availableSize) * pCache1->potentialCharge > latency2 * (500000-pCache2->availableSize) * pCache2->potentialCharge;
                                                  //return latency1 > latency2;  // the latency is greater, the cache has a smaller score

                                              }

                                              return false;
                                          }
        );
        if(it != pEndpoint->caches.cend())
        {
            Cache * pCache = *it;
            if(pCache->hasEnoughSpaceForVideo(pVideo))
                return pCache;
            else
                return nullptr;
        } else
            return nullptr;
    }


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

    void updatePotentialCharge(EndPoint* pEndpoint, Request* pReq)
    {
        for(Cache* pCache : pEndpoint->caches)
        {
            pCache->potentialCharge -= pReq->request_nb;
        }
    }

    void analyzeResult()
    {
        for (auto* pEndpoint : m_endpoints)
        {
            std::copy_if(pEndpoint->requests.cbegin(), pEndpoint->requests.cend(), std::back_inserter(pEndpoint->requestsNotInCache), [](const Request* pReq)
            {
                return pReq->videoInCache == false;
            });
        }

        m_totalUnusedCacheSize = std::accumulate(m_caches.cbegin(), m_caches.cend(), 0, [](int sum, const Cache* pCache)
        {
            return sum + pCache->availableSize;
        });
    }


    vector<Cache*>& m_caches;
    vector<Request*>& m_requests;
    vector<Video*>& m_videos;
    vector<EndPoint*>& m_endpoints;

    std::string m_outputFilename;
    InputLoader& m_loader;


    int m_totalUnusedCacheSize;
};

#endif //HASHCODE2017_ALGO_H
