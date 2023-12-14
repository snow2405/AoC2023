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

    vector<vector<char>> saved_grid;

    int sample_loop_size = 1000;
    int loop_size = 0;
    int offset = 0;
    int next_closest_output = -1;

    cout << "starting brute forcing, this may take a minute... " << endl;

    for (int cyceles = 0; cyceles < 2 * sample_loop_size; cyceles++)
    {
        // North
        for (int brute_force = 0; brute_force < input[0].size(); brute_force++)
        {
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[i].size(); j++)
                {
                    if (i > 0)
                    {
                        if (input[i - 1][j] == '.' && input[i][j] == 'O')
                        {
                            input[i - 1][j] = 'O';
                            input[i][j] = '.';
                        }
                    }
                }
            }
        }
        // WEST
        for (int brute_force = 0; brute_force < input[0].size(); brute_force++)
        {
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 1; j < input[i].size(); j++)
                {
                    if (input[i][j - 1] == '.' && input[i][j] == 'O')
                    {
                        input[i][j - 1] = 'O';
                        input[i][j] = '.';
                    }
                }
            }
        }
        // South
        for (int brute_force = 0; brute_force < input[0].size(); brute_force++)
        {
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[i].size(); j++)
                {
                    if (i < input.size() - 1)
                    {
                        if (input[i + 1][j] == '.' && input[i][j] == 'O')
                        {
                            input[i + 1][j] = 'O';
                            input[i][j] = '.';
                        }
                    }
                }
            }
        }
        // EAST
        for (int brute_force = 0; brute_force < input[0].size(); brute_force++)
        {
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[i].size() - 1; j++)
                {
                    if (input[i][j + 1] == '.' && input[i][j] == 'O')
                    {
                        input[i][j + 1] = 'O';
                        input[i][j] = '.';
                    }
                }
            }
        }
        if (cyceles == next_closest_output)
        {
            int total = 0;
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[0].size(); j++)
                {
                    if (input[i][j] == 'O')
                    {
                        total += (input.size() - i);
                    }
                }
            }

            cout << total << endl;
            break;
        }
        if (cyceles == sample_loop_size)
        {
            saved_grid = input;
        }
        if (cyceles > sample_loop_size && saved_grid == input)
        {
            loop_size = cyceles - sample_loop_size;
            offset = (1000000000 - sample_loop_size) % loop_size;
            next_closest_output = sample_loop_size + offset + (2 * loop_size) -1; //-1 as index is shifted
        }
    }

    return 0;
}