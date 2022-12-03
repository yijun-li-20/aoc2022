#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>
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
        int ls = 0;
        while (getline(fin, item))
        {
            ls = item.length()/2;
            set<char> front(item.begin(), item.begin()+ls);
            for(int i=0;i<ls;i++){
                if(front.find(item[ls+i])!=front.end()){
                    res += item[ls+i] >= 'a'? item[ls+i] - 'a' + 1 : item[ls+i] - 'A' + 27;
                    break;
                }
            } 
        }
        break;
    }
    case 1:
    {
        string item, item2, item3;
        while (getline(fin, item))
        {
            set<char> s1(item.begin(), item.end());
            getline(fin, item2);
            set<char> s2(item2.begin(), item2.end());
            getline(fin, item3);
            vector<char> v(s1.size());
            std::vector<char>::iterator it = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), v.begin());
            v.resize(it-v.begin()); 
            set<char> intsec(v.begin(), v.end());
            for(int i=0;i<item3.length();i++){
                if(intsec.find(item3[i])!=intsec.end()){
                    res += item3[i] >= 'a'? item3[i] - 'a' + 1 : item3[i] - 'A' + 27;
                    break;
                }
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