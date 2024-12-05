#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day5\\input.txt"

using namespace std;

int order(vector<int> update, unordered_multimap<int, int> &predecessors) {
    vector<int> tempVec;
    while (!update.empty()) {
        for (int pageNum = 0; pageNum < update.size(); ++pageNum) {
            bool next = true;
            auto range = predecessors.equal_range(update[pageNum]);
            for (auto it = range.first; it != range.second && next; ++it) {
                if (find(update.begin(), update.end(), it->second) != update.end()) next = false;
            }
            if (next) {
                tempVec.push_back(update.at(pageNum));
                update.erase(update.begin() + pageNum);
            }
        }
    }
    return tempVec[(tempVec.size() >> 1)];
}

int check(vector<int> &update, unordered_multimap<int, int> &predecessors) {
    for (int page = 0; page < update.size() - 1; ++page) {
        for (int following = 1; following < update.size() - page; ++following) {
            auto range = predecessors.equal_range(update[page]);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second == update[following + page]) return order(update, predecessors);
            }
        }
    }
    return 0;
}

int main() {
    int result = 0;

    unordered_multimap<int, int> predecessors;
    vector<vector<int>> updates;
    ifstream InFile(INPUT_PATH);
    string currentLine;
    while (getline(InFile, currentLine)) {
        if (currentLine.empty()) continue; //Skip empty line(s)
        if (currentLine[2] == '|') {
            //Top half of file
            int key = stoi(currentLine.substr(3, 5));
            int value = stoi(currentLine.substr(0, 2));
            predecessors.insert(make_pair(key, value));
        } else {
            //Bottom half of file
            vector<int> tempVec;
            stringstream currentLineStream(currentLine);
            while (getline(currentLineStream, currentLine, ',')) tempVec.push_back(stoi(currentLine));
            updates.push_back(tempVec);
        }
    }
    InFile.close();

    //Data extracted

    for (auto update: updates) {
        result += check(update, predecessors);
    }
    cout << result;
    return 0;
}
