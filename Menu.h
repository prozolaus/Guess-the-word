#pragma once
#include "Game.h"

class MenuText : public sf::Text
{
	sf::Font font;

public:
	MenuText(const string& text);
	void setFont(const sf::Font& f);
};

//-----------------------------------------------------------------------------

class Menu
{
	MenuSettings mset;
	MenuText start, lang, ua, ru;
	MenuText lttrs, three, four;
	MenuText lvl, school, normal, erudite;
	bool UA_lang, RU_lang;
	bool three_ls, four_ls;
	bool school_lvl, normal_lvl, erudite_lvl;
	const int x = 100, y = 100;

public:

	Menu(unsigned int window_width, unsigned int window_height);

	void setAllTextBlack();
	void changeColorOnHover(sf::Vector2i pos);
	bool isStartGame(sf::Vector2i pos);
	void mouseClickHandling(sf::Vector2i pos);
	void drawMenu(sf::RenderWindow& window);
	MenuSettings getMenuSettings() const { return mset; }
};