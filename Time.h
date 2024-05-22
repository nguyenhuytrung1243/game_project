#pragma once

#include "common.h"


class ImpTimer {
private:
	int started_tick_;
	int paused_tick_;

	bool is_started_;
	bool is_paused_;

public:
	ImpTimer()
	{
		started_tick_ = 0;
		paused_tick_ = 0;
		is_started_ = false;
		is_paused_ = false;
	}

	~ImpTimer() { ; }

	void start()
	{
		is_started_ = true;
		is_paused_ = false;
		started_tick_ = SDL_GetTicks();
	}
	void stop()
	{
		is_paused_ = false;
		is_started_ = false;
	}
	void paused() {
		if (is_started_ == true && is_paused_ == false)
		{
			is_paused_ = true;
			paused_tick_ = SDL_GetTicks() - started_tick_;
		}
	}
	void unpaused()
	{
		if (is_paused_ == true)
		{
			is_paused_ = false;
			started_tick_ = SDL_GetTicks() - paused_tick_;
			paused_tick_ = 0;
		}
	}

	int get_ticks()
	{
		if (is_started_ == true)
		{
			if (is_paused_ == true)
			{
				return paused_tick_;
			}
			else return SDL_GetTicks() - started_tick_;
		}
		return 0;
	}

	bool is_started() { return is_started_; }
	bool is_paused() { return is_paused_; }
};