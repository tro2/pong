#pragma once
#include <SDL.h>

class LTimer
{
public:
	LTimer();

	// clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	// get the timer's current time
	Uint32 getTicks() const;

	// status checks
	bool isStarted();
	bool isPaused();

private:
	// time when started
	Uint32 mStartTicks;

	// ticks stored when paused
	Uint32 mPausedTicks;

	// status
	bool mPaused;
	bool mStarted;
};
