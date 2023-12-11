#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    vector<bool> appendVertical(lines[0].size(), true);

    for (int i = 0; i < lines.size(); i++)
    {
        bool line_empty = true;
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '#')
            {
                line_empty = false;
                appendVertical[j] = false;
            }
        }
        if (line_empty)
        {
            string s(lines[i].size(), '.');
            lines.insert(lines.begin() + i, s);
            i++;
        }
    }
    for (int i = 0; i < appendVertical.size(); i++)
    {
        if (appendVertical[i])
        {
            appendVertical.insert(appendVertical.begin() + i, false);
            i++;
        }
    }

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (appendVertical[j])
            {
                lines[i].insert(j, 1, '.');
                j++;
            }
        }
    }

    vector<vector<int>> coordinates;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '#')
            {
                coordinates.push_back({i,j});
            }
        }
    }
    int total = 0;
    for(int i = 0; i < coordinates.size(); i++){
        for(int j = i+1; j < coordinates.size(); j++){
            int x_dist = abs(coordinates[j][0] - coordinates[i][0]);
            int y_dist = abs(coordinates[j][1] - coordinates[i][1]);
            int m_dist = x_dist + y_dist; //manhattan distance
            total += m_dist;
        }
    }
    cout << total << endl;

    return 0;
}