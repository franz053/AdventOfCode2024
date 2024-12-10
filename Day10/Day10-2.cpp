#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day10\\input.txt"


using namespace std;

int search(vector<int> &topographicMap, int width, int pos) {
    if (topographicMap[pos] == 9) return 1;
    int ret = 0;

    //up
    if (pos - width >= 0 && topographicMap[pos - width] == topographicMap[pos] + 1) {
        ret += search(topographicMap, width, pos - width);
    }
    //left
    if (pos % width != 0 && pos - 1 >= 0 && topographicMap[pos - 1] == topographicMap[pos] + 1) {
        ret += search(topographicMap, width, pos - 1);
    }
    //right
    if (pos % width != width - 1 && pos + 1 < topographicMap.size() &&
        topographicMap[pos + 1] == topographicMap[pos] + 1) {
        ret += search(topographicMap, width, pos + 1);
    }
    //down
    if (pos + width < topographicMap.size() && topographicMap[pos + width] == topographicMap[pos] + 1) {
        ret += search(topographicMap, width, pos + width);
    }

    return ret;
}

int main() {
    int result = 0;
    vector<int> topographicMap;
    ifstream InFile(INPUT_PATH);
    string inString;
    while (getline(InFile, inString)) {
        for (int j = 0; j < inString.length(); ++j) topographicMap.push_back(inString[j] - '0');
    }
    InFile.close();

    for (int pos = 0; pos < topographicMap.size(); ++pos) {
        if (topographicMap[pos] == 0) result += search(topographicMap, inString.length(), pos);
    }

    cout << result;
    return 0;
}