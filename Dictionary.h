#pragma once
#include <fstream>
#include <string>
#include <Windows.h>
#include <unordered_map>
#include <set>
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

enum class Guesser
{
	COMPUTER,
	PLAYER
};

enum class FirstSetSizeFor
{
	THREE = 9,
	FOUR = 7
};



class Dictionary
{
	unordered_map<string, string> current_dict, second_dict, third_dict, combined_dict;
	Language language;
	Letters letters;
	Level level;
	string folder, prefix, prefix_lvl, prefix_lvl2, prefix_lvl3, hidden_word;
	string get_filename(const string& lvlstr) { return folder + prefix + lvlstr + ".txt"; }
	void fill_dict(unordered_map<string, string>& dict, const string& fname1, const string& fname2);
	void fill_all_dicts();
	void clear_all_dicts();
	string get_random_word();
	bool is_set_contain_letters(const std::set<string>& ss, const string& s);
	bool is_word_contain_hidletters(const string& word, const std::set<char>& hidden_letters);
	bool is_word_from_history(const string& word, const vector<string>& words_from_history);

public:
	Dictionary(Language lang, Letters lttrs, Level lvl);
	void set(Language lang, Letters lttrs, Level lvl);
	string word_explanation(const string&);
	pair<int, int> get_result(const string&);
	pair<int, int> get_result(const string&, const string&);
	bool is_wrong_word(const string&);
	vector<string> get_clue_words(unordered_map<unsigned int, char>, const vector<string>&, const std::set<char>&, const unsigned int n = 5);
	std::set<string> generate_first_set();
	std::set<string> generate_another_set(const vector<string>&, const std::set<char>&);
};
