// Copyright 2024 Maz

#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <ctime>
#include <iterator>

using u32    = uint_least32_t;
using engine = std::mt19937;
typedef deque<string> prefix;

void finput(deque<std::string>* arr);
void foutput(deque<std::string> arr);

void generate(map<prefix, vector<std::string> > state_tab);

map<prefix, vector<std::string> > make_statetab();
