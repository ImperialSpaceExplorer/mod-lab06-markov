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

using namespace std;
using u32    = uint_least32_t;
using engine = std::mt19937;
typedef deque<string> prefix;

void finput(deque<string>* arr);
void foutput(deque<string> arr);

void generate(map<prefix, vector<string> > state_tab);

map<prefix, vector<string> > make_statetab();
