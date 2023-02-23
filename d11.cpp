#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <memory>
using namespace std;

class Monkey {
public:
    Monkey(vector<uint64_t> _it, int _test) : items(_it), test(_test) { }
    vector<uint64_t> items;
    int test;

    void throwTo(shared_ptr<Monkey> m, int val) {
        m->items.emplace_back(val);
        items.erase(items.begin());
    }
};

uint64_t inspect(int m, int val, int test) {
    uint64_t temp = val;
    switch (m)
    {
    case 0:
        temp *= 2;
        break;
    case 1:
        temp += 3;
        break;
    case 2:
        temp += 6;
        break;
    case 3:
        temp += 5;
        break;
    case 4:
        temp += 8;
        break;
    case 5:
        temp *= 5;
        break;
    case 6:
        temp *= val;
        break;
    case 7:
        temp += 4;
        break;
    default:
        break;
    }

    temp /= 3;
    if(temp%test == 0) { return temp | (1<<31); }
    return temp;
}

uint64_t inspect2(int m, uint64_t val) {
    uint64_t temp = val;
    switch (m)
    {
    case 0:
        temp *= 2;
        break;
    case 1:
        temp += 3;
        break;
    case 2:
        temp += 6;
        break;
    case 3:
        temp += 5;
        break;
    case 4:
        temp += 8;
        break;
    case 5:
        temp *= 5;
        break;
    case 6:
        temp *= val;
        break;
    case 7:
        temp += 4;
        break;
    default:
        break;
    }
    temp %= (2*3*5*7*11*13*17*19);
    return temp;
}

int main(int argc, char *argv[])
{
    vector<int> success = {2, 7, 6, 7, 0, 6, 3, 4};
    vector<int> fail =    {5, 4, 5, 1, 2, 3, 1, 0};
    vector<uint64_t> inspection(8, 0);
    uint64_t res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        vector<shared_ptr<Monkey>> folks;
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{96, 60, 68, 91, 83, 57, 85}, 17));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{75, 78, 68, 81, 73, 99}, 13));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{69, 86, 67, 55, 96, 69, 94, 85}, 19));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{88, 75, 74, 98, 80}, 7));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{82}, 11));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{72, 92, 92}, 3));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{74, 61}, 2));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{76, 86, 83, 55}, 5));
        for (size_t round = 0; round < 20; round++)
        {
            for (size_t m = 0; m < 8; m++)
            {
                int size = folks[m]->items.size();
                for (size_t i = 0; i < size; i++)
                {
                    uint64_t flag = inspect(m, folks[m]->items[0], folks[m]->test);
                    // idk how to formulate different operation in one class
                    if(flag >> 31 & 1) {
                        folks[m]->throwTo(folks[success[m]], flag ^ (1<<31));
                    }
                    else{
                        folks[m]->throwTo(folks[fail[m]], flag);
                    }
                    inspection[m] ++;   
                }

            }
            
        }
        sort(inspection.begin(), inspection.end(), std::greater<int>());
        res = inspection[0] * inspection[1];
        break;
    }
    case 1:
    {
        vector<shared_ptr<Monkey>> folks;
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{96, 60, 68, 91, 83, 57, 85}, 17));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{75, 78, 68, 81, 73, 99}, 13));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{69, 86, 67, 55, 96, 69, 94, 85}, 19));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{88, 75, 74, 98, 80}, 7));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{82}, 11));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{72, 92, 92}, 3));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{74, 61}, 2));
        folks.push_back(make_shared<Monkey>(vector<uint64_t>{76, 86, 83, 55}, 5));
        for (size_t round = 0; round < 10000; round++)
        {
            for (size_t m = 0; m < 8; m++)
            {
                int size = folks[m]->items.size();
                inspection[m] += size;
                for (size_t i = 0; i < size; i++)
                {
                    uint64_t flag = inspect2(m, folks[m]->items[0]);
                    // idk how to formulate different operation in one class
                    if(flag % folks[m]->test == 0) {
                        folks[m]->throwTo(folks[success[m]], flag);
                    }
                    else{
                        folks[m]->throwTo(folks[fail[m]], flag);
                    }
                }
            }
            
        }
        sort(inspection.begin(), inspection.end(), std::greater<long>());
        res = inspection[0] * inspection[1];
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}