# TTY-Timed
A simple TUI timer and stopwatch script made for Linux 

### How to use (currently)

```bash
git clone https://github.com/SlurpyIsADev/TTY-Timed.git
cd TTY-Timed || cd TTY-Timed-main 
gcc tty-timed.c Font/default-font.c -lncurses -o tty-timed -DCOMMIT="\"$(git rev-parse HEAD)\"" \ 
#skip the command below if you don't want to run it
# you can do "stopwatch", "timer", or "random" for the first argument
./tty-timed random