#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> readFile(string fileName)
{
    vector<vector<char>> in_stream_array;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<char> currentLine;
            for (char c : line)
            {
                currentLine.push_back(c);
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

    vector<vector<char>> input = readFile("input.txt");
    vector<vector<char>> transposed_input;

    for (int i = 0; i < input[0].size(); i++)
    {
        vector<char> current_column;
        for (int j = 0; j < input.size(); j++)
        {
            current_column.push_back(input[j][i]);
        }
        transposed_input.push_back(current_column);
    }
    for (int brute_force = 0; brute_force < transposed_input[0].size(); brute_force++)
    {
        for (int i = 0; i < transposed_input.size(); i++)
        {
            for (int j = 1; j < transposed_input[i].size(); j++)
            {
                if (transposed_input[i][j - 1] == '.' && transposed_input[i][j] == 'O')
                {
                    transposed_input[i][j - 1] = 'O';
                    transposed_input[i][j] = '.';
                }
            }
        }
    }
    int total = 0; 
    for (int i = 0; i < transposed_input[0].size(); i++)
    {
        for (int j = 0; j < transposed_input.size(); j++)
        {
            if(transposed_input[i][j] == 'O'){
                total += (transposed_input.size() - j);
            }
        }
    }
    cout << total;
    return 0;
}