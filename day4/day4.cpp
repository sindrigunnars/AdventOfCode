#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
using namespace std;

class Card {
public:
    Card(string numbers, string winners) {
        string no, win;
        stringstream numberStream(numbers);
        stringstream winnerStream(winners);
        while (numberStream >> no) {
            cardNumbers.insert(no);
        }
        while (winnerStream >> win) {
            winnerNumbers.insert(win);
        }
        int numOfCorrect = correctAmount();
        total = calculateScore(numOfCorrect);
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

};


int main(int argc, char* argv[]) {

    string name, numbers, winners;
    int sum = 0;
    ifstream in(argv[1]);
    while(getline(in, name, ':') && getline(in, numbers, '|') && getline(in, winners)) {
        Card test(numbers, winners);
        sum += test.getScore();
    }
    cout << sum << endl;
    return 0;
}