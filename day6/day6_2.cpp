#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

long calculateRecordBreak (long time, long distance) {
    long count = 0;
    for (long charge = 0; charge < time; charge++) {
        if (charge * (time - charge) > distance) { count++; }
    }
    return count;
}

int main(int argc, char* argv[]) {
    ifstream in(argv[1]);
    string timeLine, distanceLine;
    getline(in, timeLine); getline(in, distanceLine);

    stringstream timeStream(timeLine); stringstream distanceStream(distanceLine);
    string singleTime, singleDistance, timeName, distanceName, time, distance;

    timeStream >> singleTime; distanceStream >> singleDistance;
    while(timeStream >> singleTime && distanceStream >> singleDistance) {
        time.append(singleTime); distance.append(singleDistance);
    }
    cout << time << " " << distance << endl;
    long count = calculateRecordBreak(stol(time), stol(distance));
    cout << count << endl;
    return 0;
}
