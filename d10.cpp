#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

void draw(int ts, int x) {
	// x-1, x and x+1
	if((ts-1)%40 >= x-1 && (ts-1)%40 <= x+1){
		printf("#");
	}
	else {
		printf(".");
	}
}

int main(int argc, char *argv[])
{
	string filename = argv[1];
	ifstream fin;
	fin.open(filename.c_str());
	if (!fin)
	{
		cout << "Error opening " << filename << endl;
		exit(1);
	}

	string item;
	vector<int> input;

	while (getline(fin, item))
	{
		if (item == "noop") { input.push_back(0); }
		else { input.push_back(std::stoi(item.substr(5, item.length() - 5))); }
	}

	int res = 0, ts = 1, x = 1;
	set<int> target = {20, 60, 100, 140, 180, 220};
	switch (stoi(argv[2])) {
	case 0:
	{
		for(auto& opr: input) {
			if(opr == 0) { ts ++; }
			else {
				if(target.find(ts+1) != target.end()) { res += x*(ts+1); }
				ts += 2;
				x += opr;
			}
			if(target.find(ts) != target.end()) { res += x*ts; }
		}
		break;
	}
	case 1:
	{
		draw(ts, x);
		for(auto& opr: input) {
			if(opr == 0) {
				ts ++; 
				draw(ts, x);
			}
			else {
				ts ++;
				draw(ts, x);
				if(ts % 40 == 0) { printf("\n"); }
				ts ++;
				x += opr;
				draw(ts, x);
			}
			if(ts % 40 == 0) { printf("\n");}
		}
		break;
	}
	default:
		break;
	}

	std::cout << res << std::endl;
	return 0;
}