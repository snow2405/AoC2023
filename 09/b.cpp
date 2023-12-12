#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<int>> readFileLines(string fileName)
{
    vector<vector<int>> lines;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream iss(line);
            vector<int> lineData;
            int number;
            while (iss >> number)
            {
                lineData.push_back(number);
            }
            lines.push_back(lineData);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    return lines;
}

vector<int> find_differences(vector<int> input)
{
    vector<int> output;
    for (int i = 0; i < input.size() - 1; i++)
    {
        output.push_back(input[i + 1] - input[i]);
    }
    return output;
}

int main()
{
    vector<vector<int>> lines = readFileLines("input.txt");

    int total = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        vector<vector<int>> sub_lines;
        sub_lines.push_back(lines[i]);
        while (true)
        {
            int check_sum = 0;
            for (int j = 0; j < sub_lines[sub_lines.size() - 1].size(); j++)
            {
                check_sum += sub_lines[sub_lines.size() - 1][j];
            }
            if (check_sum == 0)
            {
                break;
            }
            sub_lines.push_back(find_differences(sub_lines[sub_lines.size() - 1]));
        }
        int current_sum = 0;
        for (int j = sub_lines.size() - 1; j >= 0; j--)
        {
            current_sum = sub_lines[j][0] - current_sum;
        }
        
        total += current_sum;
    }

    cout << total;

    return 0;
}
