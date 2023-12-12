#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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
        cout << "Unable to open file";
    }

    return lines;
}

int main()
{

    int total = 0;

    vector<string> lines = readFileLines("input.txt");
    for (int i = 0; i < lines.size(); i++)
    {
        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

        bool setValid = true;
        string current_line = lines[i];
        int gameId = stoi(current_line.substr(5, current_line.find(":") - 5));
        vector<string> substrings;
        stringstream ss(current_line.substr(current_line.find(":") + 2, current_line.size() - current_line.find(":") + 2));

        while (ss.good())
        {
            string substr;
            getline(ss, substr, ';');
            substrings.push_back(substr);
        }

        for (int j = 0; j < substrings.size(); j++)
        {
            stringstream substrStream(substrings[j]);
            int total_quantity = 0;
            string color;

            while (substrStream.good())
            {
                string item;
                getline(substrStream, item, ',');

                item = item.substr(item.find_first_not_of(" \t\n\r\f\v"), item.find_last_not_of(" \t\n\r\f\v") - item.find_first_not_of(" \t\n\r\f\v") + 1);

                int quantity = stoi(item.substr(0, item.find(" ")));
                color = item.substr(item.find(" ") + 1, item.size() - item.find(" "));

                if (color == "red")
                {
                    if (quantity > max_red)
                    {
                        max_red = quantity;
                    }
                }
                else if (color == "green")
                {
                    if (quantity > max_green)
                    {
                        max_green = quantity;
                    }
                }
                else if (color == "blue")
                {
                    if (quantity > max_blue)
                    {
                        max_blue = quantity;
                    }
                }
            }
        }
        total += max_red * max_green * max_blue;
    }
    cout << total << endl;
    return 0;
}