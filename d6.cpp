#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

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
    getline(fin, item);
    vector<int> count(26, 0);

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        int l=0, r=4;
        for (size_t i = 0; i < item.length(); i++)
        {
            if (i>=4)
            {
                count[item[i-4]-'a'] --;
            }
            count[item[i]-'a'] ++;
            if (count[item[i]-'a'] == 1 && count[item[i-1]-'a'] == 1 && count[item[i-2]-'a'] == 1 && count[item[i-3]-'a'] == 1) {
                res = i+1;
                break;
            }
        }
         
        break;
    }
    case 1:
    {
        int l = 0, r = 1;
        // sliding window, find first window==14
        count[item[l]-'a'] ++;
        
        while (r-l < 14)
        {
            count[item[r]-'a'] ++;
            while (count[item[r]-'a'] > 1)
            {
                count[item[l]-'a'] --;
                l ++;
            }
            r ++;
        }
        res = r;
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}