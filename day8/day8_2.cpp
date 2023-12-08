#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

bool allAreFinished(string currentNode) {
    return (currentNode[currentNode.length()-1] == 'Z');
}

string changeCurrentNodesLeft(string currentNode, map<string, pair<string,string>> nodeMap) {
    return nodeMap[currentNode].first;
}

string changeCurrentNodesRight(string currentNode, map<string, pair<string,string>> nodeMap) {
    return nodeMap[currentNode].second;
}

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    map<string, pair<string,string>> nodeMap;
    vector<string> currentNodes, endNodes;
    string instructions, emptyLine, node;

    getline(in, instructions);
    getline(in, emptyLine);

    while(getline(in, node)) {
        string node_start = node.substr(0, 3);
        string left = node.substr(node.find('=') + 3, 3);
        string right = node.substr(node.find(',') + 2, 3);
        nodeMap[node_start] = make_pair(left, right);
        if(node_start[node_start.length()-1] == 'A') {
            currentNodes.push_back(node_start);
        }
        if(node_start[node_start.length()-1] == 'Z') {
            endNodes.push_back(node_start);
        }
    }

    cout << "data finished " << instructions.length() << endl;
    vector<int> counts;
    for (const string& currentNodeCheck : currentNodes) {
        bool running = true;
        int instruction = 0; int count = 0;
        string currentNode = currentNodeCheck;
        while(running) {
            if (instructions[instruction] == 'L') {
                currentNode = changeCurrentNodesLeft(currentNode, nodeMap);
            }
            if (instructions[instruction] == 'R') {
                currentNode = changeCurrentNodesRight(currentNode, nodeMap);
            }
            instruction++;
            count++;
            if (instruction == instructions.length()) {
                instruction = 0;
            }
            bool allAreZed = allAreFinished(currentNode);
            if (allAreZed) { 
                running = false;
                break; 
            }
        }
        counts.push_back(count);
    }
    for (const auto& count : counts) {
        cout << count << " ";
    }
    cout << "Use LCM to find the correct answer as the paths form a cycle (number of steps needed / instruction lenggth = whole number)" << endl;
    return 0;
}