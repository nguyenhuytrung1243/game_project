#pragma once
#include "BaseObject.h"

class TextObject :public BaseObject
{
private:
	string str_val_;
	SDL_Color text_color_;

public:
	TextObject() { ; }
	~TextObject() { ; }

	void SetText(const string& text) { str_val_ = text; }

	void SetColor(const int& x, const int& y, const int& z)
	{
		SDL_Color color = { x,y,z };
		text_color_ = color;
	}

	void CreateGame(TTF_Font* font, SDL_Surface* des) {
		p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
		Show(des);
	}
};