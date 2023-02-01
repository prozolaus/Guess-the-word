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
	std::vector<sf::Texture> textures, result_textures;
	std::vector<MyLetterSprite> sprites, result_sprites, result_sprites2;
	std::vector<MyRectangleShape> rectangles;
	MyLetterSprite* myspr = nullptr;
	sf::RectangleShape resultrect1, resultrect2;
	sf::Text result_text, win_text, menu_text, wrong_word_text, word_expl_text, clue_text, restart_text;
	vector<sf::Text> history, clues;
	sf::Font font;
	string word;
	vector<string> history_vs, clue_words;
	vector<char> hidden_letters;
	void setGame();
	void setText();
	void setResultRect(sf::RectangleShape& rect, float x);

public:
	Game(MenuSettings);
	void setMotion(bool m) { motion = m; }
	void setHiding(bool h) { hiding = h; }
	bool getMotion() const { return motion; }
	bool getHiding() const { return hiding; }
	void setdX(float dx) { dX = dx; }
	void setdY(float dy) { dY = dy; }
	float getdX() const { return dX; }
	float getdY() const { return dY; }
	sf::Color getBgColor() const { return bgcolor; }
	Language getLanguage() const { return language; }
	int wordSize() { return int(letters); }
	void setLetterInWord(int i, char l) { word.at(i) = l; }
	void letterInit();
	bool allRectanglesFull();
	bool isWrongWord();
	void drawAll(sf::RenderWindow& window);
	bool isAnySpriteContain(int, int);
	bool isAnySpriteinRect(int, int);
	void resetCurrentSprite();
	void moveSprite(int x, int y);
	void setSpriteHidingOptions();
	void resetResultSprites();
	void resetRectangleLetters();
	void setMenuTextColor(sf::Color c) { menu_text.setFillColor(c); }
	bool isMenuTextContain(int x, int y) { return menu_text.getGlobalBounds().contains(x, y); }
	void setRestartTextColor(sf::Color c) { restart_text.setFillColor(c); }
	bool isRestartTextContain(int x, int y) { return restart_text.getGlobalBounds().contains(x, y); }
	void setClueTextColor(sf::Color c) { clue_text.setFillColor(c); }
	bool isClueTextContain(int x, int y) { return clue_text.getGlobalBounds().contains(x, y); }
	void setExplTextColor(sf::Color c) { word_expl_text.setFillColor(c); }
	bool isExplTextContain(int x, int y) { return word_expl_text.getGlobalBounds().contains(x, y); }
	void setWrongWordTextColor(sf::Color c) { wrong_word_text.setFillColor(c); }
	void resultHandling();
	wstring getWordExplanation() { return filesystem::path(dictionary.word_explanation(word)).wstring(); }
	void updateClueWords();
	void hideClues();
};
