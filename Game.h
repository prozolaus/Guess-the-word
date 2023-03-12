#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	char letter = ' ';
	int number = -1;
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
	const int sprite_size;
	int word_size, fncount, firstsetcount;
	bool motion, hiding, isEmptyFirstSet, noOptions, gameover;
	float dX, dY;
	sf::Vector2i pixelPos;
	sf::Color defsprcolor, bgcolor, hidcolor, wincolor;
	std::vector<sf::Texture> textures, result_textures;
	MyLetterSprite* myspr;
	pair<int, int> result;
	string word, winword;
	std::vector<MyLetterSprite> letter_sprites;
	std::pair<std::vector<MyLetterSprite>, std::vector<MyLetterSprite>> result_sprites;
	std::vector<MyRectangleShape> letter_rectangles, result_rectangles;
	sf::CircleShape dot1, dot2;
	sf::Texture winimagetexture;
	sf::Sprite winimagesprite;
	sf::SoundBuffer winsoundbuffer;
	sf::Sound winsound;
	sf::Font font, font2;
	sf::Text word_text, result_text, up_text, win_text, menu_text, wrong_action_text, word_expl_text, clue_text, restart_text;
	vector<sf::Text> history, clues;
	vector<string> history_vs, clue_words;
	set<char> hidden_letters;
	set<string> strset;
	unordered_map<string, pair<int, int>> comp_words;

	void setGame();
	void setImages();
	void setSounds();
	void setTextures();
	void setLetterSprites();
	void setLetterRectangles();
	void setResultSprites(std::vector<MyLetterSprite>&, int);
	void setResultRect(sf::RectangleShape& rect, float x);
	void setResultDot(sf::CircleShape& dot, int y);
	void setFonts();
	void setText();
	void lettersInit();

	bool allRectanglesFull();
	void drawAll(sf::RenderWindow& window);
	bool isAnySpriteContainMousePos();
	bool isAnySpriteinRect();
	void resetCurrentSprite();
	void moveSprite();
	void setSpriteHidingOptions();
	void resetResultSprites();
	void resetLetterSprites();
	void resetRectangleLetters();
	void resetResultRectNumbers();
	void resetAfterArrowClick();
	void addWordToHistory();
	void resultHandling();
	bool isWinwordContainLetter(char);
	void winHandling();
	void updateClueWords();
	void hideClues();
	void nextWordFromSet();
	void updateSet();
	void compGuessing();

	void oneTimeLeftActions();
	void oneTimeRightActions();
	void actions();
	void explTextFormatting(sf::RenderWindow& window, sf::Text&, wstring& ws);
	void wordExplaining(sf::RenderWindow& window);

public:
	Game(MenuSettings, sf::Vector2u);
	bool play(sf::RenderWindow& window);
};
