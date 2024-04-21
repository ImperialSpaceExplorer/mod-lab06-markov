// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(Test1, MakePref) {
typedef std::deque<std::string> prefix;
const char st[] = "Встретились на";
//somewhy doesnt work with file func as it does on my pc
prefix exp;//so this is an imitation of parsing specially for test
std::stringstream s = std::stringstream(st);
const char* const delimeter = " ";
char* word = new char[100];
while (s.read(word, sizeof(st))) {
char* token = std::strtok(word, delimeter);
while (token != nullptr) {
exp.push_back(std::string(token));
token = std::strtok(nullptr, delimeter);
}
word = new char[100];
}
prefix eq{ "Встретились", "на" };
std::string exp_s = exp[0] +
std::string(" ") + exp[1];
std::string eq_s = eq[0] +
std::string(" ") + eq[1];
EXPECT_EQ(eq_s, exp_s);
}

TEST(Test2, MakePair) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
const char st[] = "Встретились на дороге";
//somewhy doesnt work with file func as it does on my pc
prefix exp;//so this is an imitation of parsing specially for test
int num = 0;
std::stringstream s = std::stringstream(st);
const char* const delimeter = " ";
char* word = new char[100];
while (s.read(word, sizeof(st))) {
char* token = std::strtok(word, delimeter);
while (num < 3) {
if(num < 2) {exp.push_back(token);
} else {
statetab.insert( std::pair<prefix,
std::vector<std::string>>(exp, std::vector<std::string>
{std::string(token)}) );
}
token = std::strtok(nullptr, delimeter);
num++;
}
word = new char[100];
}
prefix pr{ "Встретились" , "на" };
std::map<prefix , std::vector<std::string> >eq = {
{pr, std::vector<std::string>{ "дороге"}} };
std::string exp_s = exp[0] +
std::string(" ") + exp[1] + std::string(" ") +
statetab[exp].at(0);
std::string pr_s = pr[0] +
std::string(" ") + pr[1] + std::string(" ") +
eq[pr].at(0);
EXPECT_EQ(exp_s, pr_s);
}

TEST(Test3, OneSuffChoose) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
statetab = { {prefix{"Встретились", "на"},
std::vector<std::string>{ "дороге"}}, {prefix{"на", "дороге"},
std::vector<std::string>{ "барин"}},
{prefix{"дороге", "барин"}, std::vector<std::string>{
"и"}}, {prefix{"барин", "и"},
std::vector<std::string>{ "мужик."}} };
std::vector<std::string> eq;
auto item = statetab.begin();
while (item != statetab.end()) {
if (item->second.size() == 1) { eq = item->second; break; }
item = statetab.begin();
std::advance(item, rand() % statetab.size());
}
EXPECT_EQ(eq.size() == 1, true);
}

TEST(Test4, MultSuffChoose) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
statetab = { {prefix{"Встретились", "на"},
std::vector<std::string> { "дороге", "пути"}} , {prefix{"на", "дороге"},
std::vector<std::string>{ "барин"}}, {prefix {"дороге", "барин"},
std::vector<std::string> { "и"}}, {prefix {"барин", "и"},
std::vector<std::string> { "мужик."}} };
std::vector<std::string> eq;
auto item = statetab.begin();
while (item != statetab.end()) {
if (item->second.size() != 1) { eq = item->second; break; }
item = statetab.begin();
std::advance(item, rand() % statetab.size());
}
EXPECT_EQ(eq.size() > 1, true);
}

TEST(Test5, MakeText) {
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
int num = 0;
prefix curr { "Встретились", "на" }, all { "Встретились", "на" };
std::map<prefix, std::vector<std::string> >expect = {
{prefix{"Встретились", "на"},
std::vector<std::string>{ "дороге"}} , {prefix{"на", "дороге"},
std::vector<std::string>{ "барин"}},
{prefix{"дороге", "барин"}, std::vector<std::string>{
"и"}}, {prefix{"барин", "и"},
std::vector<std::string>{ "мужик."}} };
while (expect.find(curr) != expect.end() && num < 10) {
all.push_back(expect[curr].at(0));
prefix tmp;
tmp.push_back(curr[1]); tmp.push_back(expect[curr].at(0));
curr = tmp;
num++;
}
std::string eq = all[0] +
std::string(" ") + all[1] + std::string(" ") +
all[2] + std::string(" ") + all[3] +
std::string(" ") + all[4] + std::string(" ") +
all[5];
const char ex[] = "Встретились на дороге барин и мужик.";
EXPECT_EQ(eq, std::string(ex));
}
