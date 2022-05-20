#pragma once

#include<iostream>
#include<sstream>
#include <SDL.h>

class GTimer
{
public:

    //Initializes variables
    GTimer();

    //The various clock actions
    void start();
    void last();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isLast();
    bool isStarted();
    bool isPaused();

private:

    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool lastRun;
    bool mPaused;
    bool mStarted;
};


