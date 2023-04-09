#include "LTimer.h"

LTimer::LTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	if (mStarted)
	{
		mStartTicks = 0;
		mPausedTicks = 0;
		mStarted = false;
		mPaused = false;
	}
}

void LTimer::pause()
{
	if (mStarted && !mPaused)
	{
		// pause
		mPaused = true;
		
		// get paused time
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	if (mStarted && mPaused)
	{
		// unpause
		mPaused = false;
		
		// reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		// reset paused ticks
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks() const
{
	// actual total time elapsed
	Uint32 time = 0;

	// if running
	if (mStarted)
	{
		if (mPaused)
		{
			// return the ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			// return elapsed time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	return mStarted;
}

bool LTimer::isPaused()
{
	return mPaused && mStarted;
}