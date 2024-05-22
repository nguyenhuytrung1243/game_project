#pragma once

#include "BaseObject.h"

const int& WIDTH_HP_NHANVAT = 1;
const int& HEIGHT_HP_NHANVAT = 8;

const int& WIDTH_HP_BOSS = 3;
const int& HEIGHT_HP_BOSS = 15;

class PlayerPower :public BaseObject
{
private:
	int number_;
	vector<int> pos_list_;

public:
	PlayerPower() {
		number_ = 0;
		rect_.x = 0;
		rect_.y = 0;
		rect_.w = 0;
		rect_.h = 0;
	}
	~PlayerPower() {

	}
	void Set_number_(const int& num) { number_ = num; }
	int Get_number_() { return number_; }

	void AddPos(const int& xpos) { pos_list_.push_back(xpos); }

	void Render(SDL_Surface* des, const SDL_Rect re)
	{
		if (number_ = pos_list_.size())
		{
			for (int i = 0; i < pos_list_.size(); i++)
			{
				rect_.x = pos_list_.at(i) + re.x - 20;
				rect_.y = re.y - rect_.h;
				Show(des);
			}
		}
	}

	void Render(SDL_Surface* des)
	{
		if (number_ = pos_list_.size())
		{
			for (int i = 0; i < pos_list_.size(); i++)
			{
				rect_.x = pos_list_.at(i);
				Show(des);
			}
		}
	}


	void Init(const char* str, const int& n)
	{
		LoadImg(str);

		if (pos_list_.size() > 0)
		{
			pos_list_.clear();
		}

		for (int i = 0; i < number_; i++) {
			AddPos(i * n);
		}
	}

	void Tang()
	{
		number_++;
		pos_list_.push_back((pos_list_.size()) * 40);
	}

	void Decrease()
	{
		number_--;
		pos_list_.pop_back();
	}
};