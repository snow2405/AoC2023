#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> readFileLines(string fileName)
{
    vector<string> lines;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    return lines;
}

vector<vector<vector<long long>>> parseData(const vector<string> &lines)
{
    vector<vector<vector<long long>>> result;
    vector<vector<long long>> currentCategory;
    vector<long long> seeds;

    for (const auto &line : lines)
    {
        if (line.find("seeds:") != string::npos)
        {
            istringstream lineStream(line.substr(line.find(':') + 1));
            long long seed;
            while (lineStream >> seed)
            {
                seeds.push_back(seed);
            }
            result.push_back({seeds}); // Add seeds as the first category
        }
        else if (line.find("map:") != string::npos)
        {
            if (!currentCategory.empty())
            {
                result.push_back(currentCategory);
                currentCategory.clear();
            }
        }
        else
        {
            istringstream lineStream(line);
            vector<long long> row;
            long long number;
            while (lineStream >> number)
            {
                row.push_back(number);
            }
            if (!row.empty())
            {
                currentCategory.push_back(row);
            }
        }
    }

    if (!currentCategory.empty())
    {
        result.push_back(currentCategory);
    }

    return result;
}

int main()
{

    vector<string> lines = readFileLines("input.txt");

    vector<vector<vector<long long>>> parsedData = parseData(lines);

    for (int i = 0; i < parsedData.size(); i++)
    {
        for (int j = 0; j < parsedData[i].size(); j++)
        {
            for (int k = 0; k < parsedData[i][j].size(); k++)
            {
                std::cout << "<<" << i << "," << j << "," << k << ":" << parsedData[i][j][k] << ">>";
            }
            std::cout << endl;
        }
        std::cout << endl;
    }
    long long minimum = parsedData[0][0][0]*100;
    long long minimum_location;
    for(int x = 0; x < parsedData[0][0].size(); x+=2){
        long long limit = parsedData[0][0][x] + parsedData[0][0][x+1];
        for (long long i = parsedData[0][0][x]; i < limit; i++)
        {
            long long seed = i;
            for (int j = 1; j < parsedData.size(); j++)
            {
                for (int k = 0; k < parsedData[j].size(); k++)
                {
                    if (parsedData[j][k][1] <= seed && parsedData[j][k][1] + parsedData[j][k][2] > seed)
                    {
                        seed = seed + parsedData[j][k][0] - parsedData[j][k][1];
                        break;
                    }
                }
            }
            //std::cout << "Final Value of seed " << i << " is: " << seed << endl;
            if(seed < minimum)
            {
                minimum = seed;
                minimum_location = i;
            }
        }
        std::cout << "progress: " << x << " out of "<< parsedData[0][0].size() << endl;
    }
    cout << "Minimum value is: " << minimum << " with seed " << minimum_location << endl;


    return 0;
}

