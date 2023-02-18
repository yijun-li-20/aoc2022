#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <regex>
#include <map>
#include <set>

using namespace std;


class Dir {
public:
    string name;
    int size = 0;
    bool file = false;
    vector<std::shared_ptr<Dir>> files = {};
    Dir* parent = nullptr;

    Dir(string _name): name(_name), file(true)  {}
    Dir(string _name, Dir* _parent): name(_name), parent(_parent), file(false)  {}

    void addFile(string f, int s) {
        auto temp = std::make_shared<Dir>(f);
        temp->size = s;
        files.emplace_back(temp);
    }

    void addDir(string f) {
        auto temp = std::make_shared<Dir>(f, this);
        files.emplace_back(temp);
    }

    int getSize() {
        if (!file) {
            computeSize();
        } 
        return size;
    }

    void computeSize()  {
        for (auto& f:files)
        {
            size += f->getSize();
        }
    }
};

int type(string c) {
    if (c[0] == '$' && c[2] == 'c') { return 0; }
    if (c[0] == '$' && c[2] == 'l') { return 1; }
    if (c[0] == 'd') { return 2; }
    if (c[0] <= '9' && c[0] >= '1') { return 3; }
    return -1;
}

void recurs(int64_t& count, Dir* node) {
    if(node->size == 0) {
        node->computeSize();
    }
    if(node->size <= 100000) {
        count += node->size;
    }
    for(auto& n: node->files) {
        if (!n->file) recurs(count, n.get());
    }
}

void findMin(int64_t bar, int64_t& count, Dir* node) {
    if(node->size >= bar && node->size < count) {
        count = node->size;
    }
    for(auto& n: node->files) {
        if (!n->file) findMin(bar, count, n.get());
    }
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
    string item, next;
    auto root = std::make_shared<Dir>("/", nullptr);
    Dir* curr; // = root.get();
    int fsize, de;
    while (getline(fin, item))
    {
        switch(type(item)) 
        {
        case 0:
            next = item.substr(5, item.length()-5);
            if (next == "..")
            {
                curr = curr->parent;
            }
            else if (next == "/") {
                curr = root.get();
            }
            else { // go to a child directory
                bool flag = false;
                for (auto& chd: curr->files)
                {
                    if(chd->name == next && !chd->file) { curr = chd.get(); flag = true;}
                }
                if (!flag) std::cerr << curr->name << ": bad dir\n";
            }
            break;
        case 1: // ls
            break;
        case 2: // dir ..
            next = item.substr(4, item.length()-4);
            curr->addDir(next);
            break;
        case 3: // file info
            de = item.find(' ');
            fsize = std::stoi(item.substr(0, de));
            next = item.substr(de+1, item.length()-de-1);
            curr->addFile(next, fsize);
            break;
        }
    }
    
    int64_t result = 0;
    int64_t& res = result;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        curr = root.get();
        recurs(res, curr);
        break;
    }
    case 1:
    {
        curr = root.get();
        recurs(res, curr);
        int64_t bar = root->size - 40000000;
        res = 30000000; // init as worst
        findMin(bar, res, curr);
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}