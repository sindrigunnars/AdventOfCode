#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

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