//
// Created by zhi on 04/03/17.
//

#ifndef HASHCODE2017_OBJECTS_H
#define HASHCODE2017_OBJECTS_H

#include <vector>
#include <map>

using namespace std;


struct EndPoint;


struct Video
{
    int id;
    int size;
};

struct Request
{
    int id;
    int request_nb;
    //int endpoint;
    Video* pVideo;
    EndPoint* pEndPoint;
    bool treated = false;
};

struct Cache
{
    int id;
    int size;
    vector<EndPoint*> endpoints;
    vector<const Video*> videos;
    map<int, int> endpointId2Lantency;

    int getAvaiablesize() const
    {
        int consumedSize = std::accumulate(videos.begin(), videos.end(), 0, [](int consumedSize, const Video* pVideo) { return consumedSize+pVideo->size; });
        return size - consumedSize;
    }

    bool hasEnoughSpaceForVideo(const Video* pVideo) const
    {
        return getAvaiablesize() >= pVideo->size;
    }

};


struct EndPoint
{
    int id;
    int data_center_lantency;
    vector<Cache*> caches;
    vector<Request*> requests;
    map<int, int> cacheId2Lantency;
};

#endif //HASHCODE2017_OBJECTS_H
