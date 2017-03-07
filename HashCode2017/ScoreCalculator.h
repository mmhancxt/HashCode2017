//
// Created by zhi on 06/03/17.
//

#ifndef HASHCODE2017_SCORECALCULATOR_H
#define HASHCODE2017_SCORECALCULATOR_H

#include <unordered_map>
#include "InputLoader.h"
#include "Objects.h"


class ScoreCalculator : public FileLoader
{
public:
    // Load input file and output file
    ScoreCalculator(const string & input, const string& output)
            : FileLoader(output), m_outputFile(output), m_inputLoader(input)
    {
    }

    virtual ~ScoreCalculator()
    {}

    virtual void Load() override
    {
        m_inputLoader.Load();
        loadOutput(m_inputLoader.caches, m_inputLoader.videos);
    }

    void Calculate()
    {
        double totalReducedLatency = 0;
        double totalReq = 0;
        // for each Endpoint, sort caches by latency
        for(EndPoint* pEndpoint : m_inputLoader.endpoints)
        {
            std::sort(pEndpoint->caches.begin(), pEndpoint->caches.end(), [pEndpoint](Cache*pCache1, Cache* pCache2)
                { return pCache1->endpointId2Lantency[pEndpoint->id] < pCache2->endpointId2Lantency[pEndpoint->id]; });
        }

        for(EndPoint* pEndpoint : m_inputLoader.endpoints)
        {
            for(Request* pReq : pEndpoint->requests)
            {
                totalReq += pReq->request_nb;

                //Video * pVideo =
                int videoId = pReq->pVideo->id;
                int cacheId = -1;
                for(Cache* pCache : pEndpoint->caches)
                {
                    if(videoInCache(pCache->id, videoId))
                    {
                        cacheId = pCache->id;
                        break;
                    }
                }
                if(cacheId != -1)
                {
                    totalReducedLatency += pReq->request_nb * (pEndpoint->data_center_latency - pEndpoint->cacheId2Lantency[cacheId]);
                }
                // else
                //      totalReducedLatency += 0;
            }
        }

        cout << "file: " << m_outputFile << ", totalReducedLatency: " << totalReducedLatency << ", totalReq: " << totalReq << ", score: " << (totalReducedLatency/totalReq) * 1000 << endl;
    }

private:
    void loadOutput(vector<Cache* > & caches, const vector<Video* > &videos)
    {
        string usedCachesStr = GetLineAsString();
        int usedCaches = std::stoi(usedCachesStr);
        for(int i = 0; i < usedCaches; ++i)
        {
            vector<int> numbers = GetLineAsVector<int>();
            int cacheId = numbers[0];
            Cache* pCache = caches[cacheId];
            m_cacheId2Videos[cacheId] = std::unordered_set<int>();
            for(int j = 1; j < numbers.size(); ++j)
            {
                const Video* pVideo = videos[numbers[j]];
                if(pCache->getAvaiablesize() >= pVideo->size)
                {
                    pCache->pushBackVideo(pVideo);
                    m_cacheId2Videos[cacheId].insert(pVideo->id);
                }
                else
                {
                    cout << "Cache " << pCache->id << " doesn't have enough space for video " << pVideo->id << endl;
                    return;
                }
            }
        }
    }

    inline bool videoInCache(int cacheId, int videoId)
    {
        auto videos = m_cacheId2Videos[cacheId];
        return videos.find(videoId) != videos.end();
    }

private:
    std::string m_outputFile;
    InputLoader m_inputLoader;
    std::unordered_map<int, std::unordered_set<int>> m_cacheId2Videos;

};


#endif //HASHCODE2017_SCORECALCULATOR_H
