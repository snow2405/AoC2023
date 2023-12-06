#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(){

    const int DataSize = 4;
    int Time[DataSize] = {56,71,79,99};
    int Distance[DataSize] = {334,1135,1350,2430};
    
    int total = 1;

    for(int i = 0; i < DataSize; i++){
        int possible_wins = 0;
        for(int j = 0; j < Time[i]; j++){
            int result_length = ((Time[i]-j) * j);
            if(result_length > Distance[i]){
                possible_wins++;
            }
        }
        total = total * possible_wins;
    }
    cout << total << endl;

    return 0;
}