#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::ifstream in(argv[1]);
    std::vector<std::string> grid;
    std::string row;
    int rowNumber = 0;
    std::pair<int,int> sLocation;
    while (getline(in, row)) {
        int columnNumber = row.find('S');
        if ( columnNumber != row.npos) {
            sLocation = std::make_pair(rowNumber, columnNumber);
        }
        grid.push_back(row);
        rowNumber++;
    }
    for (const std::string & line : grid) {
        std::cout << line << std::endl;
    }
}