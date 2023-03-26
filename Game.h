#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Dictionary.h"

//----------------------------------------------------------------------------------------------------

enum class SOUND
{
	OFF,
	ON
};

//----------------------------------------------------------------------------------------------------

struct Settings
{
	Language language;
	Letters letters;
	Level level;
	Guesser guesser;
	SOUND sound;
	bool restart;
	Settings() 
		: language{ Language::UKR }, letters{ Letters::THREE }, 
		level{ Level::SCHOOL }, guesser{ Guesser::PLAYER },
		sound{ SOUND::ON }, restart{ false } {}
};

//----------------------------------------------------------------------------------------------------

class GameText : public sf::Text
{
public:
	using sf::Text::Text;
	bool underMouse = false;
};

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
	Settings settings;
	const int alphabet_size;
	Dictionary dictionary;
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
	sf::Texture winimagetexture, soundontexture, soundofftexture;
	sf::Sprite winimagesprite, soundsprite;
	sf::SoundBuffer winsoundbuffer, inrectsoundbuffer, allrectsoundbuffer, wrongsoundbuffer, arrowsoundbuffer, hidsoundbuffer, tostartsoundbuffer, startgamesoundbuffer, hoversoundbuffer, clicksoundbuffer;
	sf::Sound winsound, inrectsound, allrectsound, wrongsound, arrowsound, hidsound, tostartsound, startgamesound, hoversound, clicksound;
	sf::Font font, font2;
	GameText word_text, result_text, up_text, win_text, menu_text, wrong_action_text, word_expl_text, clue_text, restart_text;
	vector<sf::Text> history, clues;
	vector<string> history_vs, clue_words;
	set<char> hidden_letters;
	set<string> strset;
	unordered_map<string, pair<int, int>> comp_words;

	void setGame();
	void setOneImage(const std::string&, sf::Texture&, sf::Sprite&);
	void setImages();
	void setOneSound(const std::string&, sf::SoundBuffer&, sf::Sound&);
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
	void drawAll(sf::RenderWindow&);
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
	void explTextFormatting(sf::RenderWindow&, sf::Text&, wstring&);
	void wordExplaining(sf::RenderWindow&);
	void hoverActions(GameText&, sf::Color, sf::Color, bool);

	void oneTimeLeftActions();
	void oneTimeRightActions();
	void actions();

public:
	Game(Settings);
	Settings play(sf::RenderWindow& window);
};
