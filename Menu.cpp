#include "Menu.h"

MenuText::MenuText(const string& text) : Text()
{
	fontname = "fonts\\Arial.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("Game::setGame(): cannot open a font file " + fontname);
	Text::setFont(font);
	Text::setString(text);
	Text::setFillColor(sf::Color::Black);
	Text::setCharacterSize(18);
}

void MenuText::setFont(const sf::Font& f)
{
	font = f;
	Text::setFont(font);
}

//------------------------------------------------------------------------------------------------


Menu::Menu(unsigned int window_width, unsigned int window_height)
	: start{ "Start" },
	lang{ "Language:" }, ua{ "UA" }, ru{ "RU" },
	lttrs{ "Letters:" }, three{ "Three" }, four{ "Four" },
	lvl{ "Level:" }, school{ "School" }, normal{ "Normal" }, erudite{ "Erudite" },
	UA_lang{ false }, RU_lang{ false },
	three_ls{ false }, four_ls{ false },
	school_lvl{ false }, normal_lvl{ false }, erudite_lvl{ false }
{
	start.setPosition(window_width / 2 - start.getGlobalBounds().width / 2, window_height / 2);
	lang.setPosition(x, y);
	ua.setPosition(x + lang.getGlobalBounds().width + x / 3, y);
	ru.setPosition(ua.getPosition().x + x / 2, y);
	lttrs.setPosition(x, 1.5 * y);
	three.setPosition(ua.getPosition().x, 1.5 * y);
	four.setPosition(three.getPosition().x + three.getGlobalBounds().width + x / 3, 1.5 * y);
	lvl.setPosition(x, 2 * y);
	school.setPosition(three.getPosition().x, 2 * y);
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 2, 2 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 2, 2 * y);
}


void Menu::changeLangToUKR()
{
	start.setString(L"Старт");
	lang.setString(L"Мова:");
	lttrs.setString(L"Літери:");
	three.setString(L"Три");
	four.setString(L"Чотири");
	lvl.setString(L"Рівень:");
	school.setString(L"Шкільний");
	normal.setString(L"Нормальний");
	erudite.setString(L"Ерудит");
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 3, 2 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 3, 2 * y);
}

void Menu::changeLangToRUS()
{
	start.setString(L"Старт");
	lang.setString(L"Язык:");
	lttrs.setString(L"Буквы:");
	three.setString(L"Три");
	four.setString(L"Четыре");
	lvl.setString(L"Уровень:");
	school.setString(L"Школьный");
	normal.setString(L"Нормальный");
	erudite.setString(L"Эрудит");
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 3, 2 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 3, 2 * y);
}


void Menu::setAllTextBlack()
{
	start.setFillColor(sf::Color::Black);
	if (!UA_lang) ua.setFillColor(sf::Color::Black);
	if (!RU_lang) ru.setFillColor(sf::Color::Black);
	if (!three_ls) three.setFillColor(sf::Color::Black);
	if (!four_ls) four.setFillColor(sf::Color::Black);
	if (!school_lvl) school.setFillColor(sf::Color::Black);
	if (!normal_lvl) normal.setFillColor(sf::Color::Black);
	if (!erudite_lvl) erudite.setFillColor(sf::Color::Black);
}

void Menu::changeColorOnHover(sf::Vector2i pos)
{
	if (ua.getGlobalBounds().contains(pos.x, pos.y))
		UA_lang ? ua.setFillColor(sf::Color::Blue) : ua.setFillColor(sf::Color::Green);
	if (ru.getGlobalBounds().contains(pos.x, pos.y))
		RU_lang ? ru.setFillColor(sf::Color::Blue) : ru.setFillColor(sf::Color::Green);
	if (three.getGlobalBounds().contains(pos.x, pos.y))
		three_ls ? three.setFillColor(sf::Color::Blue) : three.setFillColor(sf::Color::Green);
	if (four.getGlobalBounds().contains(pos.x, pos.y))
		four_ls ? three.setFillColor(sf::Color::Blue) : four.setFillColor(sf::Color::Green);
	if (school.getGlobalBounds().contains(pos.x, pos.y))
		school_lvl ? school.setFillColor(sf::Color::Blue) : school.setFillColor(sf::Color::Green);
	if (normal.getGlobalBounds().contains(pos.x, pos.y))
		normal_lvl ? normal.setFillColor(sf::Color::Blue) : normal.setFillColor(sf::Color::Green);
	if (erudite.getGlobalBounds().contains(pos.x, pos.y))
		erudite_lvl ? erudite.setFillColor(sf::Color::Blue) : erudite.setFillColor(sf::Color::Green);
	if (start.getGlobalBounds().contains(pos.x, pos.y) && (UA_lang || RU_lang) && (three_ls || four_ls) && (school_lvl || normal_lvl || erudite_lvl))
		start.setFillColor(sf::Color::Blue);
}

bool Menu::isStartGame(sf::Vector2i pos)
{
	return start.getGlobalBounds().contains(pos.x, pos.y) && (UA_lang || RU_lang) && (three_ls || four_ls) && (school_lvl || normal_lvl || erudite_lvl) ? true : false;
}

void Menu::mouseClickHandling(sf::Vector2i pos)
{
	if (ua.getGlobalBounds().contains(pos.x, pos.y))
	{
		ua.setFillColor(sf::Color::Blue);
		mset.language = Language::UKR;
		UA_lang = true;
		RU_lang = false;
		changeLangToUKR();
	}
	if (ru.getGlobalBounds().contains(pos.x, pos.y))
	{
		ru.setFillColor(sf::Color::Blue);
		mset.language = Language::RUS;
		RU_lang = true;
		UA_lang = false;
		changeLangToRUS();
	}
	if (three.getGlobalBounds().contains(pos.x, pos.y))
	{
		three.setFillColor(sf::Color::Blue);
		mset.letters = Letters::THREE;
		three_ls = true;
		four_ls = false;
	}
	if (four.getGlobalBounds().contains(pos.x, pos.y))
	{
		four.setFillColor(sf::Color::Blue);
		mset.letters = Letters::FOUR;
		four_ls = true;
		three_ls = false;
	}
	if (school.getGlobalBounds().contains(pos.x, pos.y))
	{
		school.setFillColor(sf::Color::Blue);
		mset.level = Level::SCHOOL;
		school_lvl = true;
		normal_lvl = false;
		erudite_lvl = false;
	}
	if (normal.getGlobalBounds().contains(pos.x, pos.y))
	{
		normal.setFillColor(sf::Color::Blue);
		mset.level = Level::NORMAL;
		normal_lvl = true;
		erudite_lvl = false;
		school_lvl = false;
	}
	if (erudite.getGlobalBounds().contains(pos.x, pos.y))
	{
		erudite.setFillColor(sf::Color::Blue);
		mset.level = Level::ERUDITE;
		erudite_lvl = true;
		school_lvl = false;
		normal_lvl = false;
	}
}

void Menu::drawMenu(sf::RenderWindow& window)
{
	window.draw(start);
	window.draw(lang);
	window.draw(ua);
	window.draw(ru);
	window.draw(lttrs);
	window.draw(three);
	window.draw(four);
	window.draw(lvl);
	window.draw(school);
	window.draw(normal);
	window.draw(erudite);
}