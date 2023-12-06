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

    string numberWords[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int total = 0;
    for(int i = 0; i<lines.size(); i++){
        string current_line = lines[i];
        string output = "";
        
        for(int j = 0; j<current_line.size(); j++){
            if(isdigit(current_line[j])){
                output += current_line[j];
            } else {
                for (int k = 0; k < 10; ++k) {
                    const string& word = numberWords[k];
                    if (current_line.substr(j, word.length()) == word) {
                        output += to_string(k); 
                        break;
                    }
                }
            }

        }
        output = string(1, output[0]) + string(1,output[output.size()-1]);
        total += stoi(output);
    }
    cout << total << endl;

    return 0;
}

