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
    vector<int> input;

    while (getline(fin, item))
    {
        input.push_back(stoi(item));
    }

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
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