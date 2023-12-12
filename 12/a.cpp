#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

void readFileLines(string fileName, vector<string> &stringParts, vector<vector<int>> &integerParts)
{
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string stringPart;
            string integerPart;

            getline(ss, stringPart, ' ');
            getline(ss, integerPart);

            stringParts.push_back(stringPart);

            vector<int> currentIntegers;
            stringstream ssInt(integerPart);
            string temp;
            while (getline(ssInt, temp, ','))
            {
                currentIntegers.push_back(stoi(temp));
            }

            integerParts.push_back(currentIntegers);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}


vector<int> countHashes(const string& input) {
    vector<int> counts;
    int count = 0;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '#') {
            count++;
        } else if (count > 0) {
            counts.push_back(count); 
            count = 0;  
        }
    }

    if (count > 0) {
        counts.push_back(count);
    }

    return counts;
}

int main()
{

    vector<string> machine_map;
    vector<vector<int>> check_locations;

    readFileLines("input.txt", machine_map, check_locations);

    int total_combinations = 0;

    cout << "Brute force is working, this may take a minute..." << endl;

    for (int i = 0; i < machine_map.size(); i++)
    {
        int numQuestionMarks = 0;

        for (int j = 0; j < machine_map[i].length(); j++)
        {
            if (machine_map[i][j] == '?')
            {
                numQuestionMarks++;
            }
        }

        int totalCombinations = (int)pow(2, numQuestionMarks);

        for (int j = 0; j < totalCombinations; j++)
        {
            string current = machine_map[i];
            int temp = j;

            // Replace '?' with '.' or '#' based on the bits of i
            for (int k = 0; k < numQuestionMarks; k++)
            {
                size_t pos = current.find('?');
                if (pos != string::npos)
                {
                    if (temp % 2 == 0)
                    {
                        current[pos] = '.';
                    }
                    else
                    {
                        current[pos] = '#';
                    }
                }
                temp /= 2;
            }
            if(countHashes(current) == check_locations[i]){
                total_combinations++;
            }
        }
    }
    cout << total_combinations;
    return 0;
}