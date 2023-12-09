#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

bool allAreZero(const std::vector<int> sequence) {
    for (const int & elem : sequence) {
        if (elem != 0) {
            return false;
        }
    }
    return true;
}

int processData(std::vector<int>& sequence) {
    std::vector<std::vector<int>> sequenceCalc;
    sequenceCalc.push_back(sequence);
    int i = 0;
    while ( !allAreZero(sequenceCalc[i]) && sequenceCalc[i].size() > 1) {
        std::vector<int> newSequence(sequenceCalc[i].size() - 1);
        for (int j = 1; j < sequenceCalc[i].size(); j++) {
            newSequence[j-1] = sequenceCalc[i][j] - sequenceCalc[i][j-1];
        }
        sequenceCalc.push_back(newSequence);
        i++;
    }
    int returnVal = 0;
    for (const auto & elem : sequenceCalc) {
        returnVal += elem.back();
    }
    return returnVal;
}


int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    std::vector<std::vector<int>> sequences;
    std::string currentSequenceString; 
    while(getline(in, currentSequenceString)) {
        std::stringstream sequenceLine(currentSequenceString);
        std::string number;
        std::vector<int> singleSequence;
        while(sequenceLine >> number) {
            singleSequence.push_back(stoi(number));
        }
        std::reverse(singleSequence.begin(), singleSequence.end());
        sequences.push_back(singleSequence);
    }
    int sum = 0;
    for (std::vector<int>& seqVec : sequences) {
        int nextNumber = processData(seqVec);
        sum = sum + nextNumber;
    }
    // 1934898173
    std::cout << sum << std::endl;
    return 0;
}