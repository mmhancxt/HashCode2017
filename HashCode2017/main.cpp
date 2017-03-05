#include <iostream>
#include "InputLoader.h"
#include "Algo.h"
#include "KnapsackAlgo.h"

using namespace std;

int main(int argc, const char * argv[])
{
    std::map<std::string, std::string> inputOutputs
    {
            {
                    "/home/zhi/workspace/HashCode2017/HashCode2017/input/me_at_the_zoo.in",
                    "/home/zhi/workspace/HashCode2017/HashCode2017/output/me_at_the_zoo.out"
            }
            ,
            {
                    "/home/zhi/workspace/HashCode2017/HashCode2017/input/trending_today.in",
                    "/home/zhi/workspace/HashCode2017/HashCode2017/output/trending_today.out"
            }
            ,
            {
                    "/home/zhi/workspace/HashCode2017/HashCode2017/input/kittens.in",
                    "/home/zhi/workspace/HashCode2017/HashCode2017/output/kittens.out"
            }
            ,
            {
                    "/home/zhi/workspace/HashCode2017/HashCode2017/input/videos_worth_spreading.in",
                    "/home/zhi/workspace/HashCode2017/HashCode2017/output/videos_worth_spreading.out"
            }

    };


    for(const auto inputOutput : inputOutputs)
    {
        InputLoader loader(inputOutput.first);
        //Algo algo(loader, inputOutput.second);
        KnapsackAlgo algo(loader, inputOutput.second);
        algo.Run();
    }

    return 0;
}
