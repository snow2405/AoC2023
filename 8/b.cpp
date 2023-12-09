#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <cmath>

using namespace std;

vector<string> locations;
vector<string> left_targets;
vector<string> right_targets;

void readFileLines(string fileName, string &map)
{
    ifstream file(fileName);
    string line;
    bool isFirstLine = true;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (isFirstLine)
            {
                map = line;
                isFirstLine = false;
                continue;
            }

            istringstream iss(line);
            string location, equals, leftEntry, rightEntry;
            if (iss >> location >> equals >> leftEntry >> rightEntry)
            {
                locations.push_back(location);
                left_targets.push_back(leftEntry.substr(1, leftEntry.size() - 2));    // Remove parentheses
                right_targets.push_back(rightEntry.substr(0, rightEntry.size() - 1)); // Remove parentheses
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

string NewPosition(string pos, char dir)
{
    for (int i = 0; i < locations.size(); i++)
    {
        if (locations[i] == pos)
        {
            if (dir == 'R')
            {
                return right_targets[i];
            }
            else
            {
                return left_targets[i];
            }
        }
    }
    return "ERROR";
}

long long LowestCommonMultiple(long long a, long long b){
    return abs(a*b) / gcd(a, b);
}

// Example usage
int main()
{
    string map;
    readFileLines("input.txt", map);

    long long total = 1;

    for (int i = 0; i < locations.size(); i++)
    {
        if (locations[i][2] == 'A')
        {
            int charIndex = 0;
            int steps = 0;
            string currentPosition = locations[i];
            while (currentPosition[2] != 'Z')
            {
                currentPosition = NewPosition(currentPosition, map[charIndex]);
                charIndex++;
                steps++;
                if (charIndex >= map.size())
                {
                    charIndex = 0;
                }
            }
            total = LowestCommonMultiple(total, steps);
        }
    }
    cout << total;

    return 0;
}