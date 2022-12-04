#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

pair<int, int> parse(string intv) {
    size_t pos = intv.find("-");
    return make_pair(stoi(intv.substr(0, pos)), stoi(intv.substr(pos+1, intv.length()-pos-1)));
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

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        string item;
        vector<int> input;
        size_t pos;
        while (getline(fin, item))
        {
            pos = item.find(",");
            string left = item.substr(0, pos);
            string right = item.substr(pos+1, item.length() -pos-1);
            pair<int, int> p1 = parse(left);
            pair<int, int> p2 = parse(right);
            if (p1.first <= p2.first && p1.second >= p2.second) {
                res ++;
            }
            else if (p2.first <= p1.first && p2.second >= p1.second)
            {
                res ++;
            } 
        }
        break;
    }
    case 1:
    {
        string item;
        vector<int> input;
        size_t pos;
        while (getline(fin, item))
        {
            pos = item.find(",");
            string left = item.substr(0, pos);
            string right = item.substr(pos+1, item.length() -pos-1);
            pair<int, int> p1 = parse(left);
            pair<int, int> p2 = parse(right);
            if (!(p1.second < p2.first || p2.second < p1.first)) {
                res ++;
            }
        }
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}