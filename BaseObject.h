#pragma once

#include "common.h"

class BaseObject {

protected:

	SDL_Rect rect_;
	SDL_Surface* p_object_;

public:
	BaseObject() {
		rect_.x = 0;
		rect_.y = 0;
		p_object_ = NULL;
	}

	~BaseObject() {
		if (p_object_ != NULL) {
			SDL_FreeSurface(p_object_);
		}
	}

	void Show(SDL_Surface* des) {
		if (p_object_ != NULL) {
			ApplySurface(p_object_, des, rect_.x, rect_.y);
		}
	}


	bool LoadImg(const char* file_name) {
		p_object_ = LoadImage(file_name);
		if (p_object_ == NULL) {
			return false;
		}
		return true;
	}

	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}
	void SetRectAll(const int& x, const int& y, const int& w, const int& h) {
		rect_.x = x;
		rect_.y = y;
		rect_.w = w;
		rect_.h = h;
	}

	void SetRectX(const int& x) { rect_.x = x; }
	void SetRectY(const int& y) { rect_.y = y; }

	SDL_Rect GetRect() const {
		return rect_;
	}

	SDL_Surface* GetObject() {
		return p_object_;
	}

};
