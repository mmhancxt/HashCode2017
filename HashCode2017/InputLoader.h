#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

class InputLoader
{
public:
    InputLoader(const string & fileName)
    {
        m_file.open(fileName);
        if(m_file.is_open())
        {
        }
        else
        {
            cout << "Error open file: " << fileName << endl;
        }

    }

    ~InputLoader()
    {
        if(m_file.is_open())
        {
            m_file.close();
        }
    }

    string GetLine()
    {
        string line;
        getline(m_file, line);
        return line;
    }

    template<typename T>
    vector<T> GetLineAsVector(char seperator = ' ')
    {
        string line;
        getline(m_file, line);

        vector<string> strVec;
        boost::algorithm::split(strVec, line, boost::is_any_of(seperator), boost::token_compress_on);

        vector<T> v;
        std::transform(strVec.begin(), strVec.end(), std::back_inserter(v), [](const string& s) {
            T value;
            stringstream ss;
            ss << s;
            ss>> value;
            return value;
        });
        return v;
    }

private:
    ifstream m_file;
};