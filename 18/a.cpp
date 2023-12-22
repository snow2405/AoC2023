#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void parseInputFile(const string &filename, vector<char> &directions, vector<int> &numbers, vector<string> &colors)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line.size() > 0)
        {
            // Extract the first character
            char direction = line[0];
            directions.push_back(direction);

            // Extract the number
            stringstream ss(line.substr(2));
            int number;
            ss >> number;
            numbers.push_back(number);

            // Extract the hex code
            size_t pos = line.find('#');
            string color = line.substr(pos + 1, 6);
            colors.push_back(color);
        }
    }
}

int main()
{
    vector<char> directions;
    vector<int> numbers;
    vector<string> colors;

    parseInputFile("input.txt", directions, numbers, colors);

    // Create a 2D vector to represent the map with the digged holes and an empty starting point.
    vector<vector<bool>> digged_map(500, vector<bool>(1000, false));

    int current_x = 500;
    int current_y = 200;
    for (int i = 0; i < directions.size(); i++)
    {
        int new_x = current_x;
        int new_y = current_y;

        if (directions[i] == 'R')
        {
            new_x += numbers[i];
            if (digged_map[0].size()-1 < new_x)
            {
                int columns_to_add = new_x - (digged_map[0].size() - 1);
                for (int k = 0; k < columns_to_add; ++k)
                {
                    for (int j = 0; j < digged_map.size(); ++j)
                    {
                        digged_map[j].push_back(false);
                    }
                }
            }
            for (int k = 0; k < numbers[i]; ++k)
            {
                digged_map[new_y][current_x + k] = true;
            }
            current_x = new_x;
        }
        else if (directions[i] == 'L')
        {
            new_x -= numbers[i];
            if (new_x < 0)
            {
                int columns_to_add = 0 - new_x;
                for (int k = 0; k < columns_to_add; ++k)
                {
                    for (int j = 0; j < digged_map.size(); ++j)
                    {
                        digged_map[j].insert(digged_map[0].begin(), false);
                    }
                }
                current_x += columns_to_add;
                new_x = 0;
            }
            for (int k = 0; k < (current_x - new_x); ++k)
            {
                digged_map[new_y][current_x - k] = true;
            }
            current_x = new_x;
        }
        if (directions[i] == 'U')
        {
            new_y -= numbers[i];
            if (new_y < 0)
            {
                int rows_to_add = 0 - new_y;
                for (int k = 0; k < rows_to_add; ++k)
                {
                    // Add a new row at the beginning filled with 'false' values.
                    digged_map.insert(digged_map.begin(), (vector<bool>(digged_map[0].size(), false)));
                }
                current_y += rows_to_add;
                new_y = 0;
            }
            for (int k = 0; k < (current_y - new_y); ++k)
            {
                digged_map[current_y - k][new_x] = true;
            }
            current_y = new_y;
            
        }
        else if (directions[i] == 'D')
        {
            new_y += numbers[i];
            if (digged_map.size()-1 < new_y)
            {
                int rows_to_add = new_y - (digged_map.size() - 1);
                for (int k = 0; k < rows_to_add; ++k)
                {
                    // Add a new row filled with 'false' values.
                    digged_map.push_back(vector<bool>(digged_map[0].size(), false));
                }
            }
            for (int k = 0; k < numbers[i]; ++k)
            {
                digged_map[current_y + k][new_x] = true;
            }
            current_y = new_y;
        }
    }

    vector<vector<bool>> digged_map_copy = digged_map;

    for (int i = 0; i < digged_map.size(); ++i)
    {
        bool isInside = false;
        for (int j = 0; j < digged_map[i].size(); ++j)
        {
            if (digged_map[i][j] == true && digged_map[i+1][j] == true && digged_map[i-1][j] == true) 
            {
                isInside = !isInside;
            }
            if(digged_map[i][j] == true && digged_map[i][j+1] == true && digged_map[i-1][j] == true)
            {
                isInside = !isInside;
            }
            else if (digged_map[i][j] == true && digged_map[i][j-1] == true && digged_map[i-1][j] == true)
            {
                isInside = !isInside;
            }
            if (isInside)
            {
                digged_map_copy[i][j] = true;
            }
        }
    }

    int total = 0;
    for (int i = 0; i < digged_map_copy.size(); ++i)
    {
        for (int j = 0; j < digged_map_copy[i].size(); ++j)
        {
            if (digged_map_copy[i][j] == true)
            {
                total++;
            }
        }
    }
    cout << "Total: " << total << endl;
    return 0;
}
