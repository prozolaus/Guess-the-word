#pragma once
#include "Game.h"

class MenuText : public sf::Text
{
	sf::Font font;
	string fontname;

public:
	MenuText(const string& text);
	void setFont(const sf::Font& f);
};

//-----------------------------------------------------------------------------

class Menu
{
	MenuSettings mset;
	MenuText start, lang, ua, ru;
	MenuText guesser, player, computer;
	MenuText lttrs, three, four;
	MenuText lvl, school, normal, erudite;
	bool UA_lang, RU_lang;
	bool player_guesses, comp_guesses;
	bool three_ls, four_ls;
	bool school_lvl, normal_lvl, erudite_lvl;
	sf::Vector2i pos;
	const int x, y;
	sf::Texture bgtexture;
	sf::Sprite background;
	void changeLangToUKR();
	void changeLangToRUS();
	void TextCorrection();
	void colorChanging(MenuText& mt, bool b);

public:

	Menu(unsigned int window_width, unsigned int window_height);

	void setMousePos(const sf::Vector2i p) { pos = p; }
	void setAllTextBlack();
	void changeColorOnHover();
	bool isStartGame();
	void mouseClickHandling();
	void drawMenu(sf::RenderWindow& window);
	MenuSettings getMenuSettings() const { return mset; }
};