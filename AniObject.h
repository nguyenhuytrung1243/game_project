#pragma once

#include "BaseObject.h"

const int EXP_WIDTH = 50;
const int EXP_HEIGHT = 50;

class AniObject :public BaseObject
{
private:
	int frame_;
	int frame_max_;
	SDL_Rect clip_[10];
public:
	AniObject() { ; }
	~AniObject() { ; }

	void Set_frame_max_(const int& fr) { frame_max_ = fr; }
	int Get_frame_max_() { return frame_max_; }

	void Set_frame(const int& fr) { frame_ = fr; }

	void Set_Clip()
	{
		for (int i = 0; i < frame_max_; i++) {
			clip_[i].x = i * EXP_WIDTH;
			clip_[i].y = 0;
			clip_[i].w = EXP_WIDTH;
			clip_[i].h = EXP_HEIGHT;
		}
	}

	void ShowEx(SDL_Surface* des)
	{
		if (frame_ >= frame_max_) frame_ = 0;
		ApplySurfaceClip(p_object_, des, &clip_[frame_], rect_.x, rect_.y);
	}
};