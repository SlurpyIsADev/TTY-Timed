# TTY-Timed
A simple TUI timer and stopwatch script made for Linux 

This script is currently in testing, bugs are to be expected

### How to build

```bash
git clone https://github.com/SlurpyIsADev/TTY-Timed.git
cd TTY-Timed || cd TTY-Timed-main 
gcc tty-timed.c Font/default-font.c -lncurses -o tty-timed -DCOMMIT="\"$(git rev-parse HEAD)\"" 
#skip the command below if you don't want to run it
# you can do "stopwatch", "timer", or "random" for the first argument
./tty-timed random
```

### Usage
```bash
A simple TUI timer and stopwatch made in C

Usage:
   tty-timed [TYPE OPTIONS...] [OPTIONS...]

Type Options [TYPE OPTIONS...]:
   stopwatch
   timer
   random    Randomly picks either Timer or Stopwatch

Time Options [OPTIONS...]:
   -S --seconds    Adds the inputted amount of seconds    Ex: [tty-timed timer -S 40] (Output: 00:40)
   -M --minutes    Adds the inputted amount of minutes    Ex: [tty-timed timer -M 5] (Output: 05:00)
   -H --hours      Adds the inputted amount of hours      Ex: [tty-timed timer -H 6] (Output: 06:00:00)

Customization Options [OPTIONS...]:
   -n --name       Adds your input above the timer/stopwatch
   --run           runs an inputted console command. Please read additional notes before use
   -p --canpause   Enables or disables the ability to pause using either 1 (for can pause) or 0 (for can not pause) as input   Default: can pause
   -c --iscentered Centers or uncenters the timer using either 1 (for centered) or 0 (for not centered) as input               Default: centered

   -C --color      Changes the color of the timer/stopwatch
      Usage of color:
         --color [COLOR OPTIONS] [COLOR] or -c [COLOR OPTIONS...]
      Color Options [COLOR OPTIONS...]:
         direct     uses values 1-1000 for red, green, and blue    Ex: [tty-timed timer -S 40 -C direct 1000 0 0] (Output but imagine it's red: 00:40)
         rgb        uses values 1-255 for red, green, and blue     Ex: [tty-timed timer -S 40 -C rgb 0 255 0] (Output but imagine it's blue: 00:40)
         hex        uses a hex value without the # for color       Ex: [tty-timed timer -S 40 -C hex 00ff00] (Output but imagine it's green: 00:40)

Other Options:
   -v --version    Prints the version and commit it was made on
   -d --debug      Prints some addtional infomation for debug
   -h --help       Prints this screen
```

### Notes
```bash
Additional notes:
   Parsing is case sensitive, meaning make sure capitals are correct. Ex: [tty-timed timer -h 6] (Output: This help function) vs [tty-timed timer -H 6] (Output: 06:00:00)

   Backup button "X":
     Since "Ctrl+C" in this script doesn't actually kill the script, the backup kill button is "X". Press "X" and it will stop the script instantly without running the command if one is set.
     "Ctrl+C" will still stop the script if no command is set.
     The "X" key is specific cases, here is an example case: [tty-timed stopwatch --run forever.sh] where "forever.sh" is just [tty-timed stopwatch --run forever.sh].

   Run command info below (--run):
     The run command will execute at the end of a timer or when the program is interrupted (Ctrl+C).
     The run command should placed at the end of the args because it records every arg after it. So, [--run sometermcommand -M 5] would run "sometermcommand" with the argument "-M 5"
     In the run command, if you put "%" and then with no space your inputted name, it will output the absolute seconds. Meaning 1:30 will output as 90. See the example below.
     Example: [tty-timed stopwatch -n example --run tty-timed timer -S %example] (Whenever the function is interuptted, a timer will countdown from the time that was on the stopwatch)

   The seconds (-S), minutes (-M), and hours (-H) args are not locked to 60, putting [-S 156] or [-M 90] will work just fine
```