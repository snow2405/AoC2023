#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> readFileLines(string fileName) {
    vector<string> lines;
    ifstream file(fileName);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }

    return lines;
}

int main(){

    vector<string> lines = readFileLines("input.txt");

    return 0;
}