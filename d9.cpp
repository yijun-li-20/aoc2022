#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define Coord pair<int, int>

Coord checkAdj(Coord h, Coord t) {
    if(h.first-t.first <= 1 && h.first-t.first >= -1 
        && h.second-t.second <= 1 && h.second-t.second >= -1){
            return {0, 0};
        }
    if(h.first == t.first){ // in the same col
        if(h.second-t.second == 2) return {0, 1};
        if(h.second-t.second == -2) return {0, -1};
        assert(false);
    }
    if(h.second == t.second){ // in the same row
        if(h.first-t.first == 2) return {1, 0};
        if(h.first-t.first == -2) return {-1, 0};
        assert(false);
    } 
    if(h.first-t.first + h.second-t.second >= 3){ // diff: (2, 1) (1, 2) (2, 2)
        return {1, 1};
    }
    if(h.first-t.first + h.second-t.second <= -3){ // diff: (-2, -1) (-1, -2) (-2, -2)
        return {-1, -1};
    }
    if(h.first-t.first - h.second+t.second >= 3){ // diff: (2, -1) (1, -2) (2, -2)
        return {1, -1};
    }
    if(h.first-t.first - h.second+t.second <= -3){ // diff: (-2, 1) (-1, 2) (-2, 2)
        return {-1, 1};
    }
    assert(false);
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
    set<Coord> visited = {{0, 0}};
    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        Coord head, tail;
        head = {0, 0};
        tail = {0, 0};
        while (getline(fin, item))
        {
            char op = item[0];
            int step = std::stoi(item.substr(2, item.length()-2));
            for(int i=0;i<step;i++) {
                switch (op){
                case 'U':
                    head.second ++;
                    break;
                case 'D':
                    head.second --;
                    break;
                case 'L':
                    head.first --;
                    break;
                case 'R':
                    head.first ++;
                    break;
                default:
                    break;
                }
                Coord move = checkAdj(head, tail);
                tail.first += move.first;
                tail.second += move.second;
                visited.insert(tail);

            }
        }
        res = visited.size();
        break;
    }
    case 1:
    {
        vector<Coord> rope(10, {0,0});
        while (getline(fin, item))
        {
            char op = item[0];
            int step = std::stoi(item.substr(2, item.length()-2));
            for(int j=0;j<step;j++) {
                switch (op){
                case 'U':
                    rope[0].second ++;
                    break;
                case 'D':
                    rope[0].second --;
                    break;
                case 'L':
                    rope[0].first --;
                    break;
                case 'R':
                    rope[0].first ++;
                    break;
                default:
                    break;
                }
                for (size_t i = 0; i < 9; i++)
                {
                    Coord move = checkAdj(rope[i], rope[i+1]);
                    rope[i+1].first += move.first;
                    rope[i+1].second += move.second;
                }
                visited.insert(rope[9]);
            }
        }
        res = visited.size();
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}