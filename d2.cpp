#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

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
    vector<pair<char, char> > input;

    while (getline(fin, item))
    {
        input.push_back(make_pair(item[0], item[2]));
    }

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        // map<char, char> draw; 
        // draw['A']='X';
        // draw['B']='Y';
        // draw['C']='Z';
        // map<char, char> win; 
        // win['A']='Y';
        // win['B']='Z';
        // win['C']='X';
        int offset = 0;
        for (auto& item: input)
        {
            offset = item.second - 'X' - (item.first-'A');
            if(offset < 0) offset += 3;
            if(offset == 0){
                res += 3;
            }
            else if (offset == 1)
            {
                res += 6;
            }
            res += item.second - 'X' + 1;
        }
        
        break;
    }
    case 1:
    {
        char resp;
        for (auto& item: input)
        {
            if(item.second == 'Z') {
                // win;
                res += 6;
                resp = item.first == 'C'?'X':item.first - 'A' + 'X' + 1;
            }
            else if (item.second == 'Y'){
                // draw
                res += 3;
                resp = item.first - 'A' + 'X';
            }
            else {
                resp = item.first == 'A'?'Z':item.first - 'A' + 'X' - 1;
            }
            res += resp - 'X' + 1;
        }
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}