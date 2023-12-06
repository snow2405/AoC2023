#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(){

    const int DataSize = 1;
    long long Time[DataSize] = {56717999};
    long long Distance[DataSize] = {334113513502430};
    
    long long total = 1;

    for(int i = 0; i < DataSize; i++){
        long long possible_wins = 0;
        for(long long j = 0; j < Time[i]; j++){
            long long result_length = ((Time[i]-j) * j);
            if(result_length > Distance[i]){
                possible_wins++;
            }
        }
        total = total * possible_wins;
    }
    cout << total << endl;

    return 0;
}