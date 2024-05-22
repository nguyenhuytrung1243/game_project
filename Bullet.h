#pragma once

#include "BaseObject.h"

#define WIDTH_LUADO 90
#define HEIGHT_LUADO 31

#define WIDTH_LUAXANH 25
#define HEIGHT_LUAXANH 37

#define WIDTH_TRUNGGA 20
#define HEIGHT_TRUNGGA 20


class BulletObject : public BaseObject
{
private:
	int x_val;
	int y_val;
	int tt;

	bool is_move;

	int frame_MAX;

	int frame_;
	SDL_Rect clip_[10];
public:


	BulletObject()
	{
		rect_.x = 0;
		rect_.y = 0;
		rect_.w = 0;
		rect_.h = 0;
		x_val = 0;
		y_val = 0;

		tt = 0;

		is_move = false;

		frame_MAX = 0;

		frame_ = -1;
	}
	~BulletObject() { ; }

	void Set_frame_max(const int& x) { frame_MAX = x; }

	void SetClip() {
		for (int i = 0; i < frame_MAX; i++) {
			clip_[i].x = i * rect_.w;
			clip_[i].y = 0;
			clip_[i].w = rect_.w;
			clip_[i].h = rect_.h;
		}
	}
	void Set_tt(const int& t) { tt = t; }

	bool get_is_move() const { return is_move; }
	void set_is_move(const bool& is_move_) { is_move = is_move_; }


	void SetWidthHeight(const int& width, const int& height) {
		rect_.w = width;
		rect_.h = height;
	}

	void set_x_val(const int& val) { x_val = val; }
	void set_y_val(const int& val) { y_val = val; }

	int get_x_val()const { return x_val; }
	int get_y_val()const { return y_val; }

	int Get_frame_() { return frame_; }
	void Set_frame(const int& frame) { frame_ = frame; }

	void ShowEx(SDL_Surface* des)
	{
		if (frame_ >= frame_MAX) frame_ = 0;
		ApplySurfaceClip(p_object_, des, &clip_[frame_], rect_.x, rect_.y);
	}


	void HandleMoveDownToUp(const SDL_Rect& re) {
		if (re.x + re.w / 2 - 15 > rect_.x) {
			rect_.x += x_val;
		}
		else if (re.x + re.w / 2 + 15 < rect_.x) {
			rect_.x -= x_val;
		}
		if (re.y + re.h / 2 - 15 > rect_.y) {
			rect_.y += y_val;
		}
		else if (re.y + re.h / 2 + 15 < rect_.y) {
			rect_.y -= y_val;
		}
		if (CheckCollision(rect_, re))
		{
			is_move = false;
		}
	}

	void HandleMoveUpToDown() {
		rect_.y += y_val;
		if (rect_.y >= 520 - HEIGHT_TRUNGGA) {
			is_move = false;
		}
	}

	void HandleMove()
	{
		rect_.x += x_val * tt;
		if (rect_.x <= 0 || rect_.x >= SCREEN_WIDTH) {
			is_move = false;
		}
	}
};