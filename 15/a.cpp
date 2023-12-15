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
        cout << "Unable to open file";
    }

    return in_stream_array;
}

int main()
{
    vector<string> input = readFile("input.txt");

    int multiplier = 17;
    int divider = 256;

    int total = 0;

    for (string s : input)
    {
        int current_value = 0;
        for (char c : s)
        {
            current_value += int(c);
            current_value *= multiplier;
            current_value %= divider;
        }
        total += current_value;
    }
    cout << total << endl;

    return 0;
}