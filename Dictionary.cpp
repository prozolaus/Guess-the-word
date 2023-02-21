#include "Dictionary.h"

Dictionary::Dictionary(Language lang, Letters lttrs, Level lvl)
	: folder{"dicts\\"}
{
	set(lang, lttrs, lvl);
}

void Dictionary::set(Language lang, Letters lttrs, Level lvl)
{
	language = lang, letters = lttrs, level = lvl;
	fill_all_dicts();
}

void Dictionary::fill_dict(unordered_map<string, string>& dict, const string& fname1, const string& fname2)
{
	ifstream ifs_words{ fname1 }, ifs_expl{ fname2 };
	if (!ifs_words)
		throw runtime_error("Cannot open " + fname1);
	if (!ifs_expl)
		throw runtime_error("Cannot open " + fname2);
	int word_count = 0, expl_count = 0;
	while (true)
	{
		string word, word_expl;
		getline(ifs_words, word);
		getline(ifs_expl, word_expl);
		if (!ifs_words || !ifs_expl)
			break;
		if (word.size() != (int)letters)
			throw runtime_error(fname1 + ": wrong size of word: " + word);
		
		if (word_expl.find('#') != std::string::npos)
			while (!(word_expl.back() == '#'))
				word_expl.pop_back();
		else
			throw runtime_error(fname2 + ": No # in explanation string end: " + word_expl);
			
		word_expl.pop_back(); //delete #
		if (word_expl.empty())
			throw runtime_error(fname2 + ", string " + to_string(expl_count + 1) + " - an empty string: " + word_expl);
		if (word_expl.size() < 5)
			throw runtime_error(fname2 + ", string " + to_string(expl_count + 1) + ": the explanation is too short: " + word_expl);
		dict[word] = word_expl;
		word_count++; expl_count++;
	}
	if (!(word_count == expl_count && expl_count == dict.size()))
	{
		cerr << "word_count = " << word_count << endl;
		cerr << "expl_count = " << expl_count << endl;
		cerr << "current_dict.size() = " << current_dict.size() << endl;
		throw runtime_error(fname1 + " and " + fname2 + ": the number of words is not equal to the number of explanation lines.");
	}
}

void Dictionary::fill_all_dicts()
{
	clear_all_dicts();

	if (language == Language::UKR) prefix = "ukr";
	else if (language == Language::RUS) prefix = "rus";
	if (letters == Letters::THREE) prefix += "_3";
	else if (letters == Letters::FOUR) prefix += "_4";
	if (level == Level::SCHOOL) { prefix_lvl = "_school"; prefix_lvl2 = "_normal"; prefix_lvl3 = "_erudite"; }
	else if (level == Level::NORMAL) { prefix_lvl = "_normal"; prefix_lvl2 = "_school"; prefix_lvl3 = "_erudite"; }
	else if (level == Level::ERUDITE) { prefix_lvl = "_erudite"; prefix_lvl2 = "_school"; prefix_lvl3 = "_normal"; }

	fill_dict(current_dict, get_filename(prefix_lvl), get_filename(prefix_lvl + "_expl"));
	fill_dict(second_dict, get_filename(prefix_lvl2), get_filename(prefix_lvl2 + "_expl"));
	fill_dict(third_dict, get_filename(prefix_lvl3), get_filename(prefix_lvl3 + "_expl"));

	combined_dict.insert(current_dict.begin(), current_dict.end());
	combined_dict.insert(second_dict.begin(), second_dict.end());
	combined_dict.insert(third_dict.begin(), third_dict.end());

	hidden_word = get_random_word();
}

void Dictionary::set_language(Language lang)
{
	language = lang;
	fill_all_dicts();
}

void Dictionary::set_letters(Letters lttrs)
{
	letters = lttrs;
	fill_all_dicts();
}

void Dictionary::set_level(Level lvl)
{
	level = lvl;
	fill_all_dicts();
}

void Dictionary::clear_all_dicts()
{
	current_dict.clear(), second_dict.clear(), third_dict.clear(), combined_dict.clear();
}

void Dictionary::print_words(ostream& os)
{
	for (const auto& p : current_dict)
		os << p.first << endl;
}

string Dictionary::get_random_word()
{
	random_device rd;
	mt19937 mersenne{ rd() };
	auto iter = current_dict.begin();
	advance(iter, mersenne()%current_dict.size());
	return  (*iter).first;
}

string Dictionary::word_explanation(const string& word)
{
	if (combined_dict.find(word) == combined_dict.end())
		throw runtime_error("Dictionary::word_explanation(): no such word in the database!");
	return combined_dict[word];
}

pair<int, int> Dictionary::get_result(const string& pword)
{
	if (pword.size() != (int)letters)
		throw runtime_error("Dictionary::get_result(pword): Wrong pword.size()!");
	return (letters == Letters::THREE ? get_result_for_3_letters(hidden_word, pword) : get_result_for_4_letters(hidden_word, pword));
}

pair<int, int> Dictionary::get_result(const string& word1, const string& word2)
{
	if (word1.size() != (int)letters || word2.size() != (int)letters)
		throw runtime_error("Dictionary::get_result(word1, word2): Wrong word.size()!");
	return (letters == Letters::THREE ? get_result_for_3_letters(word1, word2) : get_result_for_4_letters(word1, word2));
}

bool Dictionary::is_wrong_word(const string& word)
{
	return (combined_dict.find(word) != combined_dict.end()) ? false : true;
}

std::set<string> Dictionary::generate_another_set(const vector<string>& words_from_history, const std::set<char>& hidden_letters)
{
	std::set<string> ss;
	for (const auto& cd : combined_dict)
	{
		bool hidletter = false;
		for (int i = 0; i < cd.first.size() && !hidletter; i++)
			for (auto chit = hidden_letters.begin(); chit != hidden_letters.end() && !hidletter; ++chit)
				if (cd.first[i] == *chit)
					hidletter = true;
		bool isFromHistory = false;
		for (auto w : words_from_history) if (w == cd.first) isFromHistory = true;
		if (!hidletter && !isFromHistory)
			ss.insert(cd.first);
	}
	return ss;
}

vector<string> Dictionary::get_clue_words(unordered_map<unsigned int, char> map,
	const vector<string>& words_from_history, const std::set<char>& hidden_letters, const unsigned int n)
{
	string s1 = "Dictionary::get_some_words(unordered_map<int, char> map): map ";
	string s2 = " must be less than word length";
	if (map.size() > (int)letters - 1)
		throw runtime_error(s1 + "size" + s2);
	for (auto m : map)
		if (m.first > (int)letters - 1)
			throw runtime_error(s1 + "key" + s2);

	int count;
	vector<string> vs;
	for (const auto& cd : combined_dict)
	{
		count = 0;
		for (auto m : map) 
			if (cd.first[m.first] == map[m.first])
				count++;
		if (count == map.size())
		{
			bool hidletter = false;
			for (int i = 0; i < cd.first.size() && !hidletter; i++)
				for (auto chit = hidden_letters.begin(); chit != hidden_letters.end() && !hidletter; ++chit)
					if (cd.first[i] == *chit)
						hidletter = true;
			bool isFromHistory = false;
			for (auto w : words_from_history) if (w == cd.first) isFromHistory = true;
			if (!hidletter && !isFromHistory) 
				vs.push_back(cd.first);
		}
		if (vs.size() == n)
			break;
	}
	if (vs.size() == 0)
		vs.push_back(language == Language::UKR ? "Не знайдено слів" : "Не найдено слов");
	return vs;
}

bool Dictionary::is_set_contain_letters(const std::set<string>& ss, const string& s)  //Does string s contain letters from set?
{
	for (string x : ss)
		for (int i = 0; i < x.size(); i++)
			for (int j = 0; j < s.size(); j++)
				if (x[i] == s[j])
					return true;
	return false;
}

std::set<string> Dictionary::generate_set()
{
	std::set<string> ss;
	const int n = letters == Letters::THREE ? 9 : 7;
	while (ss.size() < n)
	{
		ss.clear();
		random_device rd;
		mt19937 mersenne{ rd() };
		for (int i = 0; i < combined_dict.size() && ss.size() < n; i++)
		{
			auto iter = combined_dict.begin();
			advance(iter, mersenne() % combined_dict.size());
			if (i == 0 || !is_set_contain_letters(ss, iter->first))
				ss.insert(iter->first);
		}
	}
	return ss;
}