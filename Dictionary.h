#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <random> 
#include "functions.h"

enum class Language
{
	UKR,
	RUS,
};

enum class Letters
{
	THREE = 3,
	FOUR
};

enum class Level
{
	SCHOOL,
	NORMAL,
	ERUDITE
};

struct MenuSettings
{
	Language language;
	Letters letters;
	Level level;
	MenuSettings() : language{ Language::UKR }, letters{ Letters::THREE }, level{ Level::SCHOOL } {}
};

class Dictionary
{
	unordered_map<string, string> current_dict, second_dict, third_dict, combined_dict;
	Language language;
	Letters letters;
	Level level;
	string folder, prefix, prefix_lvl, prefix_lvl2, prefix_lvl3;
	string get_filename(const string& lvlstr) { return folder + prefix + lvlstr + ".txt"; }
	string hidden_word;
	void fill_dict(unordered_map<string, string>& dict, const string& fname1, const string& fname2);
	void fill_all_dicts();
	void clear_all_dicts();
	string get_random_word();

public:
	Dictionary(Language lang, Letters lttrs, Level lvl);
	void set(Language lang, Letters lttrs, Level lvl);
	void set_language(Language lang);
	void set_letters(Letters lttrs);
	void set_level(Level lvl);
	void print_words(ostream& os);
	string hword_explanation();
	pair<int, int> get_result(const string&);
	bool is_wrong_word(const string&);
};
