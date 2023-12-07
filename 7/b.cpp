#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<string>> readFileLines(string fileName)
{
    vector<vector<string>> lines;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            string first = line.substr(0, line.find(" "));
            string second = line.substr(line.find(" ") + 1, line.size());
            lines.push_back({first, second});
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    return lines;
}

int getCardValue(char card)
{
    char card_values[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
    for (int i = 0; i < 13; i++)
    {
        if (card_values[i] == card)
            return i;
    }
    return 0;
}

bool compareTwoHands(string main_hand, string compare_hand)
{
    int main_local_rank;
    int compare_local_rank;

    int main_card_ammount[5] = {0, 0, 0, 0, 0};
    int main_j_counter = 0;
    int compare_card_ammount[5] = {0, 0, 0, 0, 0};
    int compare_j_counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (main_hand[i] == 'J')
        {
            main_j_counter++;
        }
        else
        {
            if (main_hand[0] == main_hand[i])
            {
                main_card_ammount[0]++;
            }
            else if (main_hand[1] == main_hand[i])
            {
                main_card_ammount[1]++;
            }
            else if (main_hand[2] == main_hand[i])
            {
                main_card_ammount[2]++;
            }
            else if (main_hand[3] == main_hand[i])
            {
                main_card_ammount[3]++;
            }
            else if (main_hand[4] == main_hand[i])
            {
                main_card_ammount[4]++;
            }
        }
        if (compare_hand[i] == 'J')
        {
            compare_j_counter++;
        }
        else
        {
            if (compare_hand[0] == compare_hand[i])
            {
                compare_card_ammount[0]++;
            }
            else if (compare_hand[1] == compare_hand[i])
            {
                compare_card_ammount[1]++;
            }
            else if (compare_hand[2] == compare_hand[i])
            {
                compare_card_ammount[2]++;
            }
            else if (compare_hand[3] == compare_hand[i])
            {
                compare_card_ammount[3]++;
            }
            else if (compare_hand[4] == compare_hand[i])
            {
                compare_card_ammount[4]++;
            }
        }
    }
    sort(main_card_ammount, main_card_ammount + 5, greater<int>());
    sort(compare_card_ammount, compare_card_ammount + 5, greater<int>());
    main_card_ammount[0] += main_j_counter;
    compare_card_ammount[0] += compare_j_counter;
    if (main_card_ammount[0] == 5)
    {
        main_local_rank = 7;
    }
    else if (main_card_ammount[0] == 4)
    {
        main_local_rank = 6;
    }
    else if (main_card_ammount[0] == 3 && main_card_ammount[1] == 2)
    {
        main_local_rank = 5;
    }
    else if (main_card_ammount[0] == 3)
    {
        main_local_rank = 4;
    }
    else if (main_card_ammount[0] == 2 && main_card_ammount[1] == 2)
    {
        main_local_rank = 3;
    }
    else if (main_card_ammount[0] == 2)
    {
        main_local_rank = 2;
    }
    else
    {
        main_local_rank = 1;
    }
    if (compare_card_ammount[0] == 5)
    {
        compare_local_rank = 7;
    }
    else if (compare_card_ammount[0] == 4)
    {
        compare_local_rank = 6;
    }
    else if (compare_card_ammount[0] == 3 && compare_card_ammount[1] == 2)
    {
        compare_local_rank = 5;
    }
    else if (compare_card_ammount[0] == 3)
    {
        compare_local_rank = 4;
    }
    else if (compare_card_ammount[0] == 2 && compare_card_ammount[1] == 2)
    {
        compare_local_rank = 3;
    }
    else if (compare_card_ammount[0] == 2)
    {
        compare_local_rank = 2;
    }
    else
    {
        compare_local_rank = 1;
    }

    if (main_local_rank == compare_local_rank)
    {
        for (int i = 0; i < 5; i++)
        {
            if (getCardValue(main_hand[i]) > getCardValue(compare_hand[i]))
            {

                return false;
            }
            else if (getCardValue(main_hand[i]) < getCardValue(compare_hand[i]))
            {

                return true;
            }
        }
    }
    else
    {
        if (compare_local_rank > main_local_rank)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<vector<string>> lines = readFileLines("input.txt");

    bool sort_was_needed = true;
    int cycle_count = 0;
    while (sort_was_needed)
    {
        sort_was_needed = false;
        for (int i = 0; i < lines.size(); i++)
        {

            if (i < lines.size() - 1)
            {
                if (compareTwoHands(lines[i][0], lines[i + 1][0]))
                {

                    vector<string> temp = {lines[i][0], lines[i][1]};
                    lines[i] = lines[i + 1];
                    lines[i + 1] = temp;
                    sort_was_needed = true;
                }
            }
        }
        cycle_count++;
        std::cout << "sort cycle: " << cycle_count << endl;
    }

    std::cout << "finished sorting" << endl;

    long long total = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        total += stoi(lines[i][1]) * (i + 1);
    }
    std::cout << "total: " << total << endl;

    return 0;
}