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
#include <ctype.h>
#include <signal.h>
#include "Font/default-font.h"

#ifndef COMMIT
#define COMMIT "unknown"
#endif


bool usingcolors = false; 
struct dRGB {
	int r;
	int g;
	int b;
};
char* name = "";
char command[256] = "";
int system(const char *command);
int comi = 0;
int comabseconds = 0;
bool iscentered = true;
bool canpause = true;
bool ispaused = false;
bool debugmode = false;


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
        printw("Default case... you broke it :(");
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

void help() {
	printf("A simple TUI timer and stopwatch made in C\n");
	printf("\n");
	printf("Usage:\n");
	printf("   tty-timed [TYPE OPTIONS...] [OPTIONS...]\n");
	printf("\n");
	
	printf("Type Options [TYPE OPTIONS...]:\n");
	printf("   stopwatch\n");
	printf("   timer\n");
	printf("   random    Randomly picks either Timer or Stopwatch\n");
	printf("\n");

	printf("Time Options [OPTIONS...]:\n");
	printf("   -S --seconds    Adds the inputted amount of seconds    Ex: [tty-timed timer -S 40] (Output: 00:40)\n");
	printf("   -M --minutes    Adds the inputted amount of minutes    Ex: [tty-timed timer -M 5] (Output: 05:00)\n");
	printf("   -H --hours      Adds the inputted amount of hours      Ex: [tty-timed timer -H 6] (Output: 06:00:00)\n");
	printf("\n");

	printf("Customization Options [OPTIONS...]:\n");
	printf("   -n --name       Adds your input above the timer/stopwatch\n");
	printf("   --run           runs an inputted console command. Please read additional notes before use\n");
	printf("   -p --canpause   Enables or disables the ability to pause using either 1 (for can pause) or 0 (for can not pause) as input   Default: can pause\n");
	printf("   -c --iscentered Centers or uncenters the timer using either 1 (for centered) or 0 (for not centered) as input               Default: centered\n");
	printf("\n");
	printf("   -C --color      Changes the color of the timer/stopwatch\n");
	printf("      Usage of color:\n");
	printf("         --color [COLOR OPTIONS] [COLOR] or -c [COLOR OPTIONS...]\n");
	printf("      Color Options [COLOR OPTIONS...]:\n");
	printf("         direct     uses values 1-1000 for red, green, and blue    Ex: [tty-timed timer -S 40 -C direct 1000 0 0] (Output but imagine it's red: 00:40)\n");
	printf("         rgb        uses values 1-255 for red, green, and blue     Ex: [tty-timed timer -S 40 -C rgb 0 255 0] (Output but imagine it's blue: 00:40)\n");
	printf("         hex        uses a hex value without the # for color       Ex: [tty-timed timer -S 40 -C hex 00ff00] (Output but imagine it's green: 00:40)\n");
	printf("\n");

	printf("Other Options:\n");
	printf("   -v --version    Prints the version and commit it was made on\n");
	printf("   -d --debug      Prints some addtional infomation for debug\n");
	printf("   -h --help       Prints this screen\n");
	printf("\n");

	printf("Additional notes:\n");
	printf("   Parsing is case sensitive, meaning make sure capitals are correct. Ex: [tty-timed timer -h 6] (Output: This help function) vs [tty-timed timer -H 6] (Output: 06:00:00)\n");
	printf("\n");
	printf("   Backup button \"X\":\n");
	printf("     Since \"Ctrl+C\" in this script doesn't actually kill the script, the backup kill button is \"X\". Press \"X\" and it will stop the script instantly without running the command if one is set.\n");
	printf("     \"Ctrl+C\" will still stop the script if no command is set.\n");
	printf("     The \"X\" key is specific cases, here is an example case: [tty-timed stopwatch --run forever.sh] where \"forever.sh\" is just [tty-timed stopwatch --run forever.sh].\n");
	printf("\n");
	printf("   Run command info below (--run):\n");
	printf("     The run command will execute at the end of a timer or when the program is interrupted (Ctrl+C).\n");
	printf("     The run command should placed at the end of the args because it records every arg after it. So, [--run sometermcommand -M 5] would run \"sometermcommand\" with the argument \"-M 5\"\n");
	printf("     In the run command, if you put \"%%\" and then with no space your inputted name, it will output the absolute seconds. Meaning 1:30 will output as 90. See the example below.\n");
	printf("     Example: [tty-timed stopwatch -n example --run tty-timed timer -S %%example] (Whenever the function is interuptted, a timer will countdown from the time that was on the stopwatch)\n");
	printf("\n");
	printf("   The seconds (-S), minutes (-M), and hours (-H) args are not locked to 60, putting [-S 156] or [-M 90] will work just fine\n");
}

void display() {
	if (strlen(name) != 0){
		if(iscentered){
			move((get_term_size(false)/2)-4,(get_term_size(true)/2)-(strlen(name)/2)+1);
		}
		printw("%s\n", name);
	}

	for (int i = 0; i < 5; i++) {
		if(iscentered){
			move((get_term_size(false)/2)+i-2,(get_term_size(true)/2)-15-addedx);
		}
		//days
		if(days > 0){printw("%s %s %s ",format(days/10, i), format(days%10, i), colon[i]);}
		//hours
		if(hours > 0 || days > 0){printw("%s %s %s ",format(hours/10, i), format(hours%10, i), colon[i]);}
		//minutes and seconds
		printw("%s %s %s %s %s", format(minutes/10, i), format(minutes%10, i), colon[i], format(seconds/10, i), format(seconds%10, i));
		//new line
		printw("\n");
	}

	//pausing stuff
	if (ispaused){
		if(iscentered){
			move((get_term_size(false)/2)+4,(get_term_size(true)/2)-2);
		}
		printw("PAUSED");
	}
	refresh();
}

void CtrlCHandler(int dummy) {
	comabseconds = abseconds;
	abseconds = -999;
}

int main(int argc, char *argv[]) {
	//if there are no args, return the help screen
	if(argc == 1){
		help();
		return 0;
	}

	//setup vars
	srand(time(NULL));
	void (*LogicFunc)();
	int skiparg = 0;
	struct dRGB rgbColor;

	//main loop
	for (int i = 1; i < argc; i++) {
		if (skiparg == 0) {
			//version
			if((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0)) {
				printf("0.9.0\n");
				if(COMMIT != "") {
				printf("Built at commit %s\n", COMMIT);
				}
				return 0;
			}

			//debug
			else if((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--debug") == 0)) {
				debugmode = true;
			}

			//seconds added
			else if((strcmp(argv[i], "-S") == 0) || (strcmp(argv[i], "--seconds") == 0)) {
				skiparg++;
				seconds = atoi(argv[i+1]);
			}

			//minutes added
			else if((strcmp(argv[i], "-M") == 0) || (strcmp(argv[i], "--minutes") == 0)) {
				skiparg++;
				minutes = atoi(argv[i+1]);
			}

			//hours added
			else if((strcmp(argv[i], "-H") == 0) || (strcmp(argv[i], "--hours") == 0)) {
				skiparg++;
				hours = atoi(argv[i+1]);
			}

			//centered
			else if((strcmp(argv[i], "-c") == 0) || (strcmp(argv[i], "--iscentered") == 0)) {
				skiparg++;
				if(atoi(argv[i+1]) == 0){
					iscentered = false;
				}
				else if(atoi(argv[i+1]) == 1) {
					iscentered = true;
				}
				else {
					printf("Unrecognized option '%s', please use either 1 (for true) or 0 (for false): \n", argv[i+1]);
					help();
					return 0;
				}
			}
			
			//pausing
			else if((strcmp(argv[i], "-p") == 0) || (strcmp(argv[i], "--canpause") == 0)) {
				skiparg++;
				if(atoi(argv[i+1]) == 0){
					canpause = false;
				}
				else if(atoi(argv[i+1]) == 1) {
					canpause = true;
				}
				else {
					printf("Unrecognized option '%s', please use either 1 (for true) or 0 (for false): \n", argv[i+1]);
					help();
					return 0;
				}
			}

			//help
			else if((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
				help();
				return 0;
			}

			//color
			else if((strcmp(argv[i], "-C") == 0) || (strcmp(argv[i], "--color") == 0)) {
				usingcolors = true;
				skiparg++;
				if ((strcmp(argv[i+1], "direct") == 0)) {
					skiparg += 3;
					rgbColor.r = atoi(argv[i+2]);
					rgbColor.g = atoi(argv[i+3]);
					rgbColor.b = atoi(argv[i+4]);

				}
				else if ((strcmp(argv[i+1], "rgb") == 0)) {
					skiparg += 3;
					rgbColor.r = (int)(atoi(argv[i+2])*3.9215686274509802);
					rgbColor.g = (int)(atoi(argv[i+3])*3.9215686274509802);
					rgbColor.b = (int)(atoi(argv[i+4])*3.9215686274509802);

				}
				else if ((strcmp(argv[i+1], "hex") == 0)) {
					skiparg++;
					char hex[6];
					int h[6];
					strcpy(hex, argv[i+2]);
					for (int i = 0; i < 6; i++) {
						if(isdigit(hex[i])){
							h[i] = hex[i] - '0';
							//printf("Digit ");
						}
						else {
							h[i] = (int)(tolower(hex[i]) - 'a' + 10);
							//printf("No Digit ");
						}
						//printf("On iteration %d: %d\n", i, h[i]);
					}
					rgbColor.r = ((h[0]*16) + h[1])*3.9215686274509802;
					rgbColor.g = ((h[2]*16) + h[3])*3.9215686274509802;
					rgbColor.b = ((h[4]*16) + h[5])*3.9215686274509802;
					//This was painful for someone who doesn't use c
				}
				//printf("%d, %d, %d\n", rgbColor.r, rgbColor.g, rgbColor.b);
				//return 0;
			}
			
			else if((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--name") == 0)) {
				skiparg++;
				name = argv[i+1];
			}
			else if((strcmp(argv[i], "--run") == 0)) {
				skiparg =  argc-i;
				comi = i;
			}

			//Unrecongized option
			else if(argv[i] != NULL && i != 1) {
				printf("Unrecognized option '%s', here is some help: \n", argv[i]);
				help();
				return 0;
			}
		}
		else {
			skiparg--;
		}
    }

	//stopwatch (obv)
	if(strcmp(argv[1], "stopwatch") == 0){
		LogicFunc = &stopwatch;
	}

	//timer (obv)
	else if(strcmp(argv[1], "timer") == 0){
		LogicFunc = &timer;
	}

	//random (obv)
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
		help();
		fflush(stdout);
		return 0;
	}

	//Display and Logic
	setlocale(LC_ALL, "");  
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	signal(SIGINT, CtrlCHandler);
	if (usingcolors && has_colors()){
		use_default_colors();
		start_color();
		init_color(COLOR_WHITE, rgbColor.r, rgbColor.g, rgbColor.b);
		init_pair(1, COLOR_WHITE, -1);
		attron(COLOR_PAIR(1));
	}
	bool x = true;
	abseconds = (days * 86400) + (hours * 3600) + (minutes * 60) + seconds;
	while (abseconds >= 0 && abseconds < 8640000) {
		if(ispaused == false) {
			timeMath();
			display();
			timeout(0);
			sleep(1);
			if (getch() == 32 && canpause) {
				ispaused = true;
			}
			else if (getch() == 120) {
				endwin();
				return 0;
			}
			(*LogicFunc)();
			flushinp();
			erase();
		}
		else {
			display();
			timeout(1000);
			if (getch() == 32) {
				ispaused = false;
			} 
			else if (getch() == 120) {
				endwin();
				return 0;
			}
			erase();
		}
		if (debugmode){
				//Debug stuff
				printw("Days: %d Hours: %d Minutes: %d Seconds: %d\n",days,hours,minutes,seconds);
				printw("Absolute Seconds: %d\n",abseconds);
				printw("Is Paused: %d\n",ispaused);
				refresh();
			}
	}
	endwin();

	//if this doesn't work when i commit, it's because it decides when it if it wants to work or not
		if(comi != 0) {
			char target[strlen(name)+1];
			sprintf(target, "%s%s","%",name);
			char secondsSTR[20];
			sprintf(secondsSTR, "%d", comabseconds);
			for (int f = 1; f < argc-comi; f++) {
				if (strcmp(argv[f+comi], target) == 0) {
					strcat(command, secondsSTR);
				}
				else {
					strcat(command, argv[f+comi]);
					//printf("Argv: %s\nTarget: %s\n", argv[f+comi], target);
				}
				strcat(command, " ");
			}
			printf("Running: %s\n", command);
			system(command);
		}
	return 0;	
}