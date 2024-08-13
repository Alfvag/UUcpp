#include <iostream> 
using namespace std;

int main() {
    int startNum = 0;
    int startNumBest = 0;
    int competitors = 0;
    int hrStart, minStart, secStart = 0;
    int hrEnd, minEnd, secEnd = 0;
    int hrBest, minBest, secBest = 0;
    int currHrs, currMins, currSecs = 0;
    float timeCurr = 0.0;
    float timeBest = 0.0;
    bool shouldContinue = true;

    while (shouldContinue) {
        cout << "Start number?";
        cin >> startNum;
        
        if (startNum < 1) {
            shouldContinue = false;
        } else {
            ++competitors; 

            cout << "Start time?";
            cin >> hrStart >> minStart >> secStart;

            cout << "End time?";
            cin >> hrEnd >> minEnd >> secEnd;

            currHrs = (hrEnd - hrStart) - 1;
            currMins = ((60 - minStart) + minEnd);
            currSecs =((60 - secStart) + secEnd);

            if (currSecs >= 60) {
                currSecs -= 60;
                ++currMins; 
            }

            if (currMins >= 60) {
                currMins -= 60;
                ++currHrs;
            }

            timeCurr = ((float(currHrs * 60.0)) + (float(currMins)) + (1.0 * (float(currSecs) / 60.0)));

            if (competitors == 1) {
                timeBest = timeCurr;
            } else if (competitors > 1) {
                if (timeCurr < timeBest) {
                    timeBest = timeCurr;
                    startNumBest = startNum;
                    hrBest = currHrs;
                    minBest = currMins;
                    secBest = currSecs;
                }
            }
        }

    }

    if (competitors < 1) {
        cout << "No competitors" << endl;
    } else if (competitors >= 1) {
        cout << "Winner is starting number: " << startNumBest << endl;
        cout << "Hour: " << hrBest << " Min: " << minBest << " Sec: " << secBest << endl;
        cout << "Number of competitors: " << competitors << endl;
    }

    cout << "The program ends" << endl; 

    return 0; 
}