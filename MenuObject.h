#pragma once

#include "BaseObject.h"
#include "TextObject.h"

class MenuObject : public BaseObject {
private:
	int Menu_Item;
	vector <TextObject*> text_menu;
	TextObject* text;
public:
	MenuObject()
	{
		Menu_Item = 0;
	}

	void Menu() {
		text = new TextObject();
		text->SetText(" play game");
		text->SetColor(255, 255, 255);
		text->SetRectAll(200, 200, 205, 30);
		text_menu.push_back(text);

		text = new TextObject();
		text->SetText("       exit");
		text->SetColor(255, 255, 255);
		text->SetRectAll(200, 300, 205, 30);
		text_menu.push_back(text);
	}

	void Good_End() {
		text = new TextObject();
		text->SetText(" chuc mung ban!");
		text->SetColor(0, 0, 0);
		text->SetRectAll(50, 300, 305, 30);
		text_menu.push_back(text);
	}

	void Bad_End() {
		text = new TextObject();
		text->SetText(" tro choi ket thuc!");
		text->SetColor(0, 0, 0);
		text->SetRectAll(50, 300, 305, 30);
		text_menu.push_back(text);
	}

	~MenuObject() {
		for (TextObject* item : text_menu) {
			delete item;
		}
		text_menu.clear();
	}

	void ShowText(TTF_Font* font, SDL_Surface* des)
	{
		for (int i = 0; i < Menu_Item; i++) {
			text_menu[i]->CreateGame(font, des);
		}
	}

	void Set_Menu_Item(const int& n) { Menu_Item = n; }
	int Get_Menu_Item() { return Menu_Item; }

	vector <TextObject*> Get_text_menu() { return text_menu; }
};