

/******************** TIMER **********************/


#include <bits/stdc++.h>
#include <iomanip>
#include <unistd.h>
using namespace std;

int hours = 0; // hours of timer
int minutes = 0; // minutes of timer
int seconds = 0; // seconds of timer

void displayClock() { // displays the ticking clock
    system("clear");
    cout << setfill(' ') << setw(55) << "         TIMER         \n";
    cout << setfill(' ') << setw(55) << " --------------------------\n";
    cout << setfill(' ') << setw(29);
    cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
    cout << setfill('0') << setw(2) << minutes << " min | ";
    cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
    cout << setfill(' ') << setw(55) << " --------------------------\n";
} 
void timer() {
    while (1) {
        displayClock();
        sleep(1);
        seconds ++;
        if (seconds == 60) {
            minutes ++;
            if (minutes == 60) {
                hours ++;
                minutes = 0;
            }
            seconds = 0;
        }
    }
}
int main() {
    timer();
    return 0;
}
