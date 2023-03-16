#include "Menu.h"

MenuText::MenuText(const string& text) : Text()
{
	fontname = "fonts\\Academy.ttf";
	if (!font.loadFromFile(fontname))
		throw runtime_error("Game::setGame(): cannot open a font file " + fontname);
	Text::setFont(font);
	Text::setString(text);
	Text::setFillColor(sf::Color::Black);
	Text::setCharacterSize(25);
}

void MenuText::setFont(const sf::Font& f)
{
	font = f;
	Text::setFont(font);
}

//------------------------------------------------------------------------------------------------


Menu::Menu(unsigned int window_width, unsigned int window_height)
	: start{ "START" },
	lang{ "Language:" }, ua{ "UA" }, ru{ "RU" },
	guesser{ "Guesser:" }, player{ "player" }, computer{ "computer" },
	lttrs{ "Letters:" }, three{ "three" }, four{ "four" },
	lvl{ "Level:" }, school{ "school" }, normal{ "normal" }, erudite{ "erudite" },
	UA_lang{ false }, RU_lang{ false },
	player_guesses{ false }, comp_guesses{ false },
	three_ls{ false }, four_ls{ false },
	school_lvl{ false }, normal_lvl{ false }, erudite_lvl{ false }
{
	start.setPosition(window_width / 2 - start.getGlobalBounds().width / 2, window_height / 2);
	ua.setPosition(x + lang.getGlobalBounds().width + x / 3, y);
	ru.setPosition(ua.getPosition().x + x / 2, y);
	player.setPosition(ua.getPosition().x, 1.5 * y);
	three.setPosition(ua.getPosition().x, 2 * y);
	four.setPosition(three.getPosition().x + three.getGlobalBounds().width + x / 3, 2 * y);
	school.setPosition(three.getPosition().x, 2.5 * y);
	TextCorrection();
}


void Menu::changeLangToUKR()
{
	start.setString(L"СТАРТ");
	lang.setString(L"Мова:");
	guesser.setString(L"Вгадує:");
	guesser.setPosition(x, 1.5 * y);
	player.setString(L"гравець");
	computer.setString(L"комп'ютер");
	lttrs.setString(L"Літери:");
	three.setString(L"три");
	four.setString(L"чотири");
	lvl.setString(L"Рівень:");
	school.setString(L"шкільний");
	normal.setString(L"нормальний");
	erudite.setString(L"ерудит");
	TextCorrection();
}

void Menu::changeLangToRUS()
{
	start.setString(L"СТАРТ");
	lang.setString(L"Язык:");
	guesser.setString(L"Отгадывает:");
	guesser.setPosition(x - 20, 1.5 * y);
	player.setString(L"игрок");
	computer.setString(L"компьютер");
	lttrs.setString(L"Буквы:");
	three.setString(L"три");
	four.setString(L"четыре");
	lvl.setString(L"Уровень:");
	school.setString(L"школьный");
	normal.setString(L"нормальный");
	erudite.setString(L"эрудит");
	TextCorrection();
}

void Menu::TextCorrection()
{
	int shift = RU_lang ? 30 : 0;
	lang.setPosition(x - shift, y);
	guesser.setPosition(x - shift, 1.5 * y);
	lttrs.setPosition(x - shift, 2 * y);
	lvl.setPosition(x - shift, 2.5 * y);
	computer.setPosition(player.getPosition().x + player.getGlobalBounds().width + x / 3, 1.5 * y);
	normal.setPosition(school.getPosition().x + school.getGlobalBounds().width + x / 3, 2.5 * y);
	erudite.setPosition(normal.getPosition().x + normal.getGlobalBounds().width + x / 3, 2.5 * y);
}


void Menu::setAllTextBlack()
{
	start.setFillColor(sf::Color::Black);
	if (!UA_lang) ua.setFillColor(sf::Color::Black);
	if (!RU_lang) ru.setFillColor(sf::Color::Black);
	if (!player_guesses) player.setFillColor(sf::Color::Black);
	if (!comp_guesses) computer.setFillColor(sf::Color::Black);
	if (!three_ls) three.setFillColor(sf::Color::Black);
	if (!four_ls) four.setFillColor(sf::Color::Black);
	if (!school_lvl) school.setFillColor(sf::Color::Black);
	if (!normal_lvl) normal.setFillColor(sf::Color::Black);
	if (!erudite_lvl) erudite.setFillColor(sf::Color::Black);
}

void Menu::colorChanging(MenuText& mt, bool b)
{
	if (mt.getGlobalBounds().contains(pos.x, pos.y))
		b ? mt.setFillColor(sf::Color::Blue) : mt.setFillColor(sf::Color::Green);
}

void Menu::changeColorOnHover()
{
	colorChanging(ua, UA_lang);
	colorChanging(ru, RU_lang);
	colorChanging(player, player_guesses);
	colorChanging(computer, comp_guesses);
	colorChanging(three, three_ls);
	colorChanging(four, four_ls);
	colorChanging(school, school_lvl);
	colorChanging(normal, normal_lvl);
	colorChanging(erudite, erudite_lvl);
	if (isStartGame())
		start.setFillColor(sf::Color::Blue);
}

bool Menu::isStartGame()
{
	return start.getGlobalBounds().contains(pos.x, pos.y) 
		&& (UA_lang || RU_lang) 
		&& (three_ls || four_ls) 
		&& (comp_guesses || player_guesses && (school_lvl || normal_lvl || erudite_lvl))
		? true : false;
}

void Menu::mouseClickHandling()
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
	if (player.getGlobalBounds().contains(pos.x, pos.y))
	{
		player.setFillColor(sf::Color::Blue);
		mset.guesser = Guesser::PLAYER;
		player_guesses = true;
		comp_guesses = false;
	}
	if (computer.getGlobalBounds().contains(pos.x, pos.y))
	{
		computer.setFillColor(sf::Color::Blue);
		mset.guesser = Guesser::COMPUTER;
		comp_guesses = true;
		player_guesses = false;
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
	window.clear(sf::Color{ 255, 255, 102 });
	window.draw(start);
	window.draw(lang);
	window.draw(ua);
	window.draw(ru);
	window.draw(guesser);
	window.draw(player);
	window.draw(computer);
	window.draw(lttrs);
	window.draw(three);
	window.draw(four);
	if (!comp_guesses)
	{
		window.draw(lvl);
		window.draw(school);
		window.draw(normal);
		window.draw(erudite);
	}
}