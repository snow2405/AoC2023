#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> readFileLines(string fileName)
{
    vector<vector<char>> single_chars;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<char> chars_in_line;
            for (int i = 0; i < line.size(); i++)
            {
                chars_in_line.push_back(line[i]);
            }
            single_chars.push_back(chars_in_line);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    return single_chars;
}

int main()
{

    vector<vector<char>> input_chars = readFileLines("input.txt");

    int total = 0;

    for (int i = 0; i < input_chars.size(); i++)
    {
        int window_size = 0;
        string current_number = "";
        for (int j = 0; j < input_chars[i].size(); j++)
        {
            if (isdigit(input_chars[i][j]))
            {
                current_number += input_chars[i][j];
            }
            else
            {
                if (current_number != "")
                {
                    bool found_adjacent_symbol = false;
                    char temp_ch;
                    window_size = current_number.size() + 2;
                    int starting_index = j;

                    if (starting_index - window_size < 0)
                    {
                        window_size = starting_index + 1;
                    }
                    if (starting_index == input_chars[i].size())
                    {
                        starting_index--;
                        window_size--;
                    }
                    for (int k = starting_index; k > starting_index - window_size; k--)
                    {
                        if (i != 0)
                        {
                            temp_ch = input_chars[i - 1][k];
                            if (!isdigit(temp_ch) && temp_ch != '.')
                            {
                                found_adjacent_symbol = true;
                                break;
                            }
                        }
                        if (i != input_chars.size() - 1)
                        {
                            temp_ch = input_chars[i + 1][k];
                            if (!isdigit(temp_ch) && temp_ch != '.')
                            {
                                found_adjacent_symbol = true;
                                break;
                            }
                        }
                    }
                    temp_ch = input_chars[i][starting_index];
                    if (!isdigit(temp_ch) && temp_ch != '.')
                    {
                        found_adjacent_symbol = true;
                    }
                    temp_ch = input_chars[i][starting_index - window_size + 1];
                    if (!isdigit(temp_ch) && temp_ch != '.')
                    {
                        found_adjacent_symbol = true;
                    }
                    if (found_adjacent_symbol)
                    {
                        total += stoi(current_number);
                    }
                    current_number = "";
                }
            }
        }
        if (current_number != "")
        {
            bool found_adjacent_symbol = false;
            char temp_ch;
            window_size = current_number.size() + 1;
            int starting_index = input_chars[i].size()-1;

            if (starting_index - window_size < 0)
            {
                window_size = starting_index + 1;
            }
            for (int k = starting_index; k > starting_index - window_size; k--)
            {
                if (i != 0)
                {
                    temp_ch = input_chars[i - 1][k];
                    if (!isdigit(temp_ch) && temp_ch != '.')
                    {
                        found_adjacent_symbol = true;
                        break;
                    }
                }
                if (i != input_chars.size() - 1)
                {
                    temp_ch = input_chars[i + 1][k];
                    if (!isdigit(temp_ch) && temp_ch != '.')
                    {
                        found_adjacent_symbol = true;
                        break;
                    }
                }
            }
            temp_ch = input_chars[i][starting_index];
            if (!isdigit(temp_ch) && temp_ch != '.')
            {
                found_adjacent_symbol = true;
            }
            temp_ch = input_chars[i][starting_index - window_size + 1];
            if (!isdigit(temp_ch) && temp_ch != '.')
            {
                found_adjacent_symbol = true;
            }
            if (found_adjacent_symbol)
            {
                total += stoi(current_number);
            }
            current_number = "";
        }
    }
    cout << total << endl;
    return 0;
}