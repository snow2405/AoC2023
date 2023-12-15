#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readFile(string fileName)
{
    vector<string> in_stream_array;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            string currentLine;
            for (char c : line)
            {
                if (c == ',')
                {
                    in_stream_array.push_back(currentLine);
                    currentLine.clear();
                }
                else
                {
                    currentLine += c;
                }
            }
            in_stream_array.push_back(currentLine);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    return in_stream_array;
}

int HASH_algo(char input, int _current_value)
{
    _current_value += int(input);
    _current_value *= 17;
    _current_value %= 256;
    return _current_value;
}
int main()
{
    vector<string> input = readFile("input.txt");

    vector<vector<string>> lens_labels(256);
    vector<vector<int>> lens_values(256);

    for (string s : input)
    {
        int current_value = 0;
        string current_label = "";
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '=')
            {
                bool foundLabel = false;
                for (int j = 0; j < lens_labels[current_value].size(); j++)
                {
                    if (lens_labels[current_value][j] == current_label)
                    {
                        foundLabel = true;
                        lens_values[current_value][j] = ((s[i + 1]) - '0');
                        break;
                    }
                }
                if (!foundLabel)
                {
                    lens_labels[current_value].push_back(current_label);
                    lens_values[current_value].push_back((s[i + 1]) - '0');
                }
                break;
            }
            else if (s[i] == '-')
            {
                for (int j = 0; j < lens_labels[current_value].size(); j++)
                {
                    if (lens_labels[current_value][j] == current_label)
                    {
                        lens_labels[current_value].erase(lens_labels[current_value].begin() + j);
                        lens_values[current_value].erase(lens_values[current_value].begin() + j);
                        break;
                    }
                }
                break;
            }
            else
            {
                current_value = HASH_algo(s[i], current_value);
                current_label += s[i];
            }
        }
    }

    int total = 0;
    for (int i = 0; i < lens_values.size(); i++){
        for(int j = 0; j < lens_values[i].size(); j++){
            total += (i+1) * lens_values[i][j]*(j+1);
        }
    }
    std::cout << total;


    return 0;
}