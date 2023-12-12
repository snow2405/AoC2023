#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

vector<string> readFileLines(string fileName)
{
    vector<string> lines;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    return lines;
}

int main()
{
    vector<string> lines = readFileLines("input.txt");

    int total = 0;

    int *repetition_counter = new int[lines.size()];
    fill_n(repetition_counter, lines.size(), 1);

    for (int i = 0; i < lines.size(); i++)
    {
        string your_numbers = lines[i].substr(0, lines[i].find("|") - 1);
        your_numbers = your_numbers.substr(your_numbers.find(":") + 2, your_numbers.size() - your_numbers.find(":"));
        string winning_numbers = lines[i].substr(lines[i].find("|") + 2, lines[i].size() - lines[i].find("|"));

        vector<int> your_numbers_vector;
        if (your_numbers[0] == ' ')
        {
            your_numbers.erase(0, 1);
        }
        size_t pos = 0;
        string token;
        while ((pos = your_numbers.find(" ")) != string::npos)
        {
            token = your_numbers.substr(0, pos);
            your_numbers_vector.push_back(stoi(token));
            your_numbers.erase(0, pos + 1);
            if (your_numbers[0] == ' ')
            {
                your_numbers.erase(0, 1);
            }
        }
        your_numbers_vector.push_back(stoi(your_numbers));

        vector<int> winning_numbers_vector;
        if (winning_numbers[0] == ' ')
        {
            winning_numbers.erase(0, 1);
        }
        pos = 0;
        while ((pos = winning_numbers.find(" ")) != string::npos)
        {
            token = winning_numbers.substr(0, pos);
            winning_numbers_vector.push_back(stoi(token));
            winning_numbers.erase(0, pos + 1);
            if (winning_numbers[0] == ' ')
            {
                winning_numbers.erase(0, 1);
            }
        }
        winning_numbers_vector.push_back(stoi(winning_numbers));

        int winner = 0;
        for (int j = 0; j < your_numbers_vector.size(); j++)
        {
            for (int k = 0; k < winning_numbers_vector.size(); k++)
            {
                if (your_numbers_vector[j] == winning_numbers_vector[k])
                {
                    winner++;
                    winning_numbers_vector.erase(winning_numbers_vector.begin() + k);
                    k--;
                    break;
                }
            }
        }
        std::cout << "Winner: " << winner << " card: " << i << " reps:" << repetition_counter[i] << endl;
        total += repetition_counter[i];
        for (int j = 0; j < winner; j++)
        {
            repetition_counter[i + j + 1] += repetition_counter[i];
        }
    }
    std::cout << total << endl;

    delete[] repetition_counter;

    return 0;
}