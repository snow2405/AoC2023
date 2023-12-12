// complete rewrite as solution from a, would take 20+ days with brute force approach :/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <tuple>
#include <fstream>

using namespace std;

string condition;
vector<int> record;
long long result;

vector<int> parseRecordString(const string &recordStr)
{
    stringstream ss(recordStr);
    vector<int> parsedRecord;
    string number;
    while (getline(ss, number, ','))
    {
        parsedRecord.push_back(stoi(number));
    }
    return parsedRecord;
}

long long find_combinations(int short_condition, int result_of_i, int char_in_string)
{
    int conditionSize = static_cast<int>(condition.size());
    int recordSize = static_cast<int>(record.size());

    if (short_condition >= conditionSize)
    {
        bool isResultValid = (result_of_i == recordSize - 1) && (char_in_string == record[result_of_i]);
        return result_of_i >= recordSize ? 1 : isResultValid;
    }

    bool shouldContinue = (result_of_i >= recordSize);
    if (shouldContinue)
    {
        while (short_condition < conditionSize)
        {
            if (condition[short_condition++] == '#')
            {
                return 0;
            }
        }
        return 1;
    }

    if (char_in_string > record[result_of_i])
    {
        return 0;
    }

    static map<tuple<int, int, int>, long long> solution_of_cache;
    if (short_condition == 0 && result_of_i == 0 && char_in_string == 0)
    {
        solution_of_cache.clear();
    }
    auto value_pointer = make_tuple(short_condition, result_of_i, char_in_string);

    long long cond_broken = 0, is_working = 0;

    char current = condition[short_condition];

    if (current == '?')
    {
        if (solution_of_cache.find(value_pointer) != solution_of_cache.end())
        {
            return solution_of_cache.at(value_pointer);
        }
        cond_broken = find_combinations(short_condition + 1, result_of_i, char_in_string + 1);
        if (char_in_string == record[result_of_i])
        {
            is_working = find_combinations(short_condition + 1, result_of_i + 1, 0);
        }
        else if (char_in_string == 0)
        {
            is_working = find_combinations(short_condition + 1, result_of_i, 0);
        }
        else
        {
            is_working = 0;
        }
        solution_of_cache.insert(make_pair(value_pointer, cond_broken + is_working));
        return cond_broken + is_working;
    }
    else if (current == '.')
    {
        if (!char_in_string)
        {
            long long return_value_of_search = find_combinations(short_condition + 1, result_of_i, 0);
            return return_value_of_search;
        }

        else if (char_in_string != record[result_of_i])
        {
            return 0;
        }
        else
        {
            return find_combinations(short_condition + 1, result_of_i + 1, 0);
        }
    }
    else if (current == '#')
    {
        if (char_in_string + 1 > record[result_of_i])
        {
            return 0;
        }

        else
        {
            return find_combinations(short_condition + 1, result_of_i, char_in_string + 1);
        }
    }
    return 0;
}

void processCondition(const string &short_condition, int repeat = 1)
{
    string extendedCondition = short_condition;
    for (int i = 1; i < repeat; ++i)
    {
        extendedCondition += "?" + short_condition;
    }

    condition = extendedCondition;
    if (repeat > 1)
    {
        vector<int> extendedRecord = record;
        for (int i = 1; i < repeat; ++i)
        {
            extendedRecord.insert(extendedRecord.end(), record.begin(), record.end());
        }
        record = extendedRecord;
    }
}

void solveProblemAndUpdateResults()
{
    processCondition(condition, 5);
    result += find_combinations(0, 0, 0);
}

void read_input_and_solve()
{
    ifstream inputFile("input.txt");
    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string recordStr;
        ss >> condition >> recordStr;
        record = parseRecordString(recordStr);

        solveProblemAndUpdateResults();
    }
}

int main()
{
    read_input_and_solve();
    cout << result << endl;
    return 0;
}
