#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day8\\input.txt"


using namespace std;

int main() {
    unordered_multimap<char, pair<int, int>> towers;
    set<pair<int, int>> results;
    ifstream InFile(INPUT_PATH);
    string currentLine;
    int height, width;
    for (height = 0; getline(InFile, currentLine); ++height) {
        for (width = 0; width < currentLine.size(); ++width) {
            if (currentLine[width] != '.') {
                towers.insert(make_pair(currentLine[width], make_pair(width, height)));
            }
        }
    }

    int pos = 0;
    for (auto it1 = towers.begin(); it1 != towers.end(); it1++) {
        auto it2 = it1;
        for (++it2; it2 != towers.end() && it2->first == it1->first; it2++) {
            int x = (2 * it1->second.first) - it2->second.first;
            int y = (2 * it1->second.second) - it2->second.second;
            if (x >= 0 && x < width && y >= 0 && y < height) {
                results.insert(make_pair(x, y));
            }
            x = (2 * it2->second.first) - it1->second.first;
            y = (2 * it2->second.second) - it1->second.second;
            if (x >= 0 && x < width && y >= 0 && y < height) {
                results.insert(make_pair(x, y));
            }
        }
    }

    cout << results.size();
    return 0;
}
