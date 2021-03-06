#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


#include <set>

//#include <boost/algorithm/string.hpp>

using namespace std;

struct Request
{
    int id;
    int video;
    int request_nb;
    int endpoint;
    int points;
    bool treated;
};

struct Cache
{
    int size;
    vector<int> endpoints;
    set<int> videos;
};

struct Video
{
    int size;
};

struct EndPoint
{
    int data_center_lantency;
    vector<int> cache_ids;
    vector<int> cache_latencies;
    vector<int> requests;
};


class InputLoader
{
public:
    // Load input from file
    InputLoader(const string & fileName)
    {
        const_video_nb = 0;
        const_endpoints_nb = 0;
        const_request_desc = 0;
        const_caches_nb = 0;
        const_cache_size = 0;
        m_file.open(fileName);
        if (m_file.is_open())
        {
            InitFromFile();
        }
        else
        {
            cout << "Error open file: " << fileName << endl;
        }
    }

    // Test with manually crafted data
    InputLoader()
    {
        Init();
    }

    ~InputLoader()
    {
        if (m_file.is_open())
        {
            m_file.close();
        }
    }

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
private:
    void Init()
    {
        const_video_nb = 5;
        const_endpoints_nb = 2;
        const_request_desc = 4;
        const_caches_nb = 3;
        const_cache_size = 100;
        
        // Videos
        vector<int> vs = {50, 50, 80, 30, 110};
        for (auto v : vs) {
            Video vid;
            vid.size = v;
            videos.push_back(vid);
        }
        
        // Endpoints
        EndPoint e1;
        e1.data_center_lantency = 1000;
        for (int i = 0; i < 3; ++i) {
            e1.cache_ids.push_back(i);
        }
        e1.cache_latencies.push_back(100);
        e1.cache_latencies.push_back(300);
        e1.cache_latencies.push_back(200);
        
        EndPoint e2;
        e2.data_center_lantency = 500;
        
        endpoints.push_back(e1);
        endpoints.push_back(e2);
        
        // Requests
        Request r1;
        r1.video = 3;
        r1.endpoint = 0;
        r1.request_nb = 1500;
        requests.push_back(r1);
        
        Request r2;
        r2.video = 0;
        r2.endpoint = 1;
        r2.request_nb = 1000;
        requests.push_back(r2);
        
        Request r3;
        r3.video = 4;
        r3.endpoint = 0;
        r3.request_nb = 500;
        requests.push_back(r3);
        
        Request r4;
        r4.video = 1;
        r4.endpoint = 0;
        r4.request_nb = 1000;
        requests.push_back(r4);
        
    }

    void InitFromFile()
    {
        vector<int> consts = GetLineAsVector<int>();
        const_video_nb = consts[0];
        const_endpoints_nb = consts[1];
        const_request_desc = consts[2];
        const_caches_nb = consts[3];
        const_cache_size = consts[4];

        // caches
        for (int i = 0; i < const_caches_nb; ++i)
        {
            Cache cache;
            cache.size = const_cache_size;
            caches.push_back(cache);
        }

        // videos
        vector<int> vs = GetLineAsVector<int>();
        for (auto size : vs)
        {
            Video v; v.size = size;
            videos.push_back(v);
        }

        // endpoints
        for (int i = 0; i < const_endpoints_nb; ++i)
        {
            vector<int> lantency_cache_nb = GetLineAsVector<int>();
            int lantency = lantency_cache_nb[0];
            int cache_nb = lantency_cache_nb[1];
            EndPoint endpoint;
            int currentEndpointId = endpoints.size();
            endpoint.data_center_lantency = lantency;
            for (int i = 0; i < cache_nb; ++i)
            {
                vector<int> cache_id_cache_lantency = GetLineAsVector<int>();
                int cache_id = cache_id_cache_lantency[0];
                endpoint.cache_ids.push_back(cache_id);
                endpoint.cache_latencies.push_back(cache_id_cache_lantency[1]);
                caches[cache_id].endpoints.push_back(currentEndpointId);
            }
            endpoints.push_back(endpoint);
        }

        // requests
        for (int i = 0; i < const_request_desc; ++i)
        {
            vector<int> request = GetLineAsVector<int>();
            Request req;
            req.id = i;
            req.video = request[0];
            req.endpoint = request[1];
            req.request_nb = request[2];
            req.treated = false;
            requests.push_back(req);
            endpoints[request[1]].requests.push_back(requests.size() - 1);

        }

    }

private:
    ifstream m_file;

public:
    int const_video_nb;
    int const_endpoints_nb;
    int const_request_desc;   // request nb
    int const_caches_nb;
    int const_cache_size;
    vector<Cache> caches;
    vector<Request> requests;
    vector<Video> videos;
    vector<EndPoint> endpoints;
};
