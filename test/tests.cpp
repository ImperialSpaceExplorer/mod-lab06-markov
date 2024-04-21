// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"
#include "../src/textgen.cpp"
class GenTest : public testing::Test {
protected:
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
};

TEST(GenTest, MakePref) {
	typedef deque<string> prefix;
	deque<string> arr;
	finput(&arr);
	prefix exp{arr[0],arr[1]}; 
	prefix eq{ "Р’СЃС‚СЂРµС‚РёР»РёСЃСЊ", "РЅР°" };
  EXPECT_EQ(eq[0]+" "+eq[1], exp[0]+" "+exp[1]);
}

TEST(GenTest, MakePair) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	deque<string> arr;
	finput(&arr);
	prefix exp; exp.push_back(arr[0]); exp.push_back(arr[1]);
	statetab[exp].push_back(arr[2]);
	prefix pr{ "Р’СЃС‚СЂРµС‚РёР»РёСЃСЊ","РЅР°" };
	map<prefix, vector<string> >eq = { {pr,vector<string>{ "РґРѕСЂРѕРіРµ"}} };
	EXPECT_EQ(exp[0]+" "+exp[1]+" "+ statetab[exp].at(0), pr[0]+" "+pr[1]+" "+eq[pr].at(0));
}

TEST(GenTest, OneSuffChoose) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	statetab = make_statetab();
	vector<string> eq;
	auto item = statetab.begin();
	while (item!=statetab.end()) {
		if (item->second.size() == 1) { eq = item->second; break; }
		item = statetab.begin();
		std::advance(item, rand() % statetab.size());
	}
	EXPECT_EQ(eq.size() == 1, true);
}

TEST(GenTest, MultSuffChoose) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	statetab = make_statetab();
	vector<string> eq;
	auto item = statetab.begin();
	while (item != statetab.end()) {
		if (item->second.size() != 1) { eq = item->second; break; }
		item = statetab.begin();
		std::advance(item, rand() % statetab.size());
	}
	EXPECT_EQ(eq.size() > 1, true);
}

TEST(GenTest, MakeText) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	int num = 0;
	prefix curr{ "Встретились","на" };
	string eq = curr[0] + " " + curr[1];
	map<prefix, vector<string> >expect = { {prefix{"Встретились","на"},vector<string>{ "дороге"}} ,{prefix{"на","дороге"},vector<string>{ "барин"}},{prefix{"дороге","барин"},vector<string>{ "и"}},{prefix{"барин","и"},vector<string>{ "мужик."}} };
	while (expect.find(curr) != expect.end() && num < 10) {
		eq = eq + " " + expect[curr].at(0);
		prefix tmp;
		tmp.push_back (curr[1]); tmp.push_back(expect[curr].at(0));
		curr = tmp;
		num++;
	}
	string ex = "Встретились на дороге барин и мужик.";
	EXPECT_EQ(eq, ex);
}
