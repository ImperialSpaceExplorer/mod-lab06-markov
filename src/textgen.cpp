#include"textgen.h"

typedef deque<string> prefix;  
map<prefix, vector<string> > statetab;

const int NPREF = 2;
const int MAXGEN = 1000;

prefix cur;


void generate() {
	std::ofstream output("out.txt");
	int num = 0, invec = 0;

	random_device os_seed;
	const u32 seed = os_seed();
	engine generator(seed);

	for (int i = 0; i < NPREF; i++) {
		output << cur[i] << " ";
		}
	while (statetab.find(cur)!=statetab.end()&&num<MAXGEN-2){
		if (num % 10 == 0&&num!=0) output << endl;
		std::uniform_int_distribution< u32 > distribute(0, (int)statetab[cur].size()-1);
		invec = distribute(generator);
		output <<  statetab[cur].at(invec) << " ";
		
		prefix tmp; 
		for (int j = 1; j < NPREF;j++)tmp.push_back(cur[j]);
		tmp.push_back(statetab[cur].at(invec));
		cur = tmp;
		num++;
	}
	output.close();
}

void make_statetab(){
	std::ifstream input("data.txt");
	string word;
	prefix Prefix;
	for (int i = 0; i < NPREF + 1; i++){
		input >> word;
		if (i != NPREF) { Prefix.push_back(word); cur.push_back(word);}
		else { statetab[Prefix].push_back(word); }
	}
	Prefix.pop_front();
	Prefix.push_back(word);

	while (input >> word){
		statetab[Prefix].push_back(word);
		Prefix.pop_front();
		Prefix.push_back(word);
	} 
	
	input.close();
}