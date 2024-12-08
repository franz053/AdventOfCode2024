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

    for (auto it1 = towers.begin(); it1 != towers.end(); it1++) {
        auto it2 = it1;
        for (++it2; it2 != towers.end() && it2->first == it1->first; it2++) {
            int x1 = it1->second.first;
            int y1 = it1->second.second;
            int x2 = it2->second.first;
            int y2 = it2->second.second;
            while (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
                results.insert(make_pair(x1, y1));
                int tmpX = x1, tmpY = y1;
                x1 = (x1 * 2) - x2;
                y1 = (y1 * 2) - y2;
                x2 = tmpX, y2 = tmpY;
            }
            while (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
                results.insert(make_pair(x2, y2));
                int tmpX = x2, tmpY = y2;
                x2 = (x2 * 2) - x1;
                y2 = (y2 * 2) - y1;
                x1 = tmpX, y1 = tmpY;
            }
        }
    }
    cout << results.size();
    return 0;
}
