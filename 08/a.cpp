#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

// Example usage
int main()
{
    string map;
    readFileLines("input.txt", map);

    string currentPosition = "AAA";
    int charIndex = 0;
    int totalSteps = 0;
    while (currentPosition != "ZZZ")
    {
        currentPosition = NewPosition(currentPosition, map[charIndex]);
        charIndex++;
        totalSteps++;
        if (charIndex >= map.size())
        {
            charIndex = 0;
        }
    }
    cout << totalSteps;
    return 0;
}