#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day11\\input.txt"

typedef unsigned long long ull;

using namespace std;

inline int length(ull number) {
    int res = 1;
    while (number /= 10) res++;
    return res;
}

int main() {
    vector<ull> stones;
    {
        ifstream InFile(INPUT_PATH);
        string currentLine;
        getline(InFile, currentLine);
        InFile.close();
        stringstream ss(currentLine);
        ull next;
        while (ss >> next) stones.push_back(next);
    }

    for (int blink = 0; blink < 25; ++blink) {
        for (int pos = 0; pos < stones.size(); pos++) {
            int len = length(stones[pos]);
            if (stones[pos] == 0) {
                //0
                stones[pos]++;
            } else if (len % 2) {
                //odd length
                stones[pos] *= 2024;
            } else {
                //even length
                int splitter = 10;
                for (int i = 1; i < len / 2; ++i) splitter *= 10;
                stones.insert(stones.begin() + pos + 1, stones[pos] % splitter);
                stones[pos] /= splitter;
                pos++;
            }
        }
    }

    cout << stones.size();
    return 0;
}