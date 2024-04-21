// Copyright 2024 Maz
#include <gtest/gtest.h>
#include "../include/textgen.h"
class GenTest : public testing::Test{
 protected:
typedef std::deque<std::string> prefix;
std::map<prefix, std::vector<std::string> > statetab;
};

TEST(GenTest, MakePref) {
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
exp.push_back(token);
token = std::strtok(nullptr, delimeter);
}
word = new char[100];
}
prefix eq{ "Встретились", "на" };
char* exp_s = const_cast<char*>(exp[0].c_str()) + std::string(" ") +
const_cast<char*>(exp[1].c_str()),
eq_s = const_cast<char*>(eq[0].c_str()) +
std::string(" ") + const_cast<char*>(eq[1].c_str());
EXPECT_EQ(std::string(eq_s), std::string(exp_s));
}

TEST(GenTest, MakePair) {
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
if(num < 2)exp.push_back(token);
else
statetab[exp].push_back(token);
token = std::strtok(nullptr, delimeter);
num++;
}
word = new char[100];
}
prefix pr{ "Встретились" , "на" };
std::map<prefix , std::vector<std::string> >eq = {
{pr, std::vector<std::string>{ "дороге"}} };
char* exp_s = const_cast<char*>(exp[0].c_str()) + std::string(" ") +
const_cast<char*>(exp[1].c_str()) + std::string(" ") +
const_cast<char*>(statetab[exp].at(0).c_str()),
pr_s = const_cast<char*>(pr[0].c_str()) + std::string(" ") +
const_cast<char*>(pr[1].c_str()) + std::string(" ") +
const_cast<char*>(eq[pr].at(0).c_str());
EXPECT_EQ(std::string(exp_s), std::string(pr_s));
}

TEST(GenTest, OneSuffChoose) {
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

TEST(GenTest, MultSuffChoose) {
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

TEST(GenTest, MakeText) {
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
char* eq = const_cast<char*>(all[0].c_str()) + std::string(" ") +
const_cast<char*>(all[1].c_str()) + std::string(" ") +
const_cast<char*>(all[2].c_str()) + std::string(" ")
+ const_cast<char*>(all[3].c_str()) + std::string(" ") +
const_cast<char*>(all[4].c_str()) + std::string(" ") +
const_cast<char*>(all[5].c_str());
const char ex[] = "Встретились на дороге барин и мужик.";
EXPECT_EQ(std::string(eq), std::string(ex));
}
