#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
using namespace std;
// Destination Source Range
// If input is in a source range the corresponding destination is input + (destination range start - source range start)
// If input is not in a range it stays the same through that filter
template <size_t N>
int filter(vector<array<unsigned int, N>> filter, int input) {
    for (const array<unsigned int,N> range : filter) {
        if(range[1] <= input && input <= (range[1] + range[2])) {
            return input + (range[0] - range[1]);
        }
    }
    return input;
};

int main(int argc, char* argv[]) {
    vector<vector<array<unsigned int, 3>>> filters;
    vector<unsigned int> seeds;
    ifstream in(argv[1]);
    string line, name, numbers;
    string singleNumber;
    getline(in, name, ':');
    getline(in, numbers);
    stringstream seed(numbers);
    vector<array<unsigned int, 3>> stage;
    while(seed >> singleNumber) {
        seeds.push_back(stol(singleNumber));
    }
    while(getline(in, numbers)) {
        if(numbers.find(':') == numbers.npos && !numbers.empty()) {
            array<unsigned int, 3> oneRow;
            stringstream row(numbers);
            string single;
            for (int i = 0; i < 3; i++) {
                row >> single;
                oneRow[i] = stol(single);

            }
            stage.push_back(oneRow);
        } else if (numbers.find(':') != numbers.npos)  {
            if (stage.size() != 0) {
                filters.push_back(stage);
            }
            stage.clear();
        }
    }
    filters.push_back(stage);
    unsigned int min = 0;
    int seedno = 104902451;
    for (unsigned int seed : seeds) {
        for (const auto& elem : filters) {
            seedno = filter(elem, seedno);
            cout << seedno << endl;
        }
        if (min == 0 || seedno < min) {
                min = seedno;
        }
    }

    cout << min << endl;

    return 0;
}