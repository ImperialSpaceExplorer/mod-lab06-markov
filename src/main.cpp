// Copyright 2024 Maz
#include <iostream>
#include"textgen.h"

int main() {
map<prefix, vector<std::string> > state_tab;
state_tab = make_statetab();
generate(state_tab);
return 0;
}
