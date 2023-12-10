#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> readFileLinesAndChars(string fileName)
{
    vector<vector<char>> linesAndChars;
    ifstream file(fileName);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<char> chars(line.begin(), line.end());
            linesAndChars.push_back(chars);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    return linesAndChars;
}
void DecideDirection(char dir, int xCurrent, int yCurrent, int xOld, int yOld, int &xNew, int &yNew)
{
    xNew = xCurrent;
    yNew = yCurrent;
    switch (dir)
    {
    case '|': // Vertical pipe (north and south)
        if (xCurrent - 1 != xOld)
        {
            xNew = xCurrent - 1;
        }
        else
        {
            xNew = xCurrent + 1;
        }
        break;

    case '-': // Horizontal pipe (east and west)
        if (yCurrent - 1 != yOld)
        {
            yNew = yCurrent - 1;
        }
        else
        {
            yNew = yCurrent + 1;
        }
        break;

    case 'L': // 90-degree bend (north and east)
        if (xCurrent - 1 != xOld)
        {
            xNew = xCurrent - 1;
        }
        else
        {
            yNew = yCurrent + 1;
        }
        break;

    case 'J': // 90-degree bend (north and west)
        if (xCurrent - 1 != xOld)
        {
            xNew = xCurrent - 1;
        }
        else
        {
           yNew = yCurrent - 1;
        }
        break;

    case '7': // 90-degree bend (south and west)
        if (xCurrent + 1 != xOld)
        {
            xNew = xCurrent + 1;
        }
        else
        {
            yNew = yCurrent - 1;
        }
        break;

    case 'F': // 90-degree bend (south and east)
        if (xCurrent + 1 != xOld)
        {
            xNew = xCurrent + 1;
        }
        else
        {
            yNew = yCurrent + 1;
        }
        break;

    default:
        // Handle unknown direction
        cout << "Unknown pipe direction: " << dir << endl;
        break;
    }
}

int main()
{
    vector<vector<char>> fileContent = readFileLinesAndChars("input.txt");

    int xPos, yPos, xLast, yLast, xNew, yNew = 0;

    // Optionally, print the content to check
    for (size_t i = 0; i < fileContent.size(); ++i)
    {
        bool FoundStart = false;
        for (size_t j = 0; j < fileContent[i].size(); ++j)
        {
            if (fileContent[i][j] == 'S')
            {
                FoundStart = true;
                xLast = i;
                yLast = j;
                if (fileContent[i + 1][j] != '.')
                {
                    xPos = i + 1;
                    yPos = j;
                }
                else if (fileContent[i - 1][j] != '.')
                {
                    xPos = i - 1;
                    yPos = j;
                }
                else if (fileContent[i][j + 1] != '.')
                {
                    xPos = i;
                    yPos = j + 1;
                }
                else if (fileContent[i][j - 1] != '.')
                {
                    xPos = i;
                    yPos = j - 1;
                }
            }
        }
        if (FoundStart)
        {
            break;
        }
    }
    int counter = 0;
    while (fileContent[xPos][yPos] != 'S')
    {
        DecideDirection(fileContent[xPos][yPos], xPos, yPos, xLast, yLast, xNew, yNew);
        xLast = xPos;
        yLast = yPos;
        xPos = xNew;
        yPos = yNew;
        counter ++;
    }
    cout << (counter/2)+1 << endl;

    return 0;
}