#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> input_chars;
int total = 0;

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

void checkForDigits(int x, int y)
{
    vector<int> ratios;
    if (x != 0)
    {
        vector<char> copy_of_upper_digits = input_chars[x - 1];
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (isdigit(copy_of_upper_digits[i]))
            {
                int begin = 0;
                int end = copy_of_upper_digits.size();
                for (int j = i; j > 0; j--)
                {
                    if (copy_of_upper_digits[j] == '.')
                    {
                        begin = j + 1;
                        break;
                    }
                }
                for (int j = i; j < copy_of_upper_digits.size(); j++)
                {
                    if (copy_of_upper_digits[j] == '.')
                    {
                        end = j;
                        break;
                    }
                }
                string digit_window = "";
                for (int j = begin; j < end; j++)
                {
                    digit_window += copy_of_upper_digits[j];
                    copy_of_upper_digits[j] = '.';
                }
                ratios.push_back(stoi(digit_window));
            }
        }
    }

    if (x != input_chars.size() - 1)
    {
        vector<char> copy_of_lower_digits = input_chars[x + 1];
        for (int i = y - 1; i <= y + 1; i++)
        {
            if (isdigit(copy_of_lower_digits[i]))
            {
                int begin = 0;
                int end = copy_of_lower_digits.size();
                for (int j = i; j > 0; j--)
                {
                    if (copy_of_lower_digits[j] == '.')
                    {
                        begin = j + 1;
                        break;
                    }
                }
                for (int j = i; j < copy_of_lower_digits.size(); j++)
                {
                    if (copy_of_lower_digits[j] == '.')
                    {
                        end = j;
                        break;
                    }
                }
                string digit_window = "";
                for (int j = begin; j < end; j++)
                {
                    digit_window += copy_of_lower_digits[j];
                    copy_of_lower_digits[j] = '.';
                }
                ratios.push_back(stoi(digit_window));
            }
        }
    }

    if (y != 0)
    {
        if (isdigit(input_chars[x][y - 1]))
        {
            int begin = 0;
            int end = y;
            for (int j = y; j > 0; j--)
            {
                if (input_chars[x][j] == '.')
                {
                    begin = j + 1;
                    break;
                }
            }
            string digit_window = "";
            for (int j = begin; j < end; j++)
            {
                digit_window += input_chars[x][j];
            }
            ratios.push_back(stoi(digit_window));
        }
    }
    if (y != input_chars[x].size() - 1)
    {
        if (isdigit(input_chars[x][y + 1]))
        {
            int begin = y + 1;
            int end = input_chars[x].size();
            for (int j = y; j < input_chars[x].size(); j++)
            {
                if (input_chars[x][j] == '.')
                {
                    end = j;
                    break;
                }
            }
            string digit_window = "";
            for (int j = begin; j < end; j++)
            {
                digit_window += input_chars[x][j];
            }
            ratios.push_back(stoi(digit_window));
        }
    }

    if (ratios.size() == 2)
    {
        total += ratios[0] * ratios[1];
        input_chars[x][y] = '.';
    }
}

int main()
{
    input_chars = readFileLines("input.txt");

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
                            if (temp_ch == '*')
                            {
                                checkForDigits(i - 1, k);
                                break;
                            }
                        }
                        if (i != input_chars.size() - 1)
                        {
                            temp_ch = input_chars[i + 1][k];
                            if (temp_ch == '*')
                            {
                                checkForDigits(i + 1, k);
                                break;
                            }
                        }
                    }
                    temp_ch = input_chars[i][starting_index];
                    if (temp_ch == '*')
                    {

                        checkForDigits(i, starting_index);
                    }
                    temp_ch = input_chars[i][starting_index - window_size + 1];
                    if (temp_ch == '*')
                    {
                        checkForDigits(i, starting_index - window_size + 1);
                    }
                    current_number = "";
                }
            }
        }
        if (current_number != "")
        {
            char temp_ch;
            window_size = current_number.size() + 2;
            int starting_index = input_chars[i].size()-1;

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
                    if (temp_ch == '*')
                    {
                        checkForDigits(i - 1, k);
                        break;
                    }
                }
                if (i != input_chars.size() - 1)
                {
                    temp_ch = input_chars[i + 1][k];
                    if (temp_ch == '*')
                    {
                        checkForDigits(i + 1, k);
                        break;
                    }
                }
            }
            temp_ch = input_chars[i][starting_index];
            if (temp_ch == '*')
            {

                checkForDigits(i, starting_index);
            }
            temp_ch = input_chars[i][starting_index - window_size + 1];
            if (temp_ch == '*')
            {
                checkForDigits(i, starting_index - window_size + 1);
            }
            current_number = "";
        }
    }
    cout << total << endl;
    return 0;
}