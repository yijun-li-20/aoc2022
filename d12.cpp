#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define Coord pair<int, int>

struct func {
   size_t operator()(const Coord &v) const {
     return v.first*199+v.second;
   }
};

bool valid(int r, int c, int r1, int c1) {
    if(r1<0 || c1<0 || r1>=r || c1>=c) { return false; }
    return true;
}

void printq(deque<pair<Coord, int>> q, vector<vector<char>>& input) {
    for (auto& it: q)
    {
        int r = it.first.first, c = it.first.second;
        printf("(%d, %d) %c %d\n", r, c, input[r][c], it.second);
    }
    printf("----\n");
    
}

int main(int argc, char *argv[])
{
    vector<vector<char>> input;
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
        while (getline(fin, item))
        {
            input.push_back({item.begin(), item.end()});
        }
    }
    vector<Coord> directions = {{1, 0}, {-1, 0},  {0, 1}, {0, -1}};
    int r = input.size(), c = input[0].size();

    int res = 0;
    Coord start({20, 0}), end({20, 145});
    unordered_set<Coord, func> visited;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        deque<vector<Coord>> q({{start}});
        int level = 0;
        bool flag = false;
        int qsize, vsize, r_, c_;
        while (!q.empty())
        {  
            qsize = q.size();
            auto curr = q.front();
            vsize = curr.size();
            q.pop_front();
            r_ = curr[vsize-1].first;
            c_ = curr[vsize-1].second;
            if(r_ == end.first && c_ == end.second) {
                res = vsize-1;
                break;
            }
            if(curr.size() > 1) {
                level = input[r_][c_]- 'a';
            }
            if (visited.count({r_, c_}) == 0)
            {
                visited.insert({r_, c_});
                for (auto& ij: directions) {
                    int i = ij.first, j = ij.second;
                    if(valid(r, c, r_+i, c_+j)){
                        int next_level = input[r_+i][c_+j]-'a';
                        if(next_level == 'E'-'a') { next_level = 25; }
                        if(next_level<=level+1) {
                            auto path = vector<Coord>(curr);
                            path.push_back({r_+i, c_+j});
                            q.push_back(path);
                        }
                    } 
                }
            }  
        }
        break;
    }
    case 1:
    {
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}