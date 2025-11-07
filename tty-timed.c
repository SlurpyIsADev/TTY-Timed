//No clue how to do this

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <time.h>
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

int abseconds = 0;
int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 0;


int addedx = 0;

void timeMath(){
	//logic
	seconds = abseconds%60;
	minutes = (abseconds%3600)/60;
	hours = (abseconds/3600)%24;
	days = abseconds/86400;

	if(days > 0){
		addedx = 18;
	}
	else if(hours > 0){
		addedx = 9;
	}
	else{
		addedx = 0;
	}
}

//seconds thing for Stopwatch
void stopwatch() {
	abseconds++;
}

void timer() {
	abseconds--;
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
        printw("Default case... uh oh");
        break;
    }
    return 0;
}
unsigned get_term_size(bool get_term_width) {
    struct winsize ws;

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == 0 ||
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 ||
        ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == 0) {
        return get_term_width ? ws.ws_col : ws.ws_row;
    }

    return 0;
}
void display() {
	for (int i = 0; i < 5; i++) {
		move((get_term_size(false)/2)+i-2,(get_term_size(true)/2)-15-addedx);
		//days
		if(days > 0){printw("%s %s %s",format(days/10, i), format(days%10, i), colon[i]);}
		//hours
		if(hours > 0 || days > 0){printw("%s %s %s",format(hours/10, i), format(hours%10, i), colon[i]);}
		//minutes and seconds
		printw("%s %s %s %s %s", format(minutes/10, i), format(minutes%10, i), colon[i], format(seconds/10, i), format(seconds%10, i));
		//new line
		printw("\n");
	}
	refresh();
	sleep(1);
	erase();
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	void (*LogicFunc)();
	if(strcmp(argv[1], "stopwatch") == 0){
		LogicFunc = &stopwatch;
	}
	else if(strcmp(argv[1], "timer") == 0){
		LogicFunc = &timer;
	}
	else if(strcmp(argv[1], "random") == 0){
		if(rand()%2 == 1){
			LogicFunc = &stopwatch;
		}
		else{
			LogicFunc = &timer;
		}
	}
	else{
		printf("Unrecognized option '%s', please use either 'stopwatch', 'timer', or 'random' for the first argument.\n", argv[1]);
		fflush(stdout);
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		
    }

	//Display and Logic
	setlocale(LC_ALL, "");  
	initscr();
	cbreak();
	noecho();
	bool x = true;
	abseconds = (days * 86400) + (hours * 3600) + (minutes * 60) + seconds;
	while (abseconds >= 0) {
		timeMath();
		//printw("Days: %d Hours: %d Minutes: %d Seconds: %d\n",days,hours,minutes,seconds);
		//printw("Absolute Seconds: %d\n",abseconds);
		//refresh(); //Debug stuff
		display();
		(*LogicFunc)();
	}
	endwin();
	return 0;	
}

