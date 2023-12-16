//FOR THIS TO WORK STACK SIZE NEEDS TO BE INCREASE TO A HIGHER AMOUNT THAN DEFAULT (I USED 16 MB) TO HANDLE THE RECURSION

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

vector<vector<char>> input_grid;
vector<vector<char>> energized_grid;

vector<string> tail;

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

int CheckTile(int row_pos, int column_pos)
{
    if (input_grid[row_pos][column_pos] == '.')
    {
        return 0;
    }
    else if (input_grid[row_pos][column_pos] == '|')
    {
        return 1;
    }
    else if (input_grid[row_pos][column_pos] == '-')
    {
        return 2;
    }
    else if (input_grid[row_pos][column_pos] == '/')
    {
        return 3;
    }
    else if (input_grid[row_pos][column_pos] == '\\')
    {
        return 4;
    }
    else
    {
        return -1;
    }
}

void NextTile(int row_pos, int column_pos, string direction)
{
    if (row_pos < 0 || column_pos < 0 || row_pos >= input_grid.size() || column_pos >= input_grid[0].size())
    {
        return;
    }
    else
    {
        energized_grid[row_pos][column_pos] = '#';
    }

    for (int i = 0; i < tail.size(); i++)
    {
        if (tail[i] == (to_string(row_pos) + "," + to_string(column_pos) + "," + direction))
        {
            return;
        }
    }
    tail.push_back(to_string(row_pos) + "," + to_string(column_pos) + "," + direction);

    if (direction == "^")
    {
        switch (CheckTile(row_pos, column_pos))
        {
        case 0:
            NextTile(row_pos - 1, column_pos, "^");
            break;
        case 1:
            NextTile(row_pos - 1, column_pos, "^");
            break;
        case 2:
            NextTile(row_pos, column_pos - 1, "<");
            NextTile(row_pos, column_pos + 1, ">");
            break;
        case 3:
            NextTile(row_pos, column_pos + 1, ">");
            break;
        case 4:
            NextTile(row_pos, column_pos - 1, "<");
            break;
        default:
            break;
        }
    }
    else if (direction == "v")
    {
        switch (CheckTile(row_pos, column_pos))
        {
        case 0:
            NextTile(row_pos + 1, column_pos, "v");
            break;
        case 1:
            NextTile(row_pos + 1, column_pos, "v");
            break;
        case 2:
            NextTile(row_pos, column_pos - 1, "<");
            NextTile(row_pos, column_pos + 1, ">");
            break;
        case 3:
            NextTile(row_pos, column_pos - 1, "<");
            break;
        case 4:
            NextTile(row_pos, column_pos + 1, ">");
            break;
        default:
            break;
        }
    }
    else if (direction == "<")
    {
        switch (CheckTile(row_pos, column_pos))
        {
        case 0:
            NextTile(row_pos, column_pos - 1, "<");
            break;
        case 1:
            NextTile(row_pos + 1, column_pos, "v");
            NextTile(row_pos - 1, column_pos, "^");
            break;
        case 2:
            NextTile(row_pos, column_pos - 1, "<");
            break;
        case 3:
            NextTile(row_pos + 1, column_pos, "v");
            break;
        case 4:
            NextTile(row_pos - 1, column_pos, "^");
            break;
        default:
            break;
        }
    }
    else if (direction == ">")
    {
        switch (CheckTile(row_pos, column_pos))
        {
        case 0:
            NextTile(row_pos, column_pos + 1, ">");
            break;
        case 1:
            NextTile(row_pos + 1, column_pos, "v");
            NextTile(row_pos - 1, column_pos, "^");
            break;
        case 2:
            NextTile(row_pos, column_pos + 1, ">");
            break;
        case 3:
            NextTile(row_pos - 1, column_pos, "^");
            break;
        case 4:
            NextTile(row_pos + 1, column_pos, "v");
            break;
        default:
            break;
        }
    }

    return;
}

int main()
{
    input_grid = readFile("input.txt");
    energized_grid = input_grid;

    NextTile(0, 0, ">");

    int total = 0;
    for (int i = 0; i < input_grid.size(); i++)
    {
        for (int j = 0; j < input_grid[i].size(); j++)
        {
            if (energized_grid[i][j] == '#')
                total++;
        }
    }
    cout << total;

    return 0;
}