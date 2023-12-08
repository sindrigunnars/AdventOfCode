#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <unordered_set>
#include <sstream>
using namespace std;

template <size_t N>
unsigned int reverseFilter(vector<array<unsigned int, N>> filter, unsigned int output) {
    int result = output;
    for (const auto & range : filter) {
        if (range[0] <= output && output <= (range[0] + range[2])) {
            return output - (range[0] - range[1]);
        }
    }
    return result;
}
// 104902451
int main(int argc, char* argv[]) {
    vector<vector<array<unsigned int, 3>>> filters;
    vector<pair<unsigned int, unsigned int>> seeds;
    ifstream in(argv[1]);
    string line, name, numbers;
    string number, range;
    getline(in, name, ':');
    getline(in, numbers);
    stringstream seed(numbers);
    vector<array<unsigned int, 3>> stage;
    while(seed >> number >> range) {
        seeds.push_back(make_pair(stol(number), stol(range)));
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
    unsigned int max = 104902401;
    unsigned int min = 0;
    unsigned int index = 0;
    cout << "check" << endl;
    for (unsigned int i = 0; i < max; i++) {
        unsigned int seed = i;
        for (auto it = filters.rbegin(); it != filters.rend(); ++it) {
            const vector<array<unsigned int, 3>>& filter = *it;
            seed = reverseFilter(filter, seed);
        }
        for (const auto& pair : seeds) {
            if (pair.first <= seed && seed <= pair.first + pair.second) {
                if (min == 0 || i < min) {
                    min = i;
                }
                break;
            }
        }
    }

    cout << min << endl;

    return 0;
}