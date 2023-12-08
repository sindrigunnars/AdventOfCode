#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

class Card {
public:
    Card(string numbers, string winners, vector<int>& copies, int it) {
        string no, win;
        stringstream numberStream(numbers);
        stringstream winnerStream(winners);
        while (numberStream >> no) {
            cardNumbers.insert(no);
        }
        while (winnerStream >> win) {
            winnerNumbers.insert(win);
        }
        total = correctAmount();
        increment(copies, it);
    }
    int getScore() { return total; }
private:
    set<string> cardNumbers, winnerNumbers;
    int total;
    int correctAmount() {
        int numberOfCorrect = 0;
        for (const string elem : cardNumbers) {
            if (winnerNumbers.find(elem) != winnerNumbers.end()) {
                numberOfCorrect++;
            }
        }
        return numberOfCorrect;
    }
    int calculateScore(int numOfCorrect) {
        if (numOfCorrect == 0) { return 0; }
        int ret_val = 1;
        for (int i = 1; i < numOfCorrect; i++) {
            ret_val *= 2;
        }
        return ret_val;
    }
    void increment(vector<int>& copies, int it) {
        if (copies.size() <= it) { copies.push_back(1); }
        for (int i = it + 1; i < it + total + 1; i++) {
            if (copies.size() <= i) { copies.push_back(1); }
            copies[i] += copies[it];
        }
    }

};


int main(int argc, char* argv[]) {

    string name, numbers, winners;
    vector<int> copies;
    int it = 0;
    int sum = 0;
    ifstream in(argv[1]);
    while(getline(in, name, ':') && getline(in, numbers, '|') && getline(in, winners)) {
        Card test(numbers, winners, copies, it);
        it++;
    }
    for (const int elem : copies) {
        sum += elem;
    }
    cout << sum << endl;;
    return 0;
}