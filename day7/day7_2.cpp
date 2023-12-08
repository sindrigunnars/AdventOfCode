#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const vector<char> cards = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
const vector<string> types = {"5K", "4K", "FH", "3K", "2P", "P", "H"};

class CamelCardHand {
public:
    CamelCardHand(string hand, int bid) {
        this->hand = hand;
        this->bid = bid;
        this->type = getType();
    }
    friend ostream& operator<< (std::ostream& stream, const CamelCardHand& hand) {
        cout << hand.hand << " : " << hand.bid << " : " << hand.type << endl;
        return stream;
    }
    bool operator<(CamelCardHand& hand) {
        if (this->type == hand.type) {
            vector<const char>::iterator cardPos1;
            vector<const char>::iterator cardPos2;
            for (int i = 0; i < this->hand.length(); i++) {
                cardPos1 = find(cards.begin(), cards.end(), this->hand[i]);
                cardPos2 = find(cards.begin(), cards.end(), hand.hand[i]);
                if(distance(cardPos1, cardPos2) > 0) {
                    return false;
                }
                if(distance(cardPos1, cardPos2) < 0) {
                    return true;
                }
            }
            return false;
        }
        for (const string& handType : types) {
            if (handType == hand.type) {
                return true;
            }
            if (this->type == handType) {
                return false;
            }
        }
        return false;
    }
    int getBid() {return this->bid; }

private:
    string hand;
    string type;
    int bid;

    string getType() {
        map<char, int> count;
        string retType;
        for (const char& card : this->hand) {
            auto it = count.find(card);
            if (it == count.end()) {
                // Card not found in count, initialize count to 1
                count[card] = 1;
            } else {
                // Card found, increment the count
                it->second += 1;
            }
        }
        int uniqueCards = count.size();
        int jokerCount = count['J'];
        switch (uniqueCards) {
            case 5: {
                if (jokerCount == 0) {
                    retType = "H";
                    break;
                } else {
                    retType = "P";
                    break;
                }
            }
            case 4: {
                if (jokerCount == 0) {
                    retType = "P";
                    break;
                } else {
                    retType = "3K";
                    break;
                }
            }
            case 3: {
                if (jokerCount == 2 || jokerCount == 3) {
                    retType = "4K";
                    break;
                }
                int maxAmount = 0;
                for (const auto & elem : count) {
                    if (elem.second > maxAmount) {
                        maxAmount = elem.second;
                    }
                }
                if (jokerCount == 0 && maxAmount == 2) {
                    retType = "2P";
                    break;
                }
                if (jokerCount == 0 && maxAmount == 3) {
                    retType = "3K";
                    break;
                }
                retType = jokerCount == 1 ? (maxAmount == 3 ? "4K" : "FH") : (maxAmount == 2 ? "2P" : "FH");
                break;
            }
            case 2: {
                if (jokerCount > 0) {
                    retType = "5K";
                    break;
                }
                bool fullHouse = false;
                for (const auto &elem : count) {
                    if (elem.second == 2 || elem.second == 3) {
                        fullHouse = true;
                        break;
                    }
                }
                retType = fullHouse ? "FH" : "4K";
                break;
            }
            case 1: {
                retType = "5K";
                break;
            }
        }
        return retType;
    }

};

bool compare(CamelCardHand& hand1, CamelCardHand& hand2) {
    return (hand1 < hand2);
}

class Game {
public:
    Game() {}
    void insert(CamelCardHand hand) {
        this->hands.push_back(hand);
    }
    int calculateGame() {
        this->sort();
        long sum = 0;
        for(int i = 0; i < this->hands.size(); i++) {
            sum += ((i+1) * this->hands[i].getBid());
        }
        return sum;
    }
    void sort() {
        std::sort(this->hands.begin(), this->hands.end(), compare);
    }
    friend ostream& operator<< (std::ostream& stream, const Game& game) {
        for (const CamelCardHand& hand : game.hands) {
            cout << hand;
        }
        return stream;
    }
private:
    vector<CamelCardHand> hands;
};

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    string cardsHand, bid;
    Game game;
    while(getline(in, cardsHand, ' ') && getline(in, bid)) {
        CamelCardHand hand = CamelCardHand(cardsHand, stoi(bid));
        game.insert(hand);
    }
    long sum = game.calculateGame();
    cout << game << endl;
    cout << sum << endl;

    return 0;
}