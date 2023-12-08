#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

const char* ONE     = "one";
const char* TWO     = "two";
const char* THREE   = "three";
const char* FOUR    = "four";
const char* FIVE    = "five";
const char* SIX     = "six";
const char* SEVEN   = "seven";
const char* EIGHT   = "eight";
const char* NINE    = "nine";

const char* NUMBERS[] = {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

int integer_from_string(const char* number) {
    for (int i = 0; i < sizeof(NUMBERS) / sizeof(NUMBERS[0]); ++i) {
        if (strcmp(number, NUMBERS[i]) == 0) {
            return i + 1;
        }
    }
    return -1;
}

class Node {
public:
    Node* next;
    int value;
    Node (int value) : value(value), next(nullptr) {}
};

class DLL {
public:
    DLL() : root(nullptr), last(nullptr), size(0) {}
    ~DLL() {
        this->destroyList(root);
    }
    int get_first() { return this->root->value; }
    int get_last() { return this->last->value; }
    int get_size() { return this->size; }

    void insert(int value) {
        this->size++;
        if (this->root == nullptr) {
            this->root = new Node(value);
            this->last = this->root;
            return;
        }
        insert(value, this->root);
    }
private:
    Node* root;
    Node* last;
    int size;
    void insert(int value, Node* node) {
        if (node->next == nullptr) {
            node->next = new Node(value);
            this->last = node->next;
            return;
        }
        insert(value, node->next);
    }
    void destroyList(Node* node) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
};


class CalculateNumbers {
public:
    CalculateNumbers(char* filename) {
        sum = 0;
        ifstream in(filename);

        int bufferSize = 256;
        char buffer[bufferSize];

        while (in.getline(buffer, bufferSize)) {
            DLL integers = DLL();
            for (int i = 0; i < bufferSize; i++) {
                
                if (buffer[i] == '\0') {
                    break;
                }
                if (isdigit(buffer[i])) {
                    integers.insert((int)(buffer[i] - '0'));
                    continue;
                }
                for (int j = 0; j < sizeof(NUMBERS) / sizeof(NUMBERS[0]); j++) {
                    int end_index = strlen(NUMBERS[j]);

                    char range[end_index + 1];
                    int rangeIndex = 0;

                    for (int k = i; k < i + end_index; k++) {
                        range[rangeIndex++] = buffer[k];
                    }
                    range[rangeIndex] = '\0';

                    if (strcmp(NUMBERS[j], range) == 0) {
                        integers.insert(integer_from_string(NUMBERS[j]));
                        break;
                    } 
                }
            }
            int first_value = integers.get_first();
            int last_value = integers.get_last();

            string first = to_string(first_value) + to_string(last_value);
            sum += stoi(first);

        };
    }
    int get_sum() {
        return this->sum;
    }

private:
    int sum;
};


int main(int argc, char *argv[]) {
    CalculateNumbers advent(argv[1]);
    cout << advent.get_sum() << endl;
    return 0;
};