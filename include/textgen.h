// Copyright 2024 Me

#pragma once
#include <iostream>
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

void generate();

void make_statetab();