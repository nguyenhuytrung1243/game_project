#pragma once

#include "BaseObject.h"
#include "Bullet.h"



#define WIDTH_MAIN_OBJECT 40
#define HEIGHT_MAIN_OBJECT 60

#define JUMP 15;

const int frame_max_ = 5;

class MainObject : public BaseObject
{
protected:
	int x_val_;
	int speed;

	float y_vantoc;
	float y_giatoc;
	bool is_jumping_;

	int ani_skill;

	float x_vantoc;

	vector <BulletObject* > p_bullet_list;

	int frame_;
	SDL_Rect clip_[frame_max_];
	string trangthai;

public:
	MainObject() {
		rect_.x = 0;
		rect_.y = 0;
		rect_.w = WIDTH_MAIN_OBJECT;
		rect_.h = HEIGHT_MAIN_OBJECT;
		x_val_ = 0;
		speed = 0;
		y_vantoc = 0.0;
		x_vantoc = 0.0;
		y_giatoc = 0.8;
		is_jumping_ = false;
		ani_skill = 0;
		frame_ = -1;
		for (int i = 0; i < frame_max_; i++) {
			clip_[i].x = i * WIDTH_MAIN_OBJECT;
			clip_[i].y = 0;
			clip_[i].w = WIDTH_MAIN_OBJECT;
			clip_[i].h = HEIGHT_MAIN_OBJECT;
		}
		trangthai = "_ninjaright.png";
	}
	float Get_x_vantoc() { return x_vantoc; }
	void Set_x_vantoc(const float& x) { x_vantoc = x; }

	void Set_rect_y(const int& y) { rect_.y = y; }

	void Set_Speed(int sp) { speed = sp; }
	int Get_Speed() { return speed; }


	int Get_x_val() { return x_val_; }

	float Get_y_vantoc() { return y_vantoc; }
	float Get_y_giatoc() { return y_giatoc; }
	bool Get_is_jumping_() { return is_jumping_; }

	void Set_y_vantoc(const float& f) { y_vantoc = f; }
	void Set_y_giatoc(const float& f) { y_giatoc = f; }
	void Set_is_jumping_(const bool& b) { is_jumping_ = b; }

	int Get_Ani_Skill() { return ani_skill; }
	void Set_Ani_Skill(const int& ANI_skill) { ani_skill = ANI_skill; }

	void set_frame(const int& fr) { frame_ = fr; };

	void ShowEx(SDL_Surface* des)
	{
		if (frame_ >= frame_max_) frame_ = 0;
		ApplySurfaceClip(p_object_, des, &clip_[frame_], rect_.x, rect_.y);
	}

	~MainObject() {
		;
	}

	void animation(SDL_Surface* des, const int& I) {
		if (x_val_ == 0 && is_jumping_ == false && trangthai == "_ninjaleft.png" && ani_skill == 0) {
			LoadImg("_ninjaleft.png");
			Show(des);
		}
		else if (x_val_ == 0 && is_jumping_ == false && trangthai == "_ninjaright.png" && ani_skill == 0) {
			LoadImg("_ninjaright.png");
			Show(des);
		}
		else if (x_val_ == -1 && is_jumping_ == false && ani_skill == 0) {
			LoadImg("ninjaleft.png");
			set_frame((I) % frame_max_);
			ShowEx(des);
			trangthai = "_ninjaleft.png";
		}
		else if (x_val_ == 1 && is_jumping_ == false && ani_skill == 0) {
			LoadImg("ninjaright.png");
			set_frame((I) % frame_max_);
			ShowEx(des);
			trangthai = "_ninjaright.png";
		}
		else if (trangthai == "_ninjaleft.png" && x_val_ == 0 && ani_skill == 0) {
			if (y_vantoc < 0) {
				LoadImg("jumpleft.png");
				Show(des);
			}
			else if (y_vantoc > 0) {
				LoadImg("_jumpleft.png");
				Show(des);
			}
		}
		else if (trangthai == "_ninjaright.png" && x_val_ == 0 && ani_skill == 0) {
			if (y_vantoc < 0) {
				LoadImg("jumpright.png");
				Show(des);
			}
			else if (y_vantoc > 0) {
				LoadImg("_jumpright.png");
				Show(des);
			}
		}
		else if (x_val_ == -1 && is_jumping_ == true && ani_skill == 0) {
			if (y_vantoc < 0) {
				LoadImg("jumpleft.png");
				Show(des);
			}
			else if (y_vantoc > 0) {
				LoadImg("_jumpleft.png");
				Show(des);
			}
			trangthai = "_ninjaleft.png";
		}
		else if (x_val_ == 1 && is_jumping_ == true && ani_skill == 0) {
			if (y_vantoc < 0) {
				LoadImg("jumpright.png");
				Show(des);
			}
			else if (y_vantoc > 0) {
				LoadImg("_jumpright.png");
				Show(des);
			}
			trangthai = "_ninjaright.png";
		}
		else if (ani_skill && trangthai == "_ninjaright.png" && ani_skill == 1) {
			LoadImg("ninja_right.png");
			Show(des);
		}
		else if (ani_skill && trangthai == "_ninjaleft.png" && ani_skill == 1) {
			LoadImg("ninja_left.png");
			Show(des);
		}
	}



	void HandleInputAction(SDL_Event events, Mix_Chunk* g_sound[]) {
		if (events.type == SDL_KEYDOWN) {
			switch (events.key.keysym.sym) {
			case SDLK_UP:
				if (!is_jumping_) {
					Mix_PlayChannel(-1, g_sound[2], 0);
					is_jumping_ = true;
					y_vantoc = -JUMP;
				}
				break;

			case SDLK_DOWN:
				//
				break;

			case SDLK_RIGHT:
				x_val_ = 1;
				break;

			case SDLK_LEFT:
				x_val_ = -1;
				break;

			default:
				break;
			}
		}
		else if (events.type == SDL_KEYUP) {
			if (events.key.keysym.sym == SDLK_UP) {

			}
			else if (events.key.keysym.sym == SDLK_DOWN) {

			}
			else if (events.key.keysym.sym == SDLK_RIGHT) {
				if (x_val_ == -1) x_val_ = -1;
				else x_val_ = 0;
			}
			else if (events.key.keysym.sym == SDLK_LEFT) {
				if (x_val_ == 1) x_val_ = 1;
				else x_val_ = 0;
			}
			else {

			}
		}
		else if (events.type == SDL_MOUSEBUTTONDOWN) {
			ani_skill = 1;
			BulletObject* p_bullet = new BulletObject();
			if (events.button.button == SDL_BUTTON_LEFT) {
				p_bullet->SetWidthHeight(WIDTH_LUADO, HEIGHT_LUADO);
				if (trangthai == "_ninjaright.png") {
					p_bullet->LoadImg("luado_right.png");
					p_bullet->Set_tt(1);
				}
				else if (trangthai == "_ninjaleft.png") {
					p_bullet->LoadImg("luado_left.png");
					p_bullet->Set_tt(-1);
				}
				p_bullet->Set_frame_max(8);
				p_bullet->SetClip();
				p_bullet->set_x_val(3 * speed);
				p_bullet->SetRect(this->rect_.x + WIDTH_MAIN_OBJECT / 2, this->rect_.y + HEIGHT_MAIN_OBJECT / 2);
				p_bullet->set_is_move(true);
				p_bullet_list.push_back(p_bullet);
				Mix_PlayChannel(-1, g_sound[0], 0);
			}
			else if (events.button.button == SDL_BUTTON_RIGHT) {

			}
		}
		else if (events.type == SDL_MOUSEBUTTONUP) {
			ani_skill = 0;
		}
		else {

		}
	}




	void HandleMove(const vector<SDL_Rect>& obstacles) {
		x_vantoc += speed * x_val_;

		if (x_vantoc <= 0) {
			rect_.x += speed * x_val_;
			if (rect_.x <= 0) {
				rect_.x = 0;
			}
			x_vantoc = rect_.x - DIEMBATDAU;
		}
		else if (x_vantoc >= WIDTH_BACKGROUND - SCREEN_WIDTH) {
			rect_.x += speed * x_val_;
			if (rect_.x >= SCREEN_WIDTH - WIDTH_MAIN_OBJECT) {
				rect_.x = SCREEN_WIDTH - WIDTH_MAIN_OBJECT;
			}
			x_vantoc = WIDTH_BACKGROUND - SCREEN_WIDTH - DIEMBATDAU + rect_.x;
		}

		/*bool onGround = false;*/

		//if (is_jumping_ || !onGround) {
		//	rect_.y += y_vantoc;
		//	y_vantoc += y_giatoc;
		//}

		//for (const auto& obs : obstacles) {
		//	if (CheckCollision(rect_, obs, x_vantoc + 400)) {
		//		if (y_vantoc > 0) {
		//			rect_.y = obs.y - rect_.h;
		//			y_vantoc = 0;
		//			is_jumping_ = false;
		//			onGround = true;//
		//		}
		//		break;
		//	}
		//}

		//if (!onGround && rect_.y + HEIGHT_MAIN_OBJECT < 520) {
		//	onGround = false;
		//}

		//else if (rect_.y + HEIGHT_MAIN_OBJECT >= 520) {
		//	rect_.y = 520 - HEIGHT_MAIN_OBJECT;
		//	y_vantoc = 0;
		//	is_jumping_ = false;
		//	onGround = true;//
		//}
		//if (y_vantoc != 0) is_jumping_ = true;


		rect_.y += y_vantoc;
		y_vantoc += y_giatoc;
		for (const auto& obs : obstacles) {
			if (CheckCollision(rect_, obs, x_vantoc + 400)) {
				if (y_vantoc > 0) {
					rect_.y = obs.y - rect_.h;
					y_vantoc = 0;
					is_jumping_ = false;
				}
				break;
			}
		}
		if (rect_.y + HEIGHT_MAIN_OBJECT >= 520) {
			rect_.y = 520 - HEIGHT_MAIN_OBJECT;
			y_vantoc = 0;
			is_jumping_ = false;
		}
		if (y_vantoc != 0) is_jumping_ = true;
	}

	void SetBulleList(vector <BulletObject* > bullet_list) {
		p_bullet_list = bullet_list;
	}
	vector <BulletObject* > GetBulletList()const {
		return p_bullet_list;
	}
	void MakeBullet(SDL_Surface* des, const int& I)
	{
		for (int i = 0; i < p_bullet_list.size(); i++)
		{
			BulletObject* p_bullet = p_bullet_list.at(i);
			if (p_bullet != NULL) {
				if (p_bullet->get_is_move())
				{
					p_bullet->HandleMove();
					p_bullet->Set_frame((I) % 8);
					p_bullet->ShowEx(des);
				}
				else {
					if (p_bullet != NULL)
					{
						p_bullet_list.erase(p_bullet_list.begin() + i);
						delete p_bullet;
						p_bullet = NULL;
					}
				}
			}
		}
	}

	void RemoveBullet(const int& _x)
	{
		if (p_bullet_list.size() > _x)
		{
			p_bullet_list.erase(p_bullet_list.begin() + _x);
		}
	}

};