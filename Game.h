#pragma once
#include <SFML/Graphics.hpp>
#include "Dictionary.h"

class MyRectangleShape : public sf::RectangleShape
{
	using RectangleShape::RectangleShape;

public:
	bool isfull = false;
};

class MyLetterSprite : public sf::Sprite
{
	using Sprite::Sprite;

public:
	char letter;
	bool isHidden = false;
	sf::Vector2i startpos;
	MyRectangleShape* rec = nullptr;
	void setStartPosition(int x, int y) { startpos.x = x; startpos.y = y; setStartPosition(); }
	void setStartPosition() { setPosition(startpos.x, startpos.y); }
};

class Game
{
	const int alphabet_size = 33;
	Letters letters;
	void setGame();

public:

	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;
	bool isMove = false, isHide = false;
	float dX = 0;
	float dY = 0;
	MyLetterSprite* myspr = nullptr;
	Dictionary dictionary;
	sf::RectangleShape resultrect1, resultrect2;
	sf::Text result_text, win_text, menu_text;
	sf::Font font;
	string word;

	Game(MenuSettings);
	void letterInit();
	bool rectanglesFull();
	int wordSize() { return int(letters); }
	pair<int, int> getResult() { return dictionary.get_result(word); }
};
