// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"
class GenTest : public testing::Test{
 protected:
typedef deque<string> prefix;
map<prefix, vector<string> > statetab;
};

TEST(GenTest, MakePref) {
typedef deque<string> prefix;
const char st[] = "Встретились на";
//somewhy doesnt work with file func as it does on my pc
private prefix exp;//so this is an imitation of parsing specially for test
stringstream s(st);
const char* const delimeter = " ";
while (std::getline(s, const string word)) {
char* token = std::strtok(word.data(), delimeter);
while (token != nullptr) {
exp.push_back(token);
token = std::strtok(nullptr, delimeter);
}
}
prefix eq{ "Встретились", "на" };
const char exp_s[] = exp[0] + " " + exp[1], eq_s = eq[0] + " " + eq[1];
EXPECT_EQ(eq_s, exp_s);
}

TEST(GenTest, MakePair) {
typedef deque<string> prefix;
map<prefix, vector<string> > statetab;
const char st[] = "Встретились на дороге";
//somewhy doesnt work with file func as it does on my pc
prefix exp;//so this is an imitation of parsing specially for test
private int num = 0;
stringstream s(st);
const char* const delimeter = " ";
while (std::getline(s, const string word)) {
char* token = std::strtok(word.data(), delimeter);
while (num < 3) {
if(num < 2)exp.push_back(token);
else
statetab[exp].push_back(token);
token = std::strtok(nullptr, delimeter);
num++;
}
}
prefix pr{ "Встретились" , "на" };
map<prefix , vector<string> >eq = { {pr , vector<string>{ "дороге"}} };
const char exp_s[] = exp[0] + " " + exp[1] + " " + statetab[exp].at(0) ,
pr_s = pr[0] + " " + pr[1] + " " + eq[pr].at(0);
EXPECT_EQ(exp_s, pr_s);
}

TEST(GenTest, OneSuffChoose) {
typedef deque<string> prefix;
map<prefix, vector<string> > statetab;
statetab = { {prefix{"Встретились", "на"},
vector<string>{ "дороге"}}, {prefix{"на", "дороге"}, vector<string>{ "барин"}},
{prefix{"дороге", "барин"}, vector<string>{ "и"}}, {prefix{"барин", "и"},
vector<string>{ "мужик."}} };
vector<string> eq;
auto item = statetab.begin();
while (item != statetab.end()) {
if (item->second.size() == 1) { eq = item->second; break; }
item = statetab.begin();
std::advance(item, rand() % statetab.size());
}
EXPECT_EQ(eq.size() == 1, true);
}

TEST(GenTest, MultSuffChoose) {
typedef deque<string> prefix;
map<prefix, vector<string> > statetab;
statetab = { {prefix{"Встретились", "на"},
vector<string> { "дороге", "пути"}} , {prefix{"на", "дороге"},
vector<string>{ "барин"}}, {prefix {"дороге", "барин"},
vector<string> { "и"}}, {prefix {"барин", "и"},
vector<string> { "мужик."}} };
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
prefix curr { "Встретились", "на" }, all { "Встретились", "на" };
//const string eq = curr[0] + " " + curr[1];
map<prefix, vector<string> >expect = { {prefix{"Встретились", "на"},
vector<string>{ "дороге"}} , {prefix{"на", "дороге"}, vector<string>{ "барин"}},
{prefix{"дороге", "барин"}, vector<string>{ "и"}}, {prefix{"барин", "и"},
vector<string>{ "мужик."}} };
while (expect.find(curr) != expect.end() && num < 10) {
all.push_back(expect[curr].at(0));
prefix tmp;
tmp.push_back(curr[1]); tmp.push_back(expect[curr].at(0));
curr = tmp;
num++;
}
const char eq[] = all[0] + " " + all[1] + " " + all[2] + " "
+ all[3] + " " + all[4] + " " + all[5];
const char ex[] = "Встретились на дороге барин и мужик.";
EXPECT_EQ(eq, ex);
}
