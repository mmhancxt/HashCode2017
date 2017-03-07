#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

#include "Objects.h"

using namespace std;


class FileLoader
{
public:
    FileLoader(const string & fileName)
    {
        m_file.open(fileName);
        if (!m_file.is_open())
        {
            cout << "Error open file: " << fileName << endl;
        }
    }
    virtual ~FileLoader()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

    virtual void Load() = 0;

protected:
    string GetLineAsString()
    {
        string line;
        getline(m_file, line);
        return line;
    }

    template<typename T>
    vector<T> GetLineAsVector(string seperator = " ")
    {
        string line;
        getline(m_file, line);

        vector<string> strVec = split(line, ' ');
        //boost::split(strVec, line, boost::is_any_of(seperator));// , boost::token_compress_on);

        vector<T> v;
        std::transform(strVec.begin(), strVec.end(), std::back_inserter(v), [](const string& s) {
            T value;
            stringstream ss;
            ss << s;
            ss >> value;
            return value;
        });
        return v;
    }
private:
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }



protected:
    ifstream m_file;
};


class InputLoader : public FileLoader
{
public:
    // Load input from file
    InputLoader(const string & fileName)
            : FileLoader(fileName)
    {
        const_video_nb = 0;
        const_endpoints_nb = 0;
        const_request_nb = 0;
        const_caches_nb = 0;
        const_cache_size = 0;
    }

    virtual ~InputLoader()
    {}

    virtual void Load() override
    {
        vector<int> consts = GetLineAsVector<int>();
        const_video_nb = consts[0];
        const_endpoints_nb = consts[1];
        const_request_nb = consts[2];
        const_caches_nb = consts[3];
        const_cache_size = consts[4];

        // caches
        for (int i = 0; i < const_caches_nb; ++i)
        {
            Cache* pCache = new Cache;
            pCache->id = i;
            pCache->size = const_cache_size;
            pCache->availableSize = const_cache_size;
            caches.push_back(pCache);
        }

        // videos
        vector<int> vs = GetLineAsVector<int>();
        for (int i = 0; i < vs.size(); ++i)
        {
            Video* pVideo = new Video;
            pVideo->id = i;
            pVideo->size = vs[i];
            videos.push_back(pVideo);
        }

        // endpoints
        for (int i = 0; i < const_endpoints_nb; ++i)
        {
            vector<int> lantency_cache_nb = GetLineAsVector<int>();
            int lantency = lantency_cache_nb[0];
            int cache_nb = lantency_cache_nb[1];
            EndPoint* pEndpoint = new EndPoint;
            pEndpoint->id = i;
            int currentEndpointId = endpoints.size();
            pEndpoint->data_center_latency = lantency;
            for (int i = 0; i < cache_nb; ++i)
            {
                vector<int> cache_id_cache_lantency = GetLineAsVector<int>();
                int cache_id = cache_id_cache_lantency[0];
                int cache_lantency = cache_id_cache_lantency[1];
                auto * pCache = caches[cache_id];
                pEndpoint->caches.push_back(pCache);
                pEndpoint->cacheId2Lantency.insert(make_pair(cache_id, cache_lantency));
                pCache->endpoints.push_back(pEndpoint);
                pCache->endpointId2Lantency.insert(make_pair(pEndpoint->id, cache_lantency));
            }
            endpoints.push_back(pEndpoint);
        }

        // requests
        for (int i = 0; i < const_request_nb; ++i)
        {
            vector<int> request = GetLineAsVector<int>();
            Request* pReq = new Request;
            pReq->id = i;
            pReq->pVideo = videos[request[0]];
            pReq->pEndPoint = endpoints[request[1]];
            pReq->request_nb = request[2];
            pReq->videoInCache = false;
            requests.push_back(pReq);
            endpoints[request[1]]->requests.push_back(pReq);
        }

        CalculateStatistics();

    }

private:
    void CalculateStatistics()
    {
        total_cache_size = const_cache_size * const_caches_nb;
        total_video_size = std::accumulate(videos.cbegin(), videos.cend(), 0, [](int size, const Video * pVideo) { return size + pVideo->size; } );
        for(Cache* pCache: caches)
        {
            pCache->updatePotentialCharge();
        }
    }



public:
    int const_video_nb;
    int const_endpoints_nb;
    int const_request_nb;   // request nb
    int const_caches_nb;
    int const_cache_size;
    vector<Cache*> caches;
    vector<Request*> requests;
    vector<Video*> videos;
    vector<EndPoint*> endpoints;

    int total_cache_size;
    int total_video_size;

};
