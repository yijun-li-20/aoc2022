#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <regex>

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
    vector<stack<char>> v{10, stack<char>()};
    v[1] = stack<char>({'B', 'Z', 'T'});
    v[2] = stack<char>({'V', 'H', 'T', 'D', 'N'});
    v[3] = stack<char>({'B', 'F', 'M', 'D'});
    v[4] = stack<char>({'T', 'J', 'G', 'W', 'V', 'Q', 'M'});
    v[5] = stack<char>({'W', 'D', 'G', 'P', 'V', 'F', 'Q', 'M'});
    v[6] = stack<char>({'V', 'Z', 'Q', 'G', 'H', 'F', 'S'});
    v[7] = stack<char>({'Z', 'S', 'N', 'R', 'L', 'T', 'C', 'W'});
    v[8] = stack<char>({'Z', 'H', 'W', 'D', 'J', 'N', 'R', 'M'});
    v[9] = stack<char>({'M', 'Q', 'L', 'F', 'D', 'S'});

//                 [M]     [W] [M]    
//             [L] [Q] [S] [C] [R]    
//             [Q] [F] [F] [T] [N] [S]
//     [N]     [V] [V] [H] [L] [J] [D]
//     [D] [D] [W] [P] [G] [R] [D] [F]
// [T] [T] [M] [G] [G] [Q] [N] [W] [L]
// [Z] [H] [F] [J] [D] [Z] [S] [H] [Q]
// [B] [V] [B] [T] [W] [V] [Z] [Z] [M]
//  1   2   3   4   5   6   7   8   9 

    string item;
    // vector<int> input;
    std::regex pattern("move (\\d+) from (\\d+) to (\\d+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::smatch match;
    string res = "";
    switch (stoi(argv[2]))
    {
    case 0:
    {
        while (getline(fin, item))
        {
            regex_match(item, match, pattern);
            if(match.size() == 4) {
                int count = stoi(match[1].str()), src = stoi(match[2].str()), dst = stoi(match[3].str());
                for (size_t i = 0; i < count; i++)
                {
                    char cur = v[src].top();
                    v[src].pop();
                    v[dst].push(cur);
                }
            }
        }
        for (size_t i = 1; i < 10; i++)
        {
            res += v[i].top();
        }
        break;
    }
    case 1:
    {
        stack<char> temp;
        while (getline(fin, item))
        {
            regex_match(item, match, pattern);
            if(match.size() == 4) {
                int count = stoi(match[1].str()), src = stoi(match[2].str()), dst = stoi(match[3].str());
                for (size_t i = 0; i < count; i++)
                {
                    char cur = v[src].top();
                    v[src].pop();
                    temp.push(cur);
                }
                for (size_t i = 0; i < count; i++)
                {
                    char cur = temp.top();
                    temp.pop();
                    v[dst].push(cur);
                }
            }
        }
        for (size_t i = 1; i < 10; i++)
        {
            res += v[i].top();
        }
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}