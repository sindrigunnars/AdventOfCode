#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int calculateRecordBreak(int time, int distance) {
    int count = 0;
    for (int charge = 0; charge < time; charge++) {
        if (charge * (time - charge) > distance) { count++; }
    }
    return count;
}

int totalRecords(vector<int> time, vector<int> distance) {
    int number = time.size();
    int total = 1;
    for(int i = 0; i < number; i++) {
        total *= calculateRecordBreak(time[i], distance[i]);
    }
    return total;
}


int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    string timeLine, distanceLine;
    vector<int> time, distance;
    getline(in, timeLine); getline(in, distanceLine);
    stringstream timeStream(timeLine); stringstream distanceStream(distanceLine);
    string singleTime, singleDistance;
    timeStream >> singleTime; distanceStream >> singleDistance;
    while(timeStream >> singleTime && distanceStream >> singleDistance) {
        time.push_back(stoi(singleTime)); distance.push_back(stoi(singleDistance));
    }
    int count = totalRecords(time, distance);
    cout << count << endl;
    return 0;
}
