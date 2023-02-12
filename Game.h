#pragma once
#include <SFML/Graphics.hpp>
#include "Dictionary.h"


//----------------------------------------------------------------------------------------------------

class MyRectangleShape : public sf::RectangleShape
{
	using RectangleShape::RectangleShape;
	bool filling = false;

public:
	void setFilling(bool f) { filling = f; }
	bool getFilling() const { return filling; }
};

//----------------------------------------------------------------------------------------------------


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

//----------------------------------------------------------------------------------------------------

class Game
{
	const int alphabet_size;
	Dictionary dictionary;
	Language language;
	Letters letters;
	int word_size;
	bool motion, hiding;
	float dX, dY;
	sf::Vector2i pixelPos;
	sf::Color bgcolor;
	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;
	MyLetterSprite* myspr = nullptr;
	sf::RectangleShape resultrect1, resultrect2;
	sf::CircleShape dot1, dot2;
	sf::Text result_text, win_text, menu_text, wrong_word_text, word_expl_text, clue_text, restart_text;
	vector<sf::Text> history, clues;
	sf::Font font;
	string word;
	vector<string> history_vs, clue_words;
	vector<char> hidden_letters;
	void setGame();
	void setText();
	void setResultRect(sf::RectangleShape& rect, float x);
	void setResultDot(sf::CircleShape& dot, int y);
	void letterInit();
	bool allRectanglesFull();
	void drawAll(sf::RenderWindow& window);
	bool isAnySpriteContainMousePos();
	bool isAnySpriteinRect();
	void resetCurrentSprite();
	void moveSprite();
	void setSpriteHidingOptions();
	void resetResultSprites();
	void resetRectangleLetters();
	void resultHandling();
	void updateClueWords();
	void hideClues();

	void oneTimeLeftActions();
	void oneTimeRightActions();
	void actions();
	void explTextFormatting(sf::RenderWindow& window, sf::Text&, wstring& ws);
	void wordExplaining(sf::RenderWindow& window);

public:
	Game(MenuSettings);
	bool play(sf::RenderWindow& window);
};
