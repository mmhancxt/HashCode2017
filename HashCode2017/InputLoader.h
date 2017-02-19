#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <boost/algorithm/string.hpp>

using namespace std;

class InputLoader
{
public:
    // Load input from file
    InputLoader(const string & fileName)
    {
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
        const_row = 7;
        const_column = 6;
        const_min_ingredient = 1;
        const_max_cells_in_slice = 5;
        pizza = {
            { 1, 0, 0, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 1, 0, 0 },
            { 1, 1, 0, 1, 1, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 0 },
            { 1, 1, 1, 1, 1, 1, 0 }
        };
    }

    void InitFromFile()
    {
        vector<int> consts = GetLineAsVector<int>();
        const_row = consts[0];
        const_column = consts[1];
        const_min_ingredient = consts[2];
        const_max_cells_in_slice = consts[3];

        for (int i = 0; i < const_row; i++)
        {
            string line = GetLineAsString();
            vector<int> v;
            for (int i = 0; i < line.size(); ++i)
            {
                int ingredient = (line[i] == 'T' ? 1 : 0);
                v.push_back(ingredient);
            }
            pizza.push_back(v);
            isTaken.push_back(vector<int>(line.size(), false));
        }
    }

private:
    ifstream m_file;

public:
    int const_row;
    int const_column;
    int const_min_ingredient;
    int const_max_cells_in_slice;
    vector<vector<int>> pizza;
    vector<vector<int>> isTaken;
};