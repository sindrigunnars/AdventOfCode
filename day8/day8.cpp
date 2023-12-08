#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;


int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    map<string, pair<string,string>> nodeMap;
    string instructions, emptyLine, node;
    getline(in, instructions);
    getline(in, emptyLine);
    while(getline(in, node)) {
        string node_start = node.substr(0, 3);
        string left = node.substr(node.find('=') + 3, 3);
        string right = node.substr(node.find(',') + 2, 3);
        nodeMap[node_start] = make_pair(left, right);
    }
    cout << "data finished" << endl;
    string currentNode = "AAA";
    int instruction = 0; int count = 0;
    while(currentNode != "ZZZ") {
        if (instructions[instruction] == 'L') {
            currentNode = nodeMap[currentNode].first;
        }
        if (instructions[instruction] == 'R') {
            currentNode = nodeMap[currentNode].second;
        }
        cout << currentNode << endl;
        instruction++;
        count++;
        if (instruction == instructions.length()) {
            instruction = 0;
        }
    }
    cout << count << endl;
    return 0;
}