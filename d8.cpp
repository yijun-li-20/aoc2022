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

    string item;
    vector<string> input;

    while (getline(fin, item))
    {
        input.push_back(item);
    }

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        set<pair<int, int> > visible;
        int r = input.size(), c = input[0].length();
        for (size_t i = 0; i < r; i++)
        {
            visible.insert(make_pair(i, 0));   
            visible.insert(make_pair(i, c-1));
            int thres = input[i][0];
            for (size_t j = 1; j < c-1; j++)
            {
                if(input[i][j] > thres) {
                    thres = input[i][j];
                    visible.insert(make_pair(i,j));
                }
            }
            thres = input[i][c-1];
            for (size_t j = c-2; j > 0; j--)
            {
                if(input[i][j] > thres) {
                    thres = input[i][j];
                    visible.insert(make_pair(i,j));
                }   
            }
        }
        for (size_t i = 0; i < c; i++)
        {
            visible.insert(make_pair(0, i));   
            visible.insert(make_pair(r-1, i));
            int thres = input[0][i];
            for (size_t j = 1; j < r-1; j++)
            {
                if(input[j][i] > thres) {
                    thres = input[j][i];
                    visible.insert(make_pair(j,i));
                }
            }
            thres = input[r-1][i];
            for (size_t j = r-2; j > 0; j--)
            {
                if(input[j][i] > thres) {
                    thres = input[j][i];
                    visible.insert(make_pair(j,i));
                }
            }
        }    
        res = visible.size();
        break;
    }
    case 1:
    {
        int r = input.size(), c = input[0].length();
        vector<vector<int> > dist;
        for (size_t i = 0; i < r; i++)
        {
            dist.push_back(vector<int>(c, 1));
            dist[i][0] = 0;
            dist[i][c-1] = 0;
        }
        for (size_t j = 0; j < c; j++)
        {
            dist[0][j] = 0;
            dist[r-1][j] = 0;
        }
        for (size_t i = 0; i < r; i++)
        {
            stack<pair<int, int> > st;
            for (size_t j = 0; j < c; j++)
            {
                if (st.empty() || st.top().first > input[i][j]-'0')
                {
                    st.push(make_pair(input[i][j]-'0', j));
                }
                else {
                    while(!st.empty() && st.top().first <= input[i][j]-'0') {
                        int idx = st.top().second;
                        st.pop();
                        dist[i][idx] *= (j-idx);
                    }
                    st.push(make_pair(input[i][j]-'0', j));
                }
            }
            if(!st.empty()) {
                int idx = st.top().second;
                st.pop();
                while (!st.empty())
                {
                    dist[i][st.top().second] *= (idx-st.top().second);
                    st.pop();
                }
            }
            
            for (size_t j = c-1; j != -1; j--)
            {
                if (st.empty() || st.top().first > input[i][j]-'0')
                {
                    st.push(make_pair(input[i][j]-'0', j));
                }
                else {
                    while(!st.empty() && st.top().first <= input[i][j]-'0') {
                        int idx = st.top().second;
                        st.pop();
                        dist[i][idx] *= idx-j;
                    }
                    st.push(make_pair(input[i][j]-'0', j));
                }
            }
            if(!st.empty()) {
                int idx = st.top().second;
                st.pop();
                while (!st.empty())
                {
                    dist[i][st.top().second] *= st.top().second-idx;
                    st.pop();
                }
            }
        }
        for (size_t j = 0; j < c; j++)
        {
            stack<pair<int, int> > st;
            for (size_t i = 0; i < r; i++)
            {
                if (st.empty() || st.top().first > input[i][j]-'0')
                {
                    st.push(make_pair(input[i][j]-'0', i));
                }
                else {
                    while(!st.empty() && st.top().first <= input[i][j]-'0') {
                        int idx = st.top().second;
                        st.pop();
                        dist[idx][j] *= (i-idx);
                        res = max(res, dist[idx][j]);
                    }
                    st.push(make_pair(input[i][j]-'0', i));
                }
            }
            if(!st.empty()) {
                int idx = st.top().second;
                st.pop();
                while (!st.empty())
                {
                    dist[st.top().second][j] *= (idx-st.top().second);
                    res = max(res, dist[st.top().second][j]);
                    st.pop();
                }
            }
            
            for (size_t i = r-1; i != -1; i--)
            {
                if (st.empty() || st.top().first > input[i][j]-'0')
                {
                    st.push(make_pair(input[i][j]-'0', i));
                }
                else {
                    while(!st.empty() && st.top().first <= input[i][j]-'0') {
                        int idx = st.top().second;
                        st.pop();
                        dist[idx][j] *= idx-i;
                        res = max(res, dist[idx][j]);
                    }
                    st.push(make_pair(input[i][j]-'0', i));
                }
            }
            if(!st.empty()) {
                int idx = st.top().second;
                st.pop();
                while (!st.empty())
                {
                    dist[st.top().second][j] *= st.top().second-idx;
                    res = max(res, dist[st.top().second][j]);
                    st.pop();
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