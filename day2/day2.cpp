#include <iostream>
#include <fstream>
using namespace std;

bool valid(char* color, int value) {
    if (strcmp(color, "blue") == 0) {
        return value <= 14;
    }
    if (strcmp(color, "green") == 0) {
        return value <= 13;
    }
    if (strcmp(color, "red") == 0) {
        return value <= 12;
    }
    return false;
}

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    int sum = 0;
    char name[32];
    char buffer[255];
    while (in.getline(name, sizeof(name), ':') && in.getline(buffer, sizeof(buffer))) {
        // Process the name and buffer here
        cout << name << ": " << buffer << endl;
        bool game_valid = true;

        vector<char*> sub_games;

        char *p = strtok(buffer, ";");
        sub_games.push_back(p);
        while (p) {
            p = strtok(nullptr, ";");
            if (p) {
                sub_games.push_back(p);
            }
        }
        for (char* elem : sub_games) {
            vector<char*> single_item;

            char *q = strtok(elem, ",");
            single_item.push_back(q);
            while (q) {
                q = strtok(nullptr, ",");
                if (q) {
                    single_item.push_back(q);
                }
            }
            for (char* single : single_item) {
                int number = atoi(strtok(single, " "));
                char *color = strtok(nullptr, " ");
                if(!valid(color, number)) { 
                    game_valid = false;
                    break;
                }
            }  
            if (!game_valid) {break;}
        }
        if (game_valid) {
            char* game_str = strtok(name, " ");
            sum += atoi(strtok(nullptr, " "));

        }
    }
    cout << sum << endl;
    return 0;
}