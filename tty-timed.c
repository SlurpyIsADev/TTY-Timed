//No clue how to do this

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <locale.h>
#include <ncurses.h>
#include <sys/ioctl.h>
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
int hours = -1;
int days = 0;
int addedx = 0;

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
		if(hours > -1) {
			hours++;
		}
		else {
			hours = 1;
		}
		if(addedx <= 12) {
			addedx = 9;
		}
	};

	//days
	if (hours == 24) {
		hours = 0;
		days++;
		addedx = 18;
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
	stopwatch();
	for (int i = 0; i < 5; i++) {
		move((get_term_size(false)/2)+i-2,(get_term_size(true)/2)-15-addedx);
		//days
		if(days > 0){printw("%s %s %s",format(days/10, i), format(days%10, i), colon[i]);}
		//hours
		if(hours > -1){printw("%s %s %s",format(hours/10, i), format(hours%10, i), colon[i]);}
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
	setlocale(LC_ALL, "");  
	initscr();
	cbreak();
	noecho();
	bool x = true;
	while (x) {
		display();
	}
	endwin();
	return 0;	
}

