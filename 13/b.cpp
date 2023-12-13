#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<vector<char>>> readFileGroups(string fileName)
{
    vector<vector<vector<char>>> groups;
    vector<vector<char>> currentGroup;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty())
            {
                if (!currentGroup.empty())
                {
                    groups.push_back(currentGroup);
                    currentGroup.clear();
                }
            }
            else
            {
                vector<char> currentLine;
                for (char c : line)
                {
                    currentLine.push_back(c);
                }
                currentGroup.push_back(currentLine);
            }
        }
        if (!currentGroup.empty())
        {
            groups.push_back(currentGroup);
        }

        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    return groups;
}

int ReturnVerticalMirror(vector<vector<char>> current_map)
{
    for (int mirror_index = 1; mirror_index < current_map[0].size(); mirror_index++)
    {
        bool isMirrorPosition = true;
        for (int j = 0; j < current_map.size(); j++)
        {
            int side_lengths = mirror_index;
            string left_side;
            string right_side;
            if (side_lengths > (current_map[j].size() - mirror_index))
            {
                side_lengths = current_map[j].size() - mirror_index;
                left_side = string(current_map[j].begin() + (mirror_index - side_lengths), current_map[j].begin() + mirror_index);
                right_side = string(current_map[j].begin() + mirror_index, current_map[j].begin() + (mirror_index + side_lengths));
            }
            else
            {
                left_side = string(current_map[j].begin() + (mirror_index - side_lengths), current_map[j].begin() + side_lengths);
                right_side = string(current_map[j].begin() + mirror_index, current_map[j].begin() + (mirror_index + side_lengths));
            }

            reverse(right_side.begin(), right_side.end());
            if (left_side != right_side)
            {
                isMirrorPosition = false;
                break;
            }
        }
        if (isMirrorPosition)
        {
            return mirror_index;
            break;
        }
    }

    return 0;
}

int ReturnNewUniqueVerticalMirror(vector<vector<char>> current_map, int dissalowed)
{
    for (int mirror_index = 1; mirror_index < current_map[0].size(); mirror_index++)
    {
        bool isMirrorPosition = true;
        for (int j = 0; j < current_map.size(); j++)
        {
            int side_lengths = mirror_index;
            string left_side;
            string right_side;
            if (side_lengths > (current_map[j].size() - mirror_index))
            {
                side_lengths = current_map[j].size() - mirror_index;
                left_side = string(current_map[j].begin() + (mirror_index - side_lengths), current_map[j].begin() + mirror_index);
                right_side = string(current_map[j].begin() + mirror_index, current_map[j].begin() + (mirror_index + side_lengths));
            }
            else
            {

                left_side = string(current_map[j].begin() + (mirror_index - side_lengths), current_map[j].begin() + side_lengths);
                right_side = string(current_map[j].begin() + mirror_index, current_map[j].begin() + (mirror_index + side_lengths));
            }

            reverse(right_side.begin(), right_side.end());
            if (left_side != right_side)
            {
                isMirrorPosition = false;
                break;
            }
        }
        if (isMirrorPosition && mirror_index != dissalowed)
        {
            return mirror_index;
            break;
        }
    }

    return 0;
}

int ReturnHorizontalMirror(vector<vector<char>> current_map)
{
    for (int mirror_index = 1; mirror_index < current_map.size(); mirror_index++)
    {
        bool isMirrorPosition = true;
        for (int j = 0; j < current_map[0].size(); j++)
        {
            int side_lengths = mirror_index;
            if (mirror_index > (current_map.size() - mirror_index))
            {
                side_lengths = current_map.size() - mirror_index;
            }

            string top_side;
            string bottom_side;

            for (int k = mirror_index - side_lengths; k < mirror_index; k++)
            {
                top_side += current_map[k][j];
            }
            for (int k = mirror_index; k < mirror_index + side_lengths; k++)
            {
                bottom_side += current_map[k][j];
            }
            reverse(bottom_side.begin(), bottom_side.end());
            if (top_side != bottom_side)
            {
                isMirrorPosition = false;
                break;
            }
        }
        if (isMirrorPosition)
        {
            return mirror_index;
            break;
        }
    }

    return 0;
}

int ReturnNewUniqueHorizontalMirror(vector<vector<char>> current_map, int dissalowed)
{
    for (int mirror_index = 1; mirror_index < current_map.size(); mirror_index++)
    {
        bool isMirrorPosition = true;
        for (int j = 0; j < current_map[0].size(); j++)
        {
            int side_lengths = mirror_index;
            if (mirror_index > (current_map.size() - mirror_index))
            {
                side_lengths = current_map.size() - mirror_index;
            }
            string top_side;
            string bottom_side;

            for (int k = mirror_index - side_lengths; k < mirror_index; k++)
            {
                top_side += current_map[k][j];
            }
            for (int k = mirror_index; k < mirror_index + side_lengths; k++)
            {
                bottom_side += current_map[k][j];
            }
            reverse(bottom_side.begin(), bottom_side.end());
            if (top_side != bottom_side)
            {
                isMirrorPosition = false;
                break;
            }
        }
        if (isMirrorPosition && mirror_index != dissalowed)
        {
            return mirror_index;
            break;
        }
    }

    return 0;
}

int main()
{
    vector<vector<vector<char>>> input_char_groups = readFileGroups("input.txt");

    int total = 0;

    vector<vector<int>> old_mirrors;
    for (int i = 0; i < input_char_groups.size(); i++)
    {
        old_mirrors.push_back({ReturnVerticalMirror(input_char_groups[i]), ReturnHorizontalMirror(input_char_groups[i])});
    }

    for (int i = 0; i < input_char_groups.size(); i++)
    {
        bool FoundSmudge = false;
        for (int j = 0; j < input_char_groups[i].size(); j++)
        {
            for (int k = 0; k < input_char_groups[i][j].size(); k++)
            {
                vector<vector<char>> map_temp_copy = input_char_groups[i];
                if (map_temp_copy[j][k] == '.')
                {
                    map_temp_copy[j][k] = '#';
                }
                else
                {
                    map_temp_copy[j][k] = '.';
                }
                vector<int> temp_pair = {ReturnNewUniqueVerticalMirror(map_temp_copy, old_mirrors[i][0]), ReturnNewUniqueHorizontalMirror(map_temp_copy, old_mirrors[i][1])};
                if (!(temp_pair[0] == 0 && temp_pair[1] == 0))
                {
                    FoundSmudge = true;
                    total += (temp_pair[0]) + (temp_pair[1] * 100) ;
                    break;
                }
            }
            if (FoundSmudge)
            {
                break;
            }
        }
    }

    std::cout << total << endl;

    return 0;
}