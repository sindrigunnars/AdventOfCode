#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

int getNumber(string str, int index, int row, set<tuple<int,int>>& processed) {
    int i = index;
    int j = index;
    while (isdigit(str[j]) && j < str.length()) {
        j++;     
    }
    while (isdigit(str[i]) && i >= 0) {
        i--;     
    }
    for (int it = i+1; it < j; it++) {
        processed.insert(make_tuple(row, it));
    }
    return stoi(str.substr(i+1, j));
}

vector<int> adjacentNumbers(vector<string> arr, int i, int j) {
    vector<int> result;
    set<tuple<int, int>> processed;
    if (i + 1 < arr.size() && isdigit(arr[i+1][j]) && processed.find(make_tuple(i+1, j)) == processed.end()) {
        int number = getNumber(arr[i+1], j, i+1, processed);
        result.push_back(number);
    }
    if (i > 0 && isdigit(arr[i-1][j]) && processed.find(make_tuple(i-1, j)) == processed.end()) {
        int number = getNumber(arr[i-1], j, i-1, processed);
        result.push_back(number);
    }
    if (i + 1 < arr[i].length() && isdigit(arr[i][j+1]) && processed.find(make_tuple(i, j+1)) == processed.end()) {
        int number = getNumber(arr[i], j+1, i, processed);
        result.push_back(number);
    }
    if (j > 0 && isdigit(arr[i][j-1]) && processed.find(make_tuple(i, j-1)) == processed.end()) {
        int number = getNumber(arr[i], j-1, i, processed);
        result.push_back(number);
    }
    if (i + 1 < arr.size() && j + 1 < arr[i].length() && isdigit(arr[i+1][j+1]) && processed.find(make_tuple(i+1, j+1)) == processed.end()) {
        int number = getNumber(arr[i+1], j+1, i+1, processed);
        result.push_back(number);
    }
    if (i + 1 < arr.size() && j > 0 && isdigit(arr[i+1][j-1]) && processed.find(make_tuple(i+1, j-1)) == processed.end()) {
        int number = getNumber(arr[i+1], j-1, i+1, processed);
        result.push_back(number);
    }
    if (j + 1 < arr[i].length() && i > 0 && isdigit(arr[i-1][j+1]) && processed.find(make_tuple(i-1, j+1)) == processed.end()) {
        int number = getNumber(arr[i-1], j+1, i-1, processed);
        result.push_back(number);
    }
    if (j > 0 && i > 0  && isdigit(arr[i-1][j-1]) && processed.find(make_tuple(i-1, j-1)) == processed.end()) {
        int number = getNumber(arr[i-1], j-1, i-1, processed);
        result.push_back(number);
    }
    return result;
}

int sumOfAdjacent(vector<int> arr) {
    int sum = 0;
    for (const int elem : arr) {
        sum += elem;
    }
    return sum;
} 


int main(int argc, char* argv[]) {
    string line;
    ifstream in(argv[1]);
    vector<string> lines;
    int sum = 0;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    vector<int> results;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            char current = lines[i][j];
            if (!isalnum(current) && current != '.') {
                results = adjacentNumbers(lines, i, j);
                sum += sumOfAdjacent(results);
            }
        }
    }
    cout << sum << endl;
    return 0;
}