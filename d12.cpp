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
     return v.first*200+v.second;
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
        deque<pair<Coord, int>> q({{start, 0}}), next({});
        int level = (int)'a' - 1;
        bool flag = false;

        while (!q.empty() && !flag)
        {  
            int qsize = q.size();
            for (size_t cand = 0; cand < qsize; cand++)
            {
                auto temp = q.front();
                q.pop_front();
                Coord cur = temp.first;
                if(visited.count(cur) != 0) {
                    continue;
                }
                visited.insert(cur);
                int step = temp.second;
                if(step) {
                    level = (int)input[cur.first][cur.second];
                }
                for (auto& ij: directions)
                {
                    int i = ij.first, j = ij.second;
                    if(valid(r, c, cur.first+i, cur.second+j)){
                        if(end.first == cur.first+i && end.second == cur.second+j &&
                            level == (int)'z') {
                            res = step + 1;
                            flag = true;
                            break;
                        }
                        // search for 'a': ((21, 0), 1)
                        pair<Coord, int> search = {{cur.first+i, cur.second+j}, step+1};
                        if(visited.count({cur.first+i, cur.second+j}) == 0 && 
                            (int)input[cur.first+i][cur.second+j] - level <= 1 && 
                            std::find(next.begin(), next.end(), search)==next.end()) 
                        {
                            next.push_back({{cur.first+i, cur.second+j}, step+1});
                        }
                    }
                }
                // std::cout << "q: \t";
                // printq(q, input);
            }
            std::cout << "next: \n";
            printq(next, input);
            q = next;
            next.clear();    
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