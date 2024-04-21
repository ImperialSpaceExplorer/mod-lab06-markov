// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"
class GenTest : public testing::Test {
protected:
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
};

TEST(GenTest, MakePref) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	std::ifstream input("data.txt");
	string word;
	prefix Prefix;
	for (int i = 0; i < 2; i++) {
		input >> word;
		Prefix.push_back(word);
	}
	prefix eq{ "Р’СЃС‚СЂРµС‚РёР»РёСЃСЊ", "РЅР°" };
	bool isit;
	if (eq[0] == Prefix[0] && eq[1] == Prefix[1])isit = true;
	else isit = false;
  EXPECT_EQ(isit, true);
}

TEST(GenTest, MakePair) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	std::ifstream input("data.txt");
	string word;
	prefix Prefix;
	for (int i = 0; i < 2; i++) {
		input >> word;
		Prefix.push_back(word);
	}
	input >> word;
	statetab[Prefix].push_back(word);
	map<prefix, vector<string> >expect = { {prefix{"Р’СЃС‚СЂРµС‚РёР»РёСЃСЊ","РЅР°"},vector<string>{ "РґРѕСЂРѕРіРµ"}} };
	EXPECT_EQ(expect[Prefix].at(0), statetab[Prefix].at(0));
}

TEST(GenTest, OneSuffChoose) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	std::ifstream input("data.txt");
	string word;
	prefix Prefix, cur;
	for (int i = 0; i < 2 + 1; i++) {
		input >> word;
		if (i != 2) { Prefix.push_back(word); cur.push_back(word); }
		else { statetab[Prefix].push_back(word); }
	}
	Prefix.pop_front();
	Prefix.push_back(word);

	while (input >> word) {
		statetab[Prefix].push_back(word);
		Prefix.pop_front();
		Prefix.push_back(word);
	}

	input.close();
	vector<string> eq;
	auto item = statetab.begin();
	while (true) {
		if (item->second.size() == 1) { eq = item->second; break; }
		item = statetab.begin();
		std::advance(item, rand() % statetab.size());
	}
	EXPECT_EQ(eq.size() == 1, true);
}

TEST(GenTest, MultSuffChoose) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	std::ifstream input("data.txt");
	string word;
	prefix Prefix, cur;
	for (int i = 0; i < 2 + 1; i++) {
		input >> word;
		if (i != 2) { Prefix.push_back(word); cur.push_back(word); }
		else { statetab[Prefix].push_back(word); }
	}
	Prefix.pop_front();
	Prefix.push_back(word);

	while (input >> word) {
		statetab[Prefix].push_back(word);
		Prefix.pop_front();
		Prefix.push_back(word);
	}

	input.close();
	vector<string> eq;
	auto item = statetab.begin();
	while (true) {
		if (item->second.size() != 1) { eq = item->second; break; }
		item = statetab.begin();
		std::advance(item, rand() % statetab.size());
	}
	EXPECT_EQ(eq.size() != 1, true);
}

TEST(GenTest, MakeText) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	int num = 0;
	prefix cur{ "Встретились","на" };
	string eq = cur[0] + " " + cur[1];
	map<prefix, vector<string> >expect = { {prefix{"Встретились","на"},vector<string>{ "дороге"}} ,{prefix{"на","дороге"},vector<string>{ "барин"}},{prefix{"дороге","барин"},vector<string>{ "и"}},{prefix{"барин","и"},vector<string>{ "мужик."}} };
	while (expect.find(cur) != expect.end() && num < 10) {
		eq = eq + " " + expect[cur].at(0);
		cur[0] = cur[1]; cur[1] = expect[cur].at(0);
		num++;
	}
	string ex = "Встретились на дороге барин и мужик.";
	EXPECT_EQ(eq, ex);
}
