#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
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

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        string item;
        // vector<int> input;
        int temp = 0;
        while (getline(fin, item))
        {
            if(item.length()) {
                temp += stoi(item);
            }
            else{
                // input.push_back(temp);
                if(temp > res) {
                    res = temp;
                }
                temp = 0;
            }
        }
        break;
    }
    case 1:
    {
        string item;
        // vector<int> input;
        priority_queue<int> cand;
        int temp = 0;
        while (getline(fin, item))
        {
            if(item.length()) {
                temp += stoi(item);
            }
            else{
                // input.push_back(temp);
                cand.push(-temp);
                res += temp;
                if (cand.size() == 4) {
                    res += cand.top();
                    cand.pop();
                }
                temp = 0;
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