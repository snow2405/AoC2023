#include <iostream>
#include <fstream>
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
        cout << "Unable to open file";
    }

    return lines;
}

int main()
{

    vector<string> lines = readFileLines("input.txt");

    vector<bool> appendHorizotal(lines.size(), true);
    vector<bool> appendVertical(lines[0].size(), true);

    for (int i = 0; i < lines.size(); i++)
    {
        bool line_empty = true;
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '#')
            {
                appendHorizotal[i] = false;
                appendVertical[j] = false;
            }
        }
    }

    vector<long long> horizontal_stretch_cords;
    vector<long long> vertical_stretch_cords;
    for (int i = 0; i < appendHorizotal.size(); i++)
    {
        if (appendHorizotal[i])
        {
            if (find(horizontal_stretch_cords.begin(), horizontal_stretch_cords.end(), i) == horizontal_stretch_cords.end())
            {
                horizontal_stretch_cords.push_back(i);
            }
        }
    }
    for (int j = 0; j < appendVertical.size(); j++)
    {
        if (appendVertical[j])
        {
            if (find(vertical_stretch_cords.begin(), vertical_stretch_cords.end(), j) == vertical_stretch_cords.end())
            {
                vertical_stretch_cords.push_back(j);
            }
        }
    }

    vector<vector<long long>> coordinates;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '#')
            {
                coordinates.push_back({i, j});
            }
        }
    }
    long long total = 0;
    for (int i = 0; i < coordinates.size(); i++)
    {
        for (int j = i + 1; j < coordinates.size(); j++)
        {
            long long x_dist = abs(coordinates[j][0] - coordinates[i][0]);
            long long x_min = min(coordinates[j][0], coordinates[i][0]);
            long long x_max = max(coordinates[j][0], coordinates[i][0]);
            for (long long stretch_point : horizontal_stretch_cords)
            {
                if (stretch_point > x_min && stretch_point < x_max)
                {
                    x_dist += 999999;
                }
            }

            long long y_dist = abs(coordinates[j][1] - coordinates[i][1]);
            long long y_min = min(coordinates[j][1], coordinates[i][1]);
            long long y_max = max(coordinates[j][1], coordinates[i][1]);
            for (long long stretch_point : vertical_stretch_cords)
            {
                if (stretch_point > y_min && stretch_point < y_max)
                {
                    y_dist += 999999;
                }
            }

            long long m_dist = x_dist + y_dist;
            total += m_dist;
        }
    }
    cout << total << endl;

    return 0;
}