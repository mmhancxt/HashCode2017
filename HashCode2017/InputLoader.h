#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
//#include <boost/algorithm/string.hpp>

using namespace std;

class InputLoader
{
public:
	InputLoader()
	{
		Init();
	}

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
		Init();

    }

    ~InputLoader()
    {
        if(m_file.is_open())
        {
            m_file.close();
        }
    }

    //string GetLine()
    //{
    //    string line;
    //    getline(m_file, line);
    //    return line;
    //}

    //template<typename T>
    //vector<T> GetLineAsVector(char seperator = ' ')
    //{
    //    string line;
    //    getline(m_file, line);

    //    vector<string> strVec;
    //    boost::algorithm::split(strVec, line, boost::is_any_of(seperator), boost::token_compress_on);

    //    vector<T> v;
    //    std::transform(strVec.begin(), strVec.end(), std::back_inserter(v), [](const string& s) {
    //        T value;
    //        stringstream ss;
    //        ss << s;
    //        ss>> value;
    //        return value;
    //    });
    //    return v;
    //}
private:
	void Init()
	{
		const_row = 7;
		const_column = 6;
		const_min_ingredient = 1;
		const_max_cells_in_slice = 5;
		pizza = { 
		{ 1,0,0,0,1,1,1 },
		{ 0,0,0,0,1,0,0	},
		{ 1,1,0,1,1,0,1 },
		{ 1,0,0,1,0,0,0 },
		{ 1,1,1,1,1,1,0 },
		{ 1,1,1,1,1,1,0 }
		};
	}

private:
    ifstream m_file;

public:
	int const_row;
	int const_column;
	int const_min_ingredient;
	int const_max_cells_in_slice;
	vector<vector<int>> pizza;
    vector<vector<boolean>> isTaken;
};