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
	string st = "Встретились на";	
	string word;//somewhy doesnt work with file func as it does on my pc
	prefix exp;//so this is an imitation of parsing specially for test
	while (st >> word){         
    	prefix.push_back(word);
	}
	prefix eq{ "Встретились", "на" };
	string exp_s = exp[0] + " " + exp[1], eq_s = eq[0] + " " + eq[1];
  EXPECT_EQ(eq_s, exp_s);
}

TEST(GenTest, MakePair) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	string st = "Встретились на дороге";	
	string word;//somewhy doesnt work with file func as it does on my pc
	prefix exp;//so this is an imitation of parsing specially for test
	int num=0;
	while (st >> word){         
    	if(num<2)prefix.push_back(word);
	else statetab[exp].push_back(word);
	num++;
	}
	prefix pr{ "Встретились ","на" };
	map<prefix, vector<string> >eq = { {pr,vector<string>{ "дороге"}} };
	string exp_s = exp[0] + " " + exp[1] + " " + statetab[exp].at(0), pr_s = pr[0] + " " + pr[1] + " " + eq[pr].at(0);
	EXPECT_EQ(exp_s, pr_s);
}

TEST(GenTest, OneSuffChoose) {
	typedef deque<string> prefix;
	map<prefix, vector<string> > statetab;
	statetab = { {prefix{"Встретились","на"},
	vector<string>{ "дороге"}} ,{prefix{"на","дороге"},vector<string>{ "барин"}},
	{prefix{"дороге","барин"},vector<string>{ "и"}},{prefix{"барин","и"},
	vector<string>{ "мужик."}} };
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
	statetab = { {prefix{"Встретились","на"},
	vector<string>{ "дороге", "пути"}} ,{prefix{"на","дороге"},vector<string>{ "барин"}},
	{prefix{"дороге","барин"},vector<string>{ "и"}},{prefix{"барин","и"},
	vector<string>{ "мужик."}} };
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
	map<prefix, vector<string> >expect = { {prefix{"Встретились","на"},
	vector<string>{ "дороге"}} ,{prefix{"на","дороге"},vector<string>{ "барин"}},
	{prefix{"дороге","барин"},vector<string>{ "и"}},{prefix{"барин","и"},
	vector<string>{ "мужик."}} };
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
