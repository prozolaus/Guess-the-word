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
	int number;
	bool hiding = false;
	MyRectangleShape* rec = nullptr;
	sf::Vector2i startpos;

public:
	void setLetter(char l) { letter = l; }
	char getLetter() const { return letter; }
	void setNumber(int n) { number = n; }
	int getNumber() const { return number; }
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
	sf::Vector2u window_size;
	const int alphabet_size;
	Dictionary dictionary;
	Language language;
	Letters letters;
	Guesser guesser;
	int word_size;
	bool motion, hiding;
	float dX, dY;
	sf::Vector2i pixelPos;
	sf::Color bgcolor, hidcolor;
	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles, result_rects;
	MyLetterSprite* myspr = nullptr;
	sf::CircleShape dot1, dot2;
	sf::Text word_text, result_text, win_text, menu_text, wrong_action_text, word_expl_text, clue_text, restart_text;
	vector<sf::Text> history, clues;
	sf::Font font;
	string word;
	pair<int, int> result;
	int fncount, firstsetcount;
	vector<string> history_vs, clue_words;
	set<char> hidden_letters;
	set<string> strset;
	bool isEmptyFirstSet, noOptions;
	unordered_map<string, pair<int, int>> comp_words;
	void setGame();
	void setText();
	void setResultRect(sf::RectangleShape& rect, float x);
	void setResultDot(sf::CircleShape& dot, int y);
	void lettersInit();
	bool allRectanglesFull();
	void drawAll(sf::RenderWindow& window);
	bool isAnySpriteContainMousePos();
	bool isAnySpriteinRect();
	void resetCurrentSprite();
	void moveSprite();
	void setSpriteHidingOptions();
	void resetResultSprites();
	void resetSprites();
	void resetRectangleLetters();
	void resetResultRectNumbers();
	void addWordToHistory();
	void resultHandling();
	void updateClueWords();
	void hideClues();
	void nextWordFromSet();
	void updateSet();

	void oneTimeLeftActions();
	void oneTimeRightActions();
	void actions();
	void explTextFormatting(sf::RenderWindow& window, sf::Text&, wstring& ws);
	void wordExplaining(sf::RenderWindow& window);

public:
	Game(MenuSettings, sf::Vector2u);
	bool play(sf::RenderWindow& window);
};
