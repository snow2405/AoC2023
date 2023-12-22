#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void parseInputFile(const string &filename, vector<char> &directions, vector<long long> &numbers, vector<string> &colors)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line.size() > 0)
        {
            // Extract the hex code
            size_t pos = line.find('#');
            string hexCode = line.substr(pos + 1, 6);
            colors.push_back(hexCode);

            // Extract the distance (first 5 characters of the hex code)
            string distHex = hexCode.substr(0, 5);
            long long number = stoi(distHex, nullptr, 16); // Convert hex string to int
            numbers.push_back(number);

            // Extract the direction (last character of the hex code)
            char directionChar = hexCode[5];
            char direction;
            switch(directionChar)
            {
                case '0':
                    direction = 'R';
                    break;
                case '1':
                    direction = 'D';
                    break;
                case '2':
                    direction = 'L';
                    break;
                case '3':
                    direction = 'U';
                    break;
                default:
                    direction = ' '; // Invalid direction
            }
            directions.push_back(direction);
        }
    }
}

int main()
{
    vector<char> directions;
    vector<long long> numbers;
    vector<string> colors;

    parseInputFile("input.txt", directions, numbers, colors);

    // Create a 2D vector to represent the map with the digged holes and an empty starting point.
    vector<vector<bool>> digged_map(1000000, vector<bool>(1000000, false));

    // Output for testing
    cout << "Directions: ";
    for (char dir : directions)
        cout << dir << " ";
    cout << "\nNumbers: ";
    for (long long num : numbers)
        cout << num << " ";
    cout << "\nColors: ";
    for (const string &color : colors)
        cout << color << " ";
    cout << endl;

    long long current_x = 500;
    long long current_y = 200;
    for (long long i = 0; i < directions.size(); i++)
    {
        long long new_x = current_x;
        long long new_y = current_y;
         cout << "debug; " << directions[i] << " " << numbers[i]<< ";" << current_x << " " << current_y << ";"<< digged_map.size() << " " << digged_map[0].size() << endl;

        if (directions[i] == 'R')
        {
            new_x += numbers[i];
            if (digged_map[0].size()-1 < new_x)
            {
                long long columns_to_add = new_x - (digged_map[0].size() - 1);
                for (long long k = 0; k < columns_to_add; ++k)
                {
                    for (long long j = 0; j < digged_map.size(); ++j)
                    {
                        digged_map[j].push_back(false);
                    }
                }
            }
            for (long long k = 0; k < numbers[i]; ++k)
            {
                digged_map[new_y][current_x + k] = true;
            }
            current_x = new_x;
        }
        else if (directions[i] == 'L')
        {
            new_x -= numbers[i];
            cout << "we are here with new_x: " << new_x << endl;
            if (new_x < 0)
            {
                long long columns_to_add = 0 - new_x;
                for (long long k = 0; k < columns_to_add; ++k)
                {
                    for (long long j = 0; j < digged_map.size(); ++j)
                    {
                        digged_map[j].insert(digged_map[0].begin(), false);
                    }
                }
                current_x += columns_to_add;
                new_x = 0;
            }
            for (long long k = 0; k < (current_x - new_x); ++k)
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
                long long rows_to_add = 0 - new_y;
                for (long long k = 0; k < rows_to_add; ++k)
                {
                    // Add a new row at the beginning filled with 'false' values.
                    digged_map.insert(digged_map.begin(), (vector<bool>(digged_map[0].size(), false)));
                }
                current_y += rows_to_add;
                new_y = 0;
            }
            for (long long k = 0; k < (current_y - new_y); ++k)
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
                long long rows_to_add = new_y - (digged_map.size() - 1);
                for (long long k = 0; k < rows_to_add; ++k)
                {
                    // Add a new row filled with 'false' values.
                    digged_map.push_back(vector<bool>(digged_map[0].size(), false));
                }
            }
            for (long long k = 0; k < numbers[i]; ++k)
            {
                digged_map[current_y + k][new_x] = true;
            }
            current_y = new_y;
        }
    }

   /* for (int i = 0; i < digged_map.size(); ++i)
    {
        for (int j = 0; j < digged_map[i].size(); ++j)
        {
            if(digged_map[i][j] == true)
                cout << "X";
            else
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;*/

    vector<vector<bool>> digged_map_copy = digged_map;

    for (long long i = 0; i < digged_map.size(); ++i)
    {
        bool isInside = false;
        for (long long j = 0; j < digged_map[i].size(); ++j)
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

    /*for (int i = 0; i < digged_map.size(); ++i)
    {
        for (int j = 0; j < digged_map[i].size(); ++j)
        {
            if(digged_map_copy[i][j] == true)
                cout << "X";
            else
                cout << " ";
        }
        cout << endl;
    }*/

    long long total = 0;
    for (long long i = 0; i < digged_map_copy.size(); ++i)
    {
        for (long long j = 0; j < digged_map_copy[i].size(); ++j)
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
