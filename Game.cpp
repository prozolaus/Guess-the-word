#include "Game.h"

Game::Game(MenuSettings ms)
	: dictionary{ ms.language, ms.letters, ms.level },
	letters{ ms.letters },
	textures{ alphabet_size },
	result_textures{ wordSize() + 1 }
{
	setGame();
}

void Game::setGame()
{
	for (int i = 0; i < alphabet_size; i++)
	{
		std::string s = "letters\\" + std::to_string(i) + ".png";
		textures[i].loadFromFile(s);
	}
	for (int i = 0, count = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			if (count == 33)
				break;
			sprites.push_back(MyLetterSprite{ textures[count++] });
			sprites.back().setStartPosition(j * 64, i * 64);
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
		result_sprites.back().setStartPosition(-200, i * 64);
		result_sprites2.push_back(MyLetterSprite{ result_textures[i] });
		result_sprites2.back().setStartPosition(-100, i * 64);
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
	win_text.setFillColor(sf::Color::Magenta);
	win_text.move(300, 550);
	win_text.setString("Congratulations!");
	win_text.setCharacterSize(40);
	menu_text.setFont(font);
	menu_text.setFillColor(sf::Color::Black);
	menu_text.move(620, 20);
	menu_text.setString("Menu");
}

void Game::letterInit()
{
	int count = -32;
	for (int i = 0; i < alphabet_size; i++)
	{
		if (i == 4)
			sprites[i].letter = char(-76);	//´
		else if (i == 7)
			sprites[i].letter = char(-70);	//º
		else if (i == 11)
			sprites[i].letter = char(-77);	//³
		else if (i == 12)
			sprites[i].letter = char(-65);	//¿
		else if (i == 30)
			sprites[i].letter = char(-4);	//ü
		else if (i == 31)
			sprites[i].letter = char(-2);	//þ
		else if (i == 32)
			sprites[i].letter = char(-1);	//ÿ
		else
			sprites[i].letter = char(count++);
	}
}

bool Game::rectanglesFull()
{
	for (int i = 0; i < rectangles.size(); i++)
		if (rectangles[i].isfull == false)
			return false;
	return true;
}
