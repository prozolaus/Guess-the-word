#include "Game.h"

Game::Game(MenuSettings ms)
	: alphabet_size{ 33 },
	dictionary{ ms.language, ms.letters, ms.level },
	language{ ms.language },
	letters{ ms.letters },
	motion{ false }, hiding{ false },
	dX{ 0 }, dY{ 0 },
	textures{ alphabet_size },
	result_textures{ wordSize() + 1 },
	bgcolor{sf::Color::White}
{
	setGame();
}

void Game::setGame()
{
	for (int i = 0; i < alphabet_size; i++)
	{
		string lng = language == Language::UKR ? "ukr\\" : "rus\\";
		string s = "letters\\" + lng + std::to_string(i) + ".png";
		textures[i].loadFromFile(s);
	}
	for (int i = 0, count = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			if (count == 33)
				break;
			sprites.push_back(MyLetterSprite{ textures[count++] });
			sprites.back().setStartCoords(j * 64, i * 64);
		}
	rectangles.assign(wordSize(), MyRectangleShape{ sf::Vector2f(64.f, 64.f) });
	for (int i = 0; i < rectangles.size(); i++)
	{
		rectangles[i].setFillColor(sf::Color(175, 180, 240));
		rectangles[i].move(100 + i * 64, 450);
		rectangles[i].setOutlineColor(sf::Color::Black);
		rectangles[i].setOutlineThickness(1.f);
	}
	for (int i = 0; i <= wordSize(); i++)
	{
		std::string s = "numbers\\" + std::to_string(i) + ".png";
		result_textures[i].loadFromFile(s);
		result_sprites.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites.back().setStartCoords(-200, i * 64);
		result_sprites2.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites2.back().setStartCoords(-100, i * 64);
	}
	resultrect1 = sf::RectangleShape{ sf::Vector2f(64.f, 64.f) };
	resultrect2 = sf::RectangleShape{ sf::Vector2f(64.f, 64.f) };
	resultrect1.move(116.f, 550.f);
	resultrect1.setFillColor(sf::Color::Yellow);
	resultrect1.setOutlineColor(sf::Color::Black);
	resultrect1.setOutlineThickness(1.f);
	resultrect2.move(212.f, 550.f);
	resultrect2.setFillColor(sf::Color::Yellow);
	resultrect2.setOutlineColor(sf::Color::Black);
	resultrect2.setOutlineThickness(1.f);
	word.resize(wordSize());
	letterInit();
	font.loadFromFile("Bebas_Neue_Cyrillic.ttf");
	result_text.setFont(font);
	result_text.setFillColor(sf::Color::Blue);
	result_text.move(20, 560);
	result_text.setString("Result:");
	win_text.setFont(font);
	win_text.setFillColor(bgcolor);
	win_text.move(300, 550);
	win_text.setString("Congratulations!");
	win_text.setCharacterSize(40);
	menu_text.setFont(font);
	menu_text.setFillColor(sf::Color::Black);
	menu_text.move(620, 20);
	menu_text.setString("Menu");
	wrong_word_text.setFont(font);
	wrong_word_text.setFillColor(bgcolor);
	wrong_word_text.move(20, 650);
	wrong_word_text.setString("There is no such word in the database!");
}

bool Game::isWrongWord()
{
	if (dictionary.is_wrong_word(word))
	{
		wrong_word_text.setFillColor(sf::Color::Red);
		return true;
	}
	wrong_word_text.setFillColor(bgcolor);
	return false;
}

void Game::letterInit()
{
	int count = -32;
	if (language == Language::UKR)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 4)
				sprites[i].setLetter(char(-76));	//´
			else if (i == 7)
				sprites[i].setLetter(char(-70));	//º
			else if (i == 11)
				sprites[i].setLetter(char(-77));	//³
			else if (i == 12)
				sprites[i].setLetter(char(-65));	//¿
			else if (i == 30)
				sprites[i].setLetter(char(-4));	//ü
			else if (i == 31)
				sprites[i].setLetter(char(-2));	//þ
			else if (i == 32)
				sprites[i].setLetter(char(-1));	//ÿ
			else
				sprites[i].setLetter(char(count++));
		}
	else if (language == Language::RUS)
		for (int i = 0; i < alphabet_size; i++)
		{
			if (i == 6)
				sprites[i].setLetter(char(-72));	//¸
			else
				sprites[i].setLetter(char(count++));
		}
}

bool Game::allRectanglesFull()
{
	for (int i = 0; i < rectangles.size(); i++)
		if (rectangles[i].getFilling() == false)
			return false;
	return true;
}
