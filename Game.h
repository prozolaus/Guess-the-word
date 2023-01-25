#pragma once
#include <SFML/Graphics.hpp>
#include "Dictionary.h"

class MyRectangleShape : public sf::RectangleShape
{
	using RectangleShape::RectangleShape;
	bool filling = false;

public:
	void setFilling(bool f) { filling = f; }
	bool getFilling() const { return filling; }
};

class MyLetterSprite : public sf::Sprite
{
	using Sprite::Sprite;
	char letter;
	bool hiding = false;
	MyRectangleShape* rec = nullptr;
	sf::Vector2i startpos;

public:
	void setLetter(char l) { letter = l; }
	char getLetter() const { return letter; }
	void setLetterHiding(bool lh) { hiding = lh; }
	bool getLetterHiding() const { return hiding; }
	void connectRectangle(MyRectangleShape* myrecshape) { rec = myrecshape; }
	MyRectangleShape* getConnectedRectangle() const { return rec; }
	void setStartCoords(int x, int y) { startpos.x = x; startpos.y = y; setStartPosition(); }
	void setStartPosition() { setPosition(startpos.x, startpos.y); }
};

class Game
{
	const int alphabet_size;
	Dictionary dictionary;
	Language language;
	Letters letters;
	bool motion, hiding;
	float dX, dY;
	sf::Color bgcolor;
	void setGame();
	void setText();
	void setResultRect(sf::RectangleShape& rect, float x);

public:

	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;

	MyLetterSprite* myspr = nullptr;
	sf::RectangleShape resultrect1, resultrect2;
	sf::Text result_text, win_text, menu_text, wrong_word_text;
	vector<sf::Text> history;
	sf::Font font;
	string word;

	Game(MenuSettings);
	void setMotion(bool m) { motion = m; }
	void setHiding(bool h) { hiding = h; }
	bool getMotion() const { return motion; }
	bool getHiding() const { return hiding; }
	void setdX(float dx) { dX = dx; }
	void setdY(float dy) { dY = dy; }
	float getdX() const { return dX; }
	float getdY() const { return dY; }
	void setLetterInWord(int i, char l) { word.at(i) = l; }
	void letterInit();
	bool allRectanglesFull();
	bool isWrongWord();
	int wordSize() { return int(letters); }
	pair<int, int> getResult() { return dictionary.get_result(word); }
	void drawAll(sf::RenderWindow& window);
};
