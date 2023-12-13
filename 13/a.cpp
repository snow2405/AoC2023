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
        cout << "Unable to open file";
    }

    return groups;
}

int main()
{
    vector<vector<vector<char>>> input_char_groups = readFileGroups("input.txt");
    int total = 0;
    for (int i = 0; i < input_char_groups.size(); ++i)
    {
        // Check for vertical mirror position
        for (int mirror_index = 1; mirror_index < input_char_groups[i][0].size(); mirror_index++)
        {
            bool isMirrorPosition = true;
            for (int j = 0; j < input_char_groups[i].size(); j++)
            {
                int side_lengths = mirror_index;
                string left_side;
                string right_side;
                if (side_lengths > (input_char_groups[i][j].size() - mirror_index))
                {
                    side_lengths = input_char_groups[i][j].size() - mirror_index;
                    left_side = string(input_char_groups[i][j].begin() + (mirror_index - side_lengths), input_char_groups[i][j].begin() + mirror_index);
                    right_side = string(input_char_groups[i][j].begin() + mirror_index, input_char_groups[i][j].begin() + (mirror_index + side_lengths));
                }
                else
                {

                    left_side = string(input_char_groups[i][j].begin() + (mirror_index - side_lengths), input_char_groups[i][j].begin() + side_lengths);
                    right_side = string(input_char_groups[i][j].begin() + mirror_index, input_char_groups[i][j].begin() + (mirror_index + side_lengths));
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
                total += mirror_index;
                break;
            }
        }

        // Check for horizontal mirror position
        for (int mirror_index = 1; mirror_index < input_char_groups[i].size(); mirror_index++)
        {
            bool isMirrorPosition = true;
            for (int j = 0; j < input_char_groups[i][0].size(); j++)
            {
                int side_lengths = mirror_index;
                if (mirror_index > (input_char_groups[i].size() - mirror_index))
                {
                    side_lengths = input_char_groups[i].size() - mirror_index;
                }
                string top_side;
                string bottom_side;

                for (int k = mirror_index - side_lengths; k < mirror_index; k++)
                {
                    top_side += input_char_groups[i][k][j];
                }
                for (int k = mirror_index; k < mirror_index + side_lengths; k++)
                {
                    bottom_side += input_char_groups[i][k][j];
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
                total += (mirror_index * 100);
                break;
            }
        }
    }
    cout << total << endl;

    return 0;
}