//No clue how to do this

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>
#include <ncurses.h>
#include "Font/default-font.h"

struct args {
	char color;
	char name;
	bool iscentered;
	bool canpause;	
};

struct time {
	int dseconds;
	int dminutes;
	int dhours;
};

int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 0;

//seconds thing for Stopwatch
void stopwatch() {

	//seconds
	seconds++;

	//minutes
	if(seconds == 60){
	seconds = 0;
	minutes++;
	};

	//hours
	if (minutes == 60) {
	minutes = 0;
	hours++;
	};

	//days
	if (hours == 24) {
	hours = 0;
	days++;
	};
}

//formating
const char *format(int num, int x) {
switch (num) {
    case 0:
        return a0[x];
        break;
    case 1:
        return a1[x];
        break;
    case 2:
        return a2[x];
        break;
    case 3:
        return a3[x];
        break;
    case 4:
        return a4[x];
        break;
    case 5:
        return a5[x];
        break;
    case 6:
        return a6[x];
        break;
    case 7:
        return a7[x];
        break;
    case 8:
        return a8[x];
        break;
    case 9:
        return a9[x];
        break;
    default:
        printf("Default case... uh oh");
        break;
    }
    return 0;
}
void display() {
	//initscr();
	printf("\e[1;1H\e[2J");
	sleep(1);
	stopwatch();
	for (int i = 0; i < 5; i++) {
	printf("%s %s %s %s %s\n", format(minutes/10, i), format(minutes%10, i), colon[i], format(seconds/10, i), format(seconds%10, i));
	}
	//refresh();
	//printf("%d\n", seconds);
	//printf("%d\n", minutes);
	//printf("%d\n", hours);
	fflush(stdout);
}

int main() {
	bool x = true;
	while (x) {
		display();
	}
	return 0;	
}
