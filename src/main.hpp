#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

using namespace std;

#define SUCCESFULL_END_RESULT 0         //  A code indicating that the program has completed correctly and without errors.
#define WARNING_END_RESULT -1           //  Code for an error that is not critical.
#define CRITICAL_END_RESULT -2          //  Code for an error that may have critical significance.

#define DISCORD_IP "162.159.138.232"
#define DISCORD_PORT 443

int setup();
int clearMem();
int mainProgram();


#endif