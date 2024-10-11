#include <iostream>

#include "main.hpp"

// C Includes
extern "C" {
    #include "test/dpibypass.h"
}

using namespace std;

void logResult(const string& stage, int result) {
    if (result == SUCCESFULL_END_RESULT) {
        #ifdef DEBUG
        if (DEBUG) cout << "End of " << stage << ": Success!" << endl;
        #endif
    } else {
        cerr << "Warning: " << stage << " ended with code: " << result << endl;
    }
}

int main() {
    #ifdef DEBUG
    if (DEBUG) cout << "Starting the program..." << endl;
    #endif

    try {
        #ifdef DEBUG
        if (DEBUG) cout << "Start of stage 1: Entering the setup program..." << endl;
        #endif

        const int setup_result = setup();
        logResult("stage 1", setup_result);

        #ifdef DEBUG
        if (DEBUG) cout << "Start of stage 2: Entering the main program..." << endl;
        #endif

        const int mainProgramResult = mainProgram();
        logResult("stage 2", mainProgramResult);

        #ifdef DEBUG
        if (DEBUG) cout << "Start of stage 3: Clearing program memory..." << endl;
        #endif

        const int cleaningResult = clearMem();
        logResult("stage 3", cleaningResult);
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return SUCCESFULL_END_RESULT;
}

int setup() {
    #ifdef DEBUG
    if (DEBUG) cout << "Start of stage 1.1: Application setup..." << endl;
    #endif
    try{

        return SUCCESFULL_END_RESULT;
    }
    catch(exception& e) {
        cerr << e.what() << endl;
        return WARNING_END_RESULT;
    }
}

int clearMem() {
    // Nothing

    return SUCCESFULL_END_RESULT;
}

int mainProgram() {
    #ifdef DEBUG
    if (DEBUG) cout << "Start of stage 2.1: Executing the main program..." << endl;
    #endif
    try{
        mainC();
        
        return SUCCESFULL_END_RESULT;
    }
    catch(exception& e) {
        cerr << e.what() << endl;
        return WARNING_END_RESULT;
    }
}


