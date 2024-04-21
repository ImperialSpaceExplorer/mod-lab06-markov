// Copyright 2024 Maz
#include "../include/textgen.h"

const int NPREF = 2;
const int MAXGEN = 1000;

prefix cur;

void finput(deque<string>* arr){
	std::ifstream input("data.txt");
	string word;
	deque<string> tmp;
	while (input >> word) {
		tmp.push_back(word);
	}
	*arr = tmp;
}
void foutput(deque<string> arr) {
	std::ofstream output("out.txt");
	for (int i = 0; i < arr.size(); i++){
		output << arr[i] << " ";
		if (i % 10 == 0 && i != 0) output << endl;
	}
	output.close();
}

void generate(map<prefix, vector<string> > state_tab) {
	map<prefix, vector<string> > st= state_tab;
	deque<string> arr;
	int num = 0, invec = 0;

	random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);
	for (int i = 0; i < NPREF; i++) {
		arr.push_back(cur[i]);
		}
	while (st.find(cur)!=st.end()&&num<MAXGEN-2){
		std::uniform_int_distribution< u32 > distribute(0, (int)st[cur].size()-1);
		invec = distribute(generator);
		arr.push_back(st[cur].at(invec));
		
		prefix tmp; 
		for (int j = 1; j < NPREF;j++)tmp.push_back(cur[j]);
		tmp.push_back(st[cur].at(invec));
		cur = tmp;
		num++;
	}
	
	foutput(arr);
}

map<prefix, vector<string> > make_statetab(){
	map<prefix, vector<string> > st;
	deque<string> words;
	finput(&words);
	prefix Prefix;
	for (int i = 0; i < NPREF + 1; i++){
		if (i != NPREF) { Prefix.push_back(words[i]); cur.push_back(words[i]);}
		else { st[Prefix].push_back(words[i]); }
	}
	Prefix.pop_front();
	Prefix.push_back(words[NPREF]);

	for (int i = NPREF+1; i < words.size(); i++){
		st[Prefix].push_back(words[i]);
		Prefix.pop_front();
		Prefix.push_back(words[i]);
	}
	return st;
}
