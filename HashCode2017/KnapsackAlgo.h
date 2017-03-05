//
// Created by zhi on 27/02/17.
//

#ifndef HASHCODE2017_KNAPSACKALGO_H
#define HASHCODE2017_KNAPSACKALGO_H

#include "InputLoader.h"
#include <map>
#include <numeric>
#include <unordered_set>


class KnapsackAlgo
{
public:
    KnapsackAlgo(InputLoader& loader, const std::string& outFilename) :
            m_loader(loader),
            m_requests(loader.requests),
            m_caches(loader.caches),
            m_videos(loader.videos),
            m_endpoints(loader.endpoints),
            m_outputFilename(outFilename)
    {}

    void Run()
    {
        for(Cache* pCache : m_caches)
        {
            cout << "calculate for cache: " << pCache->id << endl;
            vector<Video*> videosForCache = getVideosForCache(pCache);
            const int VIDEOS = videosForCache.size();
            const int CACHE_SIZE = m_loader.const_cache_size;

            vector<vector<int>> table(VIDEOS+1, vector<int>(CACHE_SIZE+1, 0));

            for(int i = 0; i < VIDEOS+1; ++i)
                table[i][0] = 0;
            for(int j = 0; j < CACHE_SIZE+1; ++j)
                table[0][j] = 0;

            for(int i = 1; i < VIDEOS+1; ++i)
            {
                Video* pVideo = videosForCache[i-1];
                int size = pVideo->size;
                int score = getScore(pVideo, pCache);
                for(int totalAllowedSize = 1; totalAllowedSize < CACHE_SIZE+1; ++totalAllowedSize)
                {
                    //cout << "i: " << i << ", j: " << totalAllowedSize << endl;
                    if(size > totalAllowedSize)
                        table[i][totalAllowedSize] = table[i-1][totalAllowedSize];
                    else
                    {
                        int score1 = score + table[i-1][totalAllowedSize-size];
                        int score2 = table[i-1][totalAllowedSize];
                        table[i][totalAllowedSize] = max(score1, score2);
                    }
                }
            }

            int totalAllowedSize = CACHE_SIZE;
            for(int i = VIDEOS; i > 0; --i)
            {
                Video * pVideo = videosForCache[i-1];
                int score = table[i][totalAllowedSize];
                int score2 = table[i-1][totalAllowedSize];
                if (score != score2)
                {
                    pCache->pushBackVideo(pVideo);
                    totalAllowedSize -= pVideo->size;
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

    }

    int getScore(Video* pVideo, Cache* pCache)
    {
        int score = 0;
        for(EndPoint* pEndpoint : pCache->endpoints)
        {
            for(const Request* pReq : pEndpoint->requests)
            {
                if(pReq->pVideo->id == pVideo->id)
                {
                    score += pReq->request_nb * (pEndpoint->data_center_latency - pEndpoint->cacheId2Lantency[pCache->id]);
                }
            }
        }
        return score;
    }


private:
    vector<Video*> getVideosForCache(const Cache* pCache)
    {
        set<Video*> videosForCache;
        for(const EndPoint* pEndpoint : pCache->endpoints)
        {
            //cout << "endpoint:" << pEndpoint->id << endl;
            for(const Request* pReq : pEndpoint->requests)
            {
                //auto it = std::find_if(videosForCache.begin(), videosForCache.end(), [pReq](const Video* v) { return v->id == pReq->pVideo->id; });
                //if (it == videosForCache.end())
                //    videosForCache.push_back(pReq->pVideo);
                videosForCache.insert(pReq->pVideo);
            }
        }
        return vector<Video*>(videosForCache.begin(), videosForCache.end());
    }


    vector<Cache*>& m_caches;
    vector<Request*>& m_requests;
    vector<Video*>& m_videos;
    vector<EndPoint*>& m_endpoints;

    std::string m_outputFilename;
    InputLoader& m_loader;

};

#endif //HASHCODE2017_KNAPSACKALGO_H
