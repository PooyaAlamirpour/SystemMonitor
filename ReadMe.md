## Sytem Monitor

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

In this project, I have implemented a System Monitor application for monitoring CPU and RAM usage, kernel version and some run applications. If you want to run this project, follow below instruction:

1. Clone this repo. ```git clone https://github.com/PooyaAlamirpour/SystemMonitor.git```
2. ```cd SystemMonitor```
3. Make a build directory: ```mkdir build && cd build```
4. Compile: ```cmake .. && make```
5. Run it: ```./monitor```

The result is depicted as below:

![Output](https://github.com/PooyaAlamirpour/SystemMonitor/blob/master/images/Output.png)

If you are eager to modify this project, Just open `System`, `Process`, and `Processor` classes.

## Dependencies
* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
* ncurses library
    * ```sudo apt install libncurses5-dev libncursesw5-dev```

For this project, I have used `ncurses` library. ncurses is a library that facilitates text-based graphical output in the terminal. This project relies on `ncurses` for display output. 