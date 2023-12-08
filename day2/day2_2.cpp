#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    int sum = 0;
    char name[32];
    char buffer[255];
    while (in.getline(name, sizeof(name), ':') && in.getline(buffer, sizeof(buffer))) {
        // Process the name and buffer here
        cout << name << ": " << buffer << endl;
        int red = 0;
        int green = 0;
        int blue = 0;
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
                if (strcmp(color, "red") == 0 && number > red) { red = number; }
                if (strcmp(color, "green") == 0 && number > green) { green = number; }
                if (strcmp(color, "blue") == 0 && number > blue) { blue = number; }
            } 
        }
        sum += (red * green * blue);
    }
    cout << sum << endl;
    return 0;
}