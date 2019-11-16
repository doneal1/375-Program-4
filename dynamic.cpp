#include <stddef.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <chrono>
#include <math.h>

using namespace std;

//cards.first -> profit
//cards.second -> weight
vector<pair<int,int>> cards;

int dynamic(int cap);


int main(int argc, char**argv){

	if(argc != 4){
		cout << "Run as ./submission <input> <output> <3>.\n";
		return 1;
	}

	string in = argv[1], out = argv[2];
	int type = atoi(argv[3]);
	if(type != 3){
		cout << "Run with value 3 only.\n";
		return 1;
	}

	if(!ifstream(in)){
		cout << "The given input file does not exist.\n";
		return 1;
	}
	if(!ofstream(out)){
		cout << "The given output file could not be opened.\n";
		return 1;
	}

	ifstream input(in);
	ofstream output(out);

	int item = 0, cap = 0, maxProfit = 0;
	while(input >> item >> cap){
		for(int i = 0; i < item; i++){
			pair<int,int> add(-1,-1);
			cards.push_back(add);
		}
		for(int j = 0; j < item; j++){
			input >> cards[j].second >> cards[j].first;
		}

		auto start = chrono::high_resolution_clock::now();
		
		maxProfit = dynamic(cap);

		auto stop = chrono::high_resolution_clock::now();

		chrono::duration<double> elapsed = stop - start;
		output << "Dynamic Programming: " << item << " " << maxProfit << " " << elapsed.count() << "\n";
		cards.clear();
	}

	return 0;
}

// *** DYNAMIC PROGRAMMING CODE STARTS HERE *** 

int dynamic(int cap){
	vector<vector<int>> dyn;
	vector<int> z(cap+1), y(cap+1);
	for(int i = 0; i <= cap; i++){
		z[i] = 0;
		y[i] = 0;
	}
	dyn.push_back(z);
	dyn.push_back(y);
	
	for(int i = 0; i < (int)cards.size(); i++){
		dyn.erase(dyn.begin());
		vector<int> add(cap+1);
		for(int i = 0; i <= cap; i++){
			add[i] = 0;
		}
		dyn.push_back(add);

		for(int c = 1; c <= cap; c++){ //nice
			int p = cards[i].first;
			int w = cards[i].second;
			if(w <= c && dyn[0][c-w]+p>dyn[0][c])
				dyn[1][c] = dyn[0][c-w] + p;
			else
				dyn[1][c] = dyn[0][c];

		}
	}

	return dyn[1][cap];
}

