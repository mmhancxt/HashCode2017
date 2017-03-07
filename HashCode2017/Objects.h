//
// Created by zhi on 04/03/17.
//

#ifndef HASHCODE2017_OBJECTS_H
#define HASHCODE2017_OBJECTS_H

#include <vector>
#include <map>

using namespace std;


struct EndPoint;
struct Cache;


struct Video
{
    int id;
    int size;
};

struct Request
{
    int id;
    int request_nb;
    Video* pVideo;
    EndPoint* pEndPoint;
    bool videoInCache = false;
};

struct EndPoint
{
    int id;
    int data_center_latency;
    vector<Cache*> caches;
    vector<Request*> requests;
    map<int, int> cacheId2Lantency;

    vector<Request*> requestsNotInCache;
};


struct Cache
{
    int id;
    int size;
    vector<EndPoint*> endpoints;
    vector<const Video*> videos;
    map<int, int> endpointId2Lantency;
    int availableSize;
    int potentialCharge;

    void pushBackVideo(const Video* pVideo)
    {
        videos.push_back(pVideo);
        availableSize -= pVideo->size;
    }

    void updatePotentialCharge()
    {
        for(const EndPoint* pEndpoint : endpoints)
        {
            for(const Request* pReq : pEndpoint->requests)
            {
                potentialCharge += pReq->request_nb;
            }
        }
    }

    inline int getAvaiablesize() const
    {
        return availableSize;
        //int consumedSize = std::accumulate(videos.begin(), videos.end(), 0, [](int consumedSize, const Video* pVideo) { return consumedSize+pVideo->size; });
        //return size - consumedSize;
    }

    inline bool hasEnoughSpaceForVideo(const Video* pVideo) const
    {
        return getAvaiablesize() >= pVideo->size;
    }

};




#endif //HASHCODE2017_OBJECTS_H
