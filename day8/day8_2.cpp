#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <numeric>

std::mutex countsMutex;

long getLCM(std::vector<int> counts) {
    long calclcm = counts.front();
    for (long i = 1; i < counts.size(); i++) {
        calclcm = std::lcm(calclcm, counts[i]);
    }
    return calclcm;
}

bool allAreFinished(std::string currentNode) {
    return (currentNode[currentNode.length()-1] == 'Z');
}

std::string changeCurrentNodesLeft(std::string currentNode, std::map<std::string, std::pair<std::string,std::string>> nodeMap) {
    return nodeMap[currentNode].first;
}

std::string changeCurrentNodesRight(std::string currentNode, std::map<std::string, std::pair<std::string, std::string>> nodeMap) {
    return nodeMap[currentNode].second;
}

void run(std::string currentNodeCheck, std::vector<int> &counts,
        std::string instructions, std::map<std::string,
        std::pair<std::string,std::string>> nodeMap, int index) {

    bool running = true;
    int instruction = 0; int count = 0;
    std::string currentNode = currentNodeCheck;
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
    std::lock_guard<std::mutex> lock(countsMutex); // Locks counts access
    counts[index] = count;
}

int main(int argc, char* argv[]) {
    std::ifstream in(argv[1]);
    std::map<std::string, std::pair<std::string,std::string>> nodeMap;
    std::vector<std::string> currentNodes, endNodes;
    std::string instructions, emptyLine, node;

    getline(in, instructions);
    getline(in, emptyLine);

    while(getline(in, node)) {
        std::string node_start = node.substr(0, 3);
        std::string left = node.substr(node.find('=') + 3, 3);
        std::string right = node.substr(node.find(',') + 2, 3);
        nodeMap[node_start] = make_pair(left, right);
        if(node_start[node_start.length()-1] == 'A') {
            currentNodes.push_back(node_start);
        }
        if(node_start[node_start.length()-1] == 'Z') {
            endNodes.push_back(node_start);
        }
    }

    std::vector<int> counts(currentNodes.size());
    std::thread threads[currentNodes.size()]; // One thread for each A
    int i = 0;
    for (int i = 0; i < currentNodes.size(); i++) {
        threads[i] = std::thread(run, currentNodes[i], std::ref(counts), instructions, nodeMap, i);
    }
    for(int i = 0; i < currentNodes.size(); i++) {
        threads[i].join();
    }
    std::cout << getLCM(counts) << std::endl;
    std::cout << "Use LCM to find the correct answer as the paths form a cycle" << std::endl;
    std::cout << "(number of steps needed / instruction length = whole number)" << std::endl;
    return 0;
}