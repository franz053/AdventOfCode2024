#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define INPUT_PATH "..\\Day11\\input.txt"

typedef unsigned long long ull;

using namespace std;

inline int length(ull number) {
    int res = 1;
    while (number /= 10) res++;
    return res;
}


int main() {
    vector<pair<ull, ull>> stones;
    {
        ifstream InFile(INPUT_PATH);
        string currentLine;
        getline(InFile, currentLine);
        InFile.close();
        stringstream ss(currentLine);
        ull next;
        while (ss >> next) stones.emplace_back(next, 1);
    }

    for (int blink = 0; blink < 75; ++blink) {
        for (int pos = 0; pos < stones.size(); pos++) {
            int len = length(stones[pos].first);
            if (stones[pos].first == 0) {
                //0
                stones[pos].first++;
            } else if (len % 2) {
                //odd length
                stones[pos].first *= 2024;
            } else {
                //even length
                int splitter = 10;
                for (int i = 1; i < len / 2; ++i) splitter *= 10;
                stones.insert(stones.begin() + pos + 1, make_pair(stones[pos].first % splitter, stones[pos].second));
                stones[pos].first /= splitter;
                pos++;
            }
        }
        sort(stones.begin(), stones.end());
        for (int i = 0; i < stones.size() - 1; ++i) {
            if (stones[i].first == stones[i + 1].first) {
                stones[i + 1].second += stones[i].second;
                stones.erase(stones.begin() + i);
                i--;
            }
        }
    }

    ull result = 0;
    for (auto stone: stones) {
        result += stone.second;
    }

    cout << result;
    return 0;
}