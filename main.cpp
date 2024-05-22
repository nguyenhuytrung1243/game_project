#include "common.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Time.h"
#include "ThreatsObject.h"
#include "Bullet.h"
#include "PlayerPower.h"
#include "TextObject.h"
#include "MenuObject.h"
#include "AniObject.h"


bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}
	g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1200, 600, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		return false;
	}
	g_screen = SDL_GetWindowSurface(g_window);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;

	g_sound[0] = Mix_LoadWAV("Fireball+3.wav");
	g_sound[1] = Mix_LoadWAV("ChimUng.wav");
	g_sound[2] = Mix_LoadWAV("jump.wav");
	g_sound[3] = Mix_LoadWAV("tiengset.wav");
	g_sound[4] = Mix_LoadWAV("tangdiem.wav");

	/*if (g_sound[0] == NULL || g_sound[1] == NULL || g_sound[2] == NULL) return false;*/

	for (int i = 0; i < 5; i++) {
		if (g_sound[i] == NULL) return false;
	}


	g_music = Mix_LoadMUS("Yu-Gi-Oh.mp3");
	if (g_music == NULL) return false;
	if (Mix_PlayMusic(g_music, -1) == -1) return false;


	if (TTF_Init() == -1) return false;

	g_font_text = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 20);
	if (g_font_text == NULL) return false;

	g_font_menu = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 30);
	if (g_font_menu == NULL) return false;



	return true;
}





int main(int argc, char* grgv[])
{
	ImpTimer fps_time;

	bool is_quit = false;

	if (Init() == false) return 1;

	BaseObject HinhAnh;
	bool _ha = HinhAnh.LoadImg("bg4800.png");
	if (!_ha) return 1;

	TextObject time_game;
	time_game.SetColor(255, 255, 255);
	time_game.SetRect(520, 1);

	TextObject diem_game;
	diem_game.SetColor(255, 255, 255);
	diem_game.SetRect(1000, 1);

	TextObject boss_game;
	boss_game.SetColor(0, 0, 0);
	boss_game.SetRect(0, 600 - 15);
	boss_game.SetText("BOSS");

	TextObject name_boss;
	name_boss.SetColor(0, 0, 0);
	name_boss.SetText("BOSS");

	MainObject Nhanvat;
	bool nv = Nhanvat.LoadImg("_ninjaright.png");
	if (!nv) return 1;
	Nhanvat.SetRect(DIEMBATDAU, 520 - HEIGHT_MAIN_OBJECT);
	Nhanvat.Set_Speed(10);
	PlayerPower hpNhanVat;
	hpNhanVat.SetRectAll(0, 0, WIDTH_HP_NHANVAT, HEIGHT_HP_NHANVAT);
	hpNhanVat.Set_number_(80);
	hpNhanVat.Init("hp.png", 1);
	PlayerPower Mang;
	Mang.SetRectAll(0, 0, WIDTH_MAIN_OBJECT, HEIGHT_MAIN_OBJECT);
	Mang.Set_number_(5);
	Mang.Init("_ninjaright.png", WIDTH_MAIN_OBJECT);


	ThreatsObject* threat = new ThreatsObject();
	bool B_ = threat->LoadImg("ma_left.png");
	if (!B_) return 1;
	threat->Set_x_val(TOCDOTHREATS1);
	BulletObject* p_bullet = new BulletObject();
	threat->InitBullet(p_bullet);
	PlayerPower bosshp;
	bosshp.Set_number_(400);
	bosshp.Init("hpBOSS.png", 3);
	bosshp.SetRectAll(0, SCREEN_HEIGHT - HEIGHT_HP_BOSS, WIDTH_HP_BOSS, HEIGHT_HP_BOSS);
	PlayerPower bosshp1;
	bosshp1.Set_number_(400);
	bosshp1.Init("hpBOSS1.png", 3);
	bosshp1.SetRectAll(0, SCREEN_HEIGHT - HEIGHT_HP_BOSS, WIDTH_HP_BOSS, HEIGHT_HP_BOSS);
	PlayerPower bosshp2;
	bosshp2.Set_number_(400);
	bosshp2.Init("hpBOSS2.png", 3);
	bosshp2.SetRectAll(0, SCREEN_HEIGHT - HEIGHT_HP_BOSS, WIDTH_HP_BOSS, HEIGHT_HP_BOSS);


	ThreatsObject_* list_threats = new ThreatsObject_[NUM_THREATS];
	for (int i = 0; i < NUM_THREATS; i++) {
		ThreatsObject_* p_threats = list_threats + i;
		p_threats->Set_x_vitri(WIDTH_BACKGROUND + i * SCREEN_WIDTH);
		p_threats->SetRect(WIDTH_BACKGROUND, GetRandom(0, SCREEN_HEIGHT - 100));
		bool b_ = p_threats->LoadImg("chim_left.png");
		if (!b_) return 1;
		p_threats->Set_x_val(TOCDOTHREATS2);
		p_threats->Set_y_val(1);
	}
	//
	ThreatsObject_* list_threats3 = new ThreatsObject_[NUM_THREATS3];
	for (int i = 0; i < NUM_THREATS3; i++) {
		ThreatsObject_* p_threats = list_threats3 + i;
		p_threats->Set_x_vitri(WIDTH_BACKGROUND + i * 1600);
		p_threats->SetRect(WIDTH_BACKGROUND, GetRandom(0, SCREEN_HEIGHT - 500));
		bool b_ = p_threats->LoadImg("chim_do_left.png");
		if (!b_) return 1;
		p_threats->Set_x_val(TOCDOTHREATS3);
		BulletObject* _bullet = new BulletObject();
		p_threats->InitBullet(_bullet);
	}

	AniObject ani;
	if (!ani.LoadImg("vacham.png")) return 1;
	ani.Set_frame_max_(9);
	ani.Set_Clip();


	vector<SDL_Rect> vatcanRECT;

	BaseObject vatcan1;
	bool vc = vatcan1.LoadImg("vatcan_1.png");
	if (!vc) return 1;
	vatcan1.SetRectAll(VATCAN_1_X, VATCAN_1_Y, VATCAN_1_W, VATCAN_1_H);

	BaseObject vatcan2;
	bool vc2 = vatcan2.LoadImg("vatcan_1.png");
	if (!vc2) return 1;
	vatcan2.SetRectAll(VATCAN_2_X, VATCAN_2_Y, VATCAN_2_W, VATCAN_2_H);

	BaseObject vatcan3;
	bool vc3 = vatcan3.LoadImg("3.png");
	if (!vc3) return 1;
	vatcan3.SetRectAll(VATCAN_3_X, VATCAN_3_Y, VATCAN_3_W, VATCAN_3_H);

	BaseObject vatcan4;
	bool vc4 = vatcan4.LoadImg("4.png");
	if (!vc4) return 1;
	vatcan4.SetRectAll(VATCAN_4_X, VATCAN_4_Y, VATCAN_4_W, VATCAN_4_H);

	BaseObject vatcan5;
	bool vc5 = vatcan5.LoadImg("5.png");
	if (!vc5) return 1;
	vatcan5.SetRectAll(VATCAN_5_X, VATCAN_5_Y, VATCAN_5_W, VATCAN_5_H);

	BaseObject vatcan6;
	bool vc6 = vatcan6.LoadImg("6.png");
	if (!vc6) return 1;
	vatcan6.SetRectAll(VATCAN_6_X, VATCAN_6_Y, VATCAN_6_W, VATCAN_6_H);

	BaseObject vatcan7;
	bool vc7 = vatcan7.LoadImg("7.png");
	if (!vc7) return 1;
	vatcan7.SetRectAll(VATCAN_7_X, VATCAN_7_Y, VATCAN_7_W, VATCAN_7_H);

	BaseObject vatcan8;
	bool vc8 = vatcan8.LoadImg("8.png");
	if (!vc8) return 1;
	vatcan8.SetRectAll(VATCAN_8_X, VATCAN_8_Y, VATCAN_8_W, VATCAN_8_H);

	BaseObject vatcan9;
	bool vc9 = vatcan9.LoadImg("9.png");
	if (!vc9) return 1;
	vatcan9.SetRectAll(VATCAN_9_X, VATCAN_9_Y, VATCAN_9_W, VATCAN_9_H);

	BaseObject vatcan0;
	bool vc0 = vatcan0.LoadImg("7.png");
	if (!vc0) return 1;
	vatcan0.SetRectAll(VATCAN_0_X, VATCAN_0_Y, VATCAN_0_W, VATCAN_0_H);

	vatcanRECT.push_back(vatcan1.GetRect());
	vatcanRECT.push_back(vatcan2.GetRect());
	vatcanRECT.push_back(vatcan3.GetRect());
	vatcanRECT.push_back(vatcan4.GetRect());
	vatcanRECT.push_back(vatcan5.GetRect());
	vatcanRECT.push_back(vatcan6.GetRect());
	vatcanRECT.push_back(vatcan7.GetRect());
	vatcanRECT.push_back(vatcan8.GetRect());
	vatcanRECT.push_back(vatcan9.GetRect());
	vatcanRECT.push_back(vatcan0.GetRect());

	MenuObject menu_;
	if (!menu_.LoadImg("hinhnen.png"));
	menu_.SetRect(0, 0);
	menu_.Set_Menu_Item(2);
	menu_.Menu();

	MenuObject good_ending;
	good_ending.SetRect(0, 0);
	good_ending.Set_Menu_Item(1);

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				return 1;
			}
			else if (g_event.type == SDL_MOUSEMOTION)
			{
				for (int i = 0; i < menu_.Get_text_menu().size(); i++)
				{
					if (CheckFocusWithRect(g_event.motion.x, g_event.motion.y, menu_.Get_text_menu().at(i)->GetRect()))
					{
						menu_.Get_text_menu().at(i)->SetColor(255, 0, 0);
					}
					else {
						menu_.Get_text_menu().at(i)->SetColor(255, 255, 255);
					}
				}
				break;
			}
			else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
				for (int i = 0; i < menu_.Get_text_menu().size(); i++)
				{
					if (CheckFocusWithRect(g_event.motion.x, g_event.motion.y, menu_.Get_text_menu().at(i)->GetRect()))
					{
						if (i == 0) {
							is_quit = true;
							break;
						}
						else if (i == 1) return 1;
					}
				}
				break;
			}
			else;
		}
		menu_.Show(g_screen);
		menu_.ShowText(g_font_menu, g_screen);
		if (SDL_UpdateWindowSurface(g_window) == -1) return 0;
	}
	is_quit = false;
	int end = 1;
	int diem = 0;
	int I = 0;
	while (!is_quit)
	{
		fps_time.start();
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				return 1;
			}
			Nhanvat.HandleInputAction(g_event, g_sound);
		}
		HinhAnh.Show(g_screen);
		hpNhanVat.Render(g_screen, Nhanvat.GetRect());
		name_boss.SetRect(threat->GetRect().x - 17, threat->GetRect().y - 20);
		Mang.Render(g_screen);
		bosshp.Render(g_screen);
		bosshp2.Render(g_screen);
		bosshp1.Render(g_screen);
		if (Nhanvat.Get_x_vantoc() >= 0 && Nhanvat.Get_x_vantoc() <= WIDTH_BACKGROUND - SCREEN_WIDTH) {
			HinhAnh.SetRect(-Nhanvat.Get_x_vantoc(), 0);
			vatcan1.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_1_X, VATCAN_1_Y);
			vatcan2.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_2_X, VATCAN_2_Y);
			vatcan3.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_3_X, VATCAN_3_Y);
			vatcan4.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_4_X, VATCAN_4_Y);
			vatcan5.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_5_X, VATCAN_5_Y);
			vatcan6.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_6_X, VATCAN_6_Y);
			vatcan7.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_7_X, VATCAN_7_Y);
			vatcan8.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_8_X, VATCAN_8_Y);
			vatcan9.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_9_X, VATCAN_9_Y);
			vatcan0.SetRect(-Nhanvat.Get_x_vantoc() + VATCAN_0_X, VATCAN_0_Y);

			threat->SetRect(-Nhanvat.Get_x_vantoc() + threat->Get_x_vitri(), 520 - HEIGHT_THREATS);

			for (int i = 0; i < NUM_THREATS; i++) {
				ThreatsObject_* p_threats = list_threats + i;
				if (p_threats) p_threats->SetRectX(-Nhanvat.Get_x_vantoc() + p_threats->Get_x_vitri());
			}
			//
			for (int i = 0; i < NUM_THREATS3; i++) {
				ThreatsObject_* p_threats = list_threats3 + i;
				if (p_threats) p_threats->SetRectX(-Nhanvat.Get_x_vantoc() + p_threats->Get_x_vitri());
			}
		}
		else if (Nhanvat.Get_x_vantoc() < 0)
		{

			HinhAnh.SetRect(0, 0);
			vatcan1.SetRect(VATCAN_1_X, VATCAN_1_Y);
			vatcan2.SetRect(VATCAN_2_X, VATCAN_2_Y);
			vatcan3.SetRect(VATCAN_3_X, VATCAN_3_Y);
			vatcan4.SetRect(VATCAN_4_X, VATCAN_4_Y);
			vatcan5.SetRect(VATCAN_5_X, VATCAN_5_Y);
			vatcan6.SetRect(VATCAN_6_X, VATCAN_6_Y);
			vatcan7.SetRect(VATCAN_7_X, VATCAN_7_Y);
			vatcan8.SetRect(VATCAN_8_X, VATCAN_8_Y);
			vatcan9.SetRect(VATCAN_9_X, VATCAN_9_Y);
			vatcan0.SetRect(VATCAN_0_X, VATCAN_0_Y);

			threat->SetRect(threat->Get_x_vitri(), 520 - HEIGHT_THREATS);

			for (int i = 0; i < NUM_THREATS; i++) {
				ThreatsObject_* p_threats = list_threats + i;
				if (p_threats) p_threats->SetRectX(p_threats->Get_x_vitri());
			}
			//
			for (int i = 0; i < NUM_THREATS3; i++) {
				ThreatsObject_* p_threats = list_threats3 + i;
				if (p_threats) p_threats->SetRectX(p_threats->Get_x_vitri());
			}
		}
		else if (Nhanvat.Get_x_vantoc() > WIDTH_BACKGROUND - SCREEN_WIDTH)
		{
			threat->SetRect(threat->Get_x_vitri() - (WIDTH_BACKGROUND - SCREEN_WIDTH), 520 - HEIGHT_THREATS);

			for (int i = 0; i < NUM_THREATS; i++) {
				ThreatsObject_* p_threats = list_threats + i;
				if (p_threats) p_threats->SetRectX(p_threats->Get_x_vitri() - (WIDTH_BACKGROUND - SCREEN_WIDTH));
			}
			//
			for (int i = 0; i < NUM_THREATS3; i++) {
				ThreatsObject_* p_threats = list_threats3 + i;
				if (p_threats) p_threats->SetRectX(p_threats->Get_x_vitri() - (WIDTH_BACKGROUND - SCREEN_WIDTH));
			}
		}

		Nhanvat.animation(g_screen, I);
		Nhanvat.HandleMove(vatcanRECT);

		vatcan1.Show(g_screen);
		vatcan2.Show(g_screen);
		vatcan3.Show(g_screen);
		vatcan4.Show(g_screen);
		vatcan5.Show(g_screen);
		vatcan6.Show(g_screen);
		vatcan7.Show(g_screen);
		vatcan8.Show(g_screen);
		vatcan9.Show(g_screen);
		vatcan0.Show(g_screen);

		Nhanvat.MakeBullet(g_screen, I);

		threat->animation(g_screen, Nhanvat.Get_x_vantoc(), Nhanvat.GetRect());
		if (CheckCollision(Nhanvat.GetRect(), threat->GetRect()))
		{
			Mix_PlayChannel(-1, g_sound[3], 0);
			ani.SetRect(Nhanvat.GetRect().x, Nhanvat.GetRect().y);
			ani.Set_frame(I % ani.Get_frame_max_());
			ani.ShowEx(g_screen);
			hpNhanVat.Decrease();
		}
		for (int j = 0; j < Nhanvat.GetBulletList().size(); j++)
		{
			BulletObject* p_bullet = Nhanvat.GetBulletList().at(j);
			if (p_bullet)
			{
				if (CheckCollision(p_bullet->GetRect(), threat->GetRect())) {
					Mix_PlayChannel(-1, g_sound[3], 0);
					ani.SetRect(threat->GetRect().x, threat->GetRect().y);
					ani.Set_frame(I % ani.Get_frame_max_());
					ani.ShowEx(g_screen);
					if (bosshp1.Get_number_() > 0) bosshp1.Decrease();
					else if (bosshp2.Get_number_() > 0 && bosshp1.Get_number_() == 0) bosshp2.Decrease();
					else if (bosshp2.Get_number_() == 0) bosshp.Decrease();
				}
			}
		}
		if (bosshp1.Get_number_() == 1) {
			bosshp1.Decrease();
			Mang.Tang();
		}
		else if (bosshp2.Get_number_() == 1) {
			bosshp2.Decrease();
			Mang.Tang();
		}
		for (int j = 0; j < threat->Get_bullet_list().size(); j++) {
			BulletObject* p_bullet = threat->Get_bullet_list().at(j);
			if (p_bullet)
			{
				if (CheckCollision(p_bullet->GetRect(), Nhanvat.GetRect()))
				{
					Mix_PlayChannel(-1, g_sound[3], 0);
					ani.SetRect(Nhanvat.GetRect().x, Nhanvat.GetRect().y);
					ani.Set_frame(I % ani.Get_frame_max_());
					ani.ShowEx(g_screen);
					hpNhanVat.Decrease();
				}
			}
		}


		for (int i = 0; i < NUM_THREATS; i++) {
			ThreatsObject_* p_threats = list_threats + i;
			if (p_threats) {
				p_threats->Set_frame(I % 4);
				p_threats->HandleMove(Nhanvat.Get_x_vantoc(), Nhanvat.GetRect().y);
				p_threats->ShowEx(g_screen);

				if (CheckCollision(Nhanvat.GetRect(), p_threats->GetRect()))
				{
					ani.SetRect(Nhanvat.GetRect().x, Nhanvat.GetRect().y);
					ani.Set_frame(I % ani.Get_frame_max_());
					ani.ShowEx(g_screen);
					hpNhanVat.Decrease();
					Mix_PlayChannel(-1, g_sound[1], 0);
				}

				for (int j = 0; j < Nhanvat.GetBulletList().size(); j++)
				{
					BulletObject* p_bullet = Nhanvat.GetBulletList().at(j);
					if (p_bullet)
					{
						if (CheckCollision(p_bullet->GetRect(), p_threats->GetRect())) {
							Mix_PlayChannel(-1, g_sound[4], 0);
							diem++;
							Nhanvat.RemoveBullet(j);
							p_threats->SetRect(WIDTH_BACKGROUND, GetRandom(0, SCREEN_HEIGHT - 100));
							p_threats->Set_x_vitri(WIDTH_BACKGROUND * GetRandom(-2, 2));
						}
					}
				}
			}
		}
		//
		for (int i = 0; i < NUM_THREATS3; i++) {
			ThreatsObject_* p_threats = list_threats3 + i;
			if (p_threats) {
				p_threats->Set_frame(I % 4);
				p_threats->HandleMove();
				p_threats->ShowEx(g_screen);
				p_threats->MakeBullet(g_screen);
				if (CheckCollision(Nhanvat.GetRect(), p_threats->GetRect()))
				{
					ani.SetRect(Nhanvat.GetRect().x, Nhanvat.GetRect().y);
					ani.Set_frame(I % ani.Get_frame_max_());
					ani.ShowEx(g_screen);
					hpNhanVat.Decrease();
					Mix_PlayChannel(-1, g_sound[1], 0);
				}
				for (int j = 0; j < Nhanvat.GetBulletList().size(); j++)
				{
					BulletObject* p_bullet = Nhanvat.GetBulletList().at(j);
					if (p_bullet)
					{
						if (CheckCollision(p_bullet->GetRect(), p_threats->GetRect())) {
							Mix_PlayChannel(-1, g_sound[4], 0);
							diem++;
							Nhanvat.RemoveBullet(j);
							p_threats->SetRect(WIDTH_BACKGROUND, GetRandom(0, SCREEN_HEIGHT - 500));
							p_threats->Set_x_vitri(WIDTH_BACKGROUND * GetRandom(-1, 2));
						}
					}
				}
				for (int j = 0; j < p_threats->Get_bullet_list().size(); j++) {
					BulletObject* p_bullet = p_threats->Get_bullet_list().at(j);
					if (p_bullet)
					{
						if (CheckCollision(p_bullet->GetRect(), Nhanvat.GetRect()))
						{
							Mix_PlayChannel(-1, g_sound[3], 0);
							ani.SetRect(Nhanvat.GetRect().x, Nhanvat.GetRect().y);
							ani.Set_frame(I % ani.Get_frame_max_());
							ani.ShowEx(g_screen);
							hpNhanVat.Decrease();
						}
					}
				}
			}
		}
		if (hpNhanVat.Get_number_() <= 1) {
			Nhanvat.SetRect(DIEMBATDAU, 520 - HEIGHT_MAIN_OBJECT);
			Nhanvat.Set_x_vantoc(0.0);
			hpNhanVat.Set_number_(80);
			hpNhanVat.Init("hp.png", 1);
			Mang.Decrease();
			if (Mang.Get_number_() == 0) {
				is_quit = true;
				end = 0;
			}
		}
		else if (bosshp.Get_number_() <= 1) {
			is_quit = true;
			end = 1;
		}

		string time_minute = to_string((I / 30) / 60);
		if (time_minute.size() == 1) time_minute = "0" + time_minute;
		string time_second = to_string((I / 30) % 60);
		if (time_second.size() == 1) time_second = "0" + time_second;
		string _time = "Thoi Gian : ";
		_time += (time_minute + "m" + time_second + "s");
		time_game.SetText(_time);

		string str_diem = to_string(diem);
		string diem_so = "Diem : ";
		diem_so += str_diem;
		diem_game.SetText(diem_so);

		time_game.CreateGame(g_font_text, g_screen);
		diem_game.CreateGame(g_font_text, g_screen);
		boss_game.CreateGame(g_font_text, g_screen);
		name_boss.CreateGame(g_font_text, g_screen);

		if (SDL_UpdateWindowSurface(g_window) == -1) return 0;
		int real_imp_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
		I++;
	}
	is_quit = false;
	if (end == 1) {
		if (!good_ending.LoadImg("good_ending.png"));
		good_ending.Good_End();
	}
	else {
		if (!good_ending.LoadImg("bad_ending.png"));
		good_ending.Bad_End();
	}
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				return 1;
			}
			else if (g_event.type == SDL_MOUSEMOTION)
			{
				for (int i = 0; i < good_ending.Get_text_menu().size(); i++)
				{
					if (CheckFocusWithRect(g_event.motion.x, g_event.motion.y, good_ending.Get_text_menu().at(i)->GetRect()))
					{
						good_ending.Get_text_menu().at(i)->SetColor(255, 0, 0);
					}
					else {
						good_ending.Get_text_menu().at(i)->SetColor(0, 0, 0);
					}
				}
				break;
			}
			else if (g_event.type == SDL_MOUSEBUTTONDOWN) {
				for (int i = 0; i < good_ending.Get_text_menu().size(); i++)
				{
					if (CheckFocusWithRect(g_event.motion.x, g_event.motion.y, good_ending.Get_text_menu().at(i)->GetRect()))
					{
						if (i == 0) {
							is_quit = true;
							break;
						}
					}
				}
				break;
			}
			else;
		}
		good_ending.Show(g_screen);
		good_ending.ShowText(g_font_menu, g_screen);
		if (SDL_UpdateWindowSurface(g_window) == -1) return 0;
	}

	delete threat;
	threat = nullptr;
	delete[] list_threats;
	delete[] list_threats3;
	CleanUp();
	SDL_Quit();
	return 0;
}
