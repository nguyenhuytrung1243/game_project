#pragma once


#include "BaseObject.h"
#include "Bullet.h"

#define WIDTH_THREATS 40
#define HEIGHT_THREATS 40
const int frame_max = 3;


class ThreatsObject :public BaseObject
{
private:
	int x_val_;
	int y_val_;
	int x_vitri;

	vector<BulletObject*> p_bullet_list_;

	int frame_;
	SDL_Rect clip_[frame_max];
	int I;
	int J;
public:
	ThreatsObject() {

		x_val_ = 0;
		y_val_ = 0;
		x_vitri = 4 * SCREEN_WIDTH;

		rect_.x = 4 * SCREEN_WIDTH;
		rect_.y = 520 - HEIGHT_THREATS;
		rect_.w = WIDTH_THREATS;
		rect_.h = HEIGHT_THREATS;

		I = 0;
		J = 0;
		frame_ = -1;
		for (int i = 0; i < frame_max; i++) {
			clip_[i].x = i * WIDTH_THREATS;
			clip_[i].y = 0;
			clip_[i].w = WIDTH_THREATS;
			clip_[i].h = HEIGHT_THREATS;
		}
	}
	~ThreatsObject() {
		if (p_bullet_list_.size() > 0)
		{
			for (int i = 0; i < p_bullet_list_.size(); i++) {
				BulletObject* p_bullet = p_bullet_list_.at(i);
				if (p_bullet)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
			p_bullet_list_.clear();
		}
	}
	vector<BulletObject*> Get_bullet_list() { return p_bullet_list_; }

	void Set_x_val(const int& x) { x_val_ = x; }
	void Set_y_val(const int& y) { y_val_ = y; }
	void Set_x_vitri(const int& vitri) { x_vitri = vitri; }
	void Set_frame(const int& frame) { frame_ = frame; }

	int Get_x_val() { return x_val_; }
	int Get_y_val() { return y_val_; }
	int Get_x_vitri() { return x_vitri; }

	int Get_frame_() { return frame_; }

	void ShowEx(SDL_Surface* des)
	{
		if (frame_ >= frame_max) frame_ = 0;
		ApplySurfaceClip(p_object_, des, &clip_[frame_], rect_.x, rect_.y);
	}
	void HandleMove(int x_vantoc) {
		x_vitri -= x_val_;

		if (x_vitri <= x_vantoc + DIEMBATDAU - 100) {
			x_val_ = -TOCDOTHREATS1;
			LoadImg("ma_right.png");
		}
		else if (x_vitri >= x_vantoc + DIEMBATDAU + 100) {
			x_val_ = TOCDOTHREATS1;
			LoadImg("ma_left.png");
		}
	}
	void animation(SDL_Surface* des, int x_vantoc, const SDL_Rect& re) {
		Set_frame((I++) % frame_max);
		HandleMove(x_vantoc);
		if (x_vitri > x_vantoc + DIEMBATDAU - 300 && x_vitri < x_vantoc + DIEMBATDAU + 300) {
			LoadImg("ma_.png");
			Show(des);
		}
		else {
			ShowEx(des);
		}
		MakeBullet(des, x_vantoc, re);
	}
	void InitBullet(BulletObject* p_bullet) {
		if (p_bullet) {
			bool bo = p_bullet->LoadImg("luaxanh.png");
			if (bo) {
				p_bullet->set_is_move(false);
				p_bullet->SetWidthHeight(WIDTH_LUAXANH, WIDTH_LUAXANH);
				p_bullet->Set_frame_max(4);
				p_bullet->SetRect(rect_.x + rect_.w / 2, rect_.y);
				p_bullet->set_x_val(20);
				p_bullet->set_y_val(20);
				p_bullet->SetClip();
				p_bullet_list_.push_back(p_bullet);
			}
		}
	}
	void MakeBullet(SDL_Surface* des, int x_vantoc, const SDL_Rect& re)
	{
		for (int i = 0; i < p_bullet_list_.size(); i++) {
			BulletObject* p_bullet = p_bullet_list_.at(i);
			if (p_bullet)
			{
				if (p_bullet->get_is_move())
				{
					p_bullet->Set_frame((J++) % 4);
					p_bullet->ShowEx(des);
					p_bullet->HandleMoveDownToUp(re);
				}
				else if (x_vitri > x_vantoc + DIEMBATDAU - 300 && x_vitri < x_vantoc + DIEMBATDAU + 300)
				{
					p_bullet->set_is_move(true);
					p_bullet->SetRect(rect_.x + rect_.w / 2, rect_.y);
				}
				else {
					p_bullet->SetRect(rect_.x + rect_.w / 2, rect_.y);
				}
			}
		}
	}
};


#define WIDTH_THREATS_ 87
#define HEIGHT_THREATS_ 51
const int _frame_max = 4;

class ThreatsObject_ :public BaseObject
{
private:
	int x_val_;
	int y_val_;
	int x_vitri;

	vector<BulletObject*> p_bullet_list_;

	int frame_;
	SDL_Rect clip_[_frame_max];
public:
	ThreatsObject_() {
		x_val_ = 0;
		y_val_ = 0;
		x_vitri = 4 * SCREEN_WIDTH;

		rect_.x = 4 * SCREEN_WIDTH;
		rect_.y = 0;
		rect_.w = WIDTH_THREATS_;
		rect_.h = HEIGHT_THREATS_;

		frame_ = -1;
		for (int i = 0; i < _frame_max; i++) {
			clip_[i].x = i * WIDTH_THREATS_;
			clip_[i].y = 0;
			clip_[i].w = WIDTH_THREATS_;
			clip_[i].h = HEIGHT_THREATS_;
		}
	}
	~ThreatsObject_() {
		if (p_bullet_list_.size() > 0)
		{
			for (int i = 0; i < p_bullet_list_.size(); i++) {
				BulletObject* p_bullet = p_bullet_list_.at(i);
				if (p_bullet)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
			p_bullet_list_.clear();
		}
	}
	vector<BulletObject*> Get_bullet_list() { return p_bullet_list_; }

	void Set_x_val(const int& x) { x_val_ = x; }
	void Set_y_val(const int& y) { y_val_ = y; }
	void Set_x_vitri(const int& vitri) { x_vitri = vitri; }
	void Set_frame(const int& frame) { frame_ = frame; }

	int Get_x_val() { return x_val_; }
	int Get_y_val() { return y_val_; }
	int Get_x_vitri() { return x_vitri; }
	int Get_frame_() { return frame_; }


	void ShowEx(SDL_Surface* des)
	{
		if (frame_ >= frame_max) frame_ = 0;
		ApplySurfaceClip(p_object_, des, &clip_[frame_], rect_.x, rect_.y);
	}
	void HandleMove(const int& x_vantoc, const int& y_vantoc) {
		x_vitri -= x_val_;
		if (x_vitri <= 0) {
			x_val_ = -TOCDOTHREATS2;
			LoadImg("chim_right.png");
		}
		else if (x_vitri >= WIDTH_BACKGROUND) {
			x_val_ = TOCDOTHREATS2;
			LoadImg("chim_left.png");
		}
		rect_.y += y_val_;
		if (y_vantoc > rect_.y) {
			y_val_ = 1;
		}
		else if (y_vantoc < rect_.y) {
			y_val_ = -1;
		}
	}
	void HandleMove() {
		x_vitri -= x_val_;
		if (x_vitri <= 0) {
			x_val_ = -TOCDOTHREATS3;
			LoadImg("chim_do_right.png");
		}
		else if (x_vitri >= WIDTH_BACKGROUND) {
			x_val_ = TOCDOTHREATS3;
			LoadImg("chim_do_left.png");
		}
	}

	void InitBullet(BulletObject* p_bullet) {
		if (p_bullet) {
			bool bo = p_bullet->LoadImg("trungga.png");
			if (bo) {
				p_bullet->set_is_move(true);
				p_bullet->SetWidthHeight(WIDTH_TRUNGGA, WIDTH_TRUNGGA);
				p_bullet->SetRect(rect_.x + rect_.w / 2, rect_.y + rect_.h);
				p_bullet->set_y_val(10);
				p_bullet->Set_frame_max(4);
				p_bullet_list_.push_back(p_bullet);
			}
		}
	}

	void MakeBullet(SDL_Surface* des)
	{
		for (int i = 0; i < p_bullet_list_.size(); i++) {
			BulletObject* p_bullet = p_bullet_list_.at(i);
			if (p_bullet)
			{
				if (p_bullet->get_is_move())
				{
					p_bullet->HandleMoveUpToDown();
					p_bullet->Show(des);
				}
				else if (p_bullet->get_is_move() == false)
				{
					p_bullet->set_is_move(true);
					p_bullet->SetRectY(rect_.y + rect_.h);
				}
				p_bullet->SetRectX(rect_.x + rect_.w / 2);

			}
		}
	}
};
