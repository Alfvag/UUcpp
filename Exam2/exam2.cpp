#include <iostream>
using namespace std;

int main() {
    int startNum = 0;
    int startNumBest = 0;
    int competitors = 0;
    int hrStart, minStart, secStart = 0;
    int hrEnd, minEnd, secEnd = 0;
    int hrBest, minBest, secBest = 0;
    int currSecs = 0;
    float timeCurr = 0.0;
    float timeBest = 0.0;
    bool shouldContinue = true;

    while (shouldContinue) {
        cout << "Start number? ";
        cin >> startNum;

        // Break loop if start number is below 1
        if (startNum < 1) {
            shouldContinue = false;
        } else {
            ++competitors;

            cout << "Start time? ";
            cin >> hrStart >> minStart >> secStart;

            cout << "End time? ";
            cin >> hrEnd >> minEnd >> secEnd;

            // Convert start and end times to total seconds from midnight
            int startTotalSecs = (hrStart * 3600) + (minStart * 60) + secStart;
            int endTotalSecs = (hrEnd * 3600) + (minEnd * 60) + secEnd;

            // If end time is less than start time, add 24 hours to the end time
            if (endTotalSecs < startTotalSecs) {
                endTotalSecs += 86400;  // 24 * 3600
            }

            currSecs = endTotalSecs - startTotalSecs;

            // Convert seconds back to hours, minutes, seconds
            int currHrs = currSecs / 3600;
            currSecs %= 3600;
            int currMins = currSecs / 60;
            currSecs %= 60;

            // Calculate time in minutes in order to compaare times
            timeCurr = (currHrs * 60.0) + currMins + (float(currSecs) / 60.0);

            // Compare times and push if new best
            if (competitors == 1 || timeCurr < timeBest) {
                timeBest = timeCurr;
                startNumBest = startNum;
                hrBest = currHrs;
                minBest = currMins;
                secBest = currSecs;
            }
        }
    }

    // Check if there are any competitors and announce winner
    if (competitors < 1) {
        cout << "No competitors" << endl;
    } else {
        cout << "Winner is starting number: " << startNumBest << endl;
        cout << "Hour: " << hrBest << " Min: " << minBest << " Sec: " << secBest << endl;
        cout << "Number of competitors: " << competitors << endl;
    }

    cout << "The program ends" << endl;

    return 0;
}