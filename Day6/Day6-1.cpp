#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_PATH "..\\Day6\\input.txt"

using namespace std;


enum {
    visited,
    unvisited,
    blocked
};

int main() {
    int result = 1;

    vector<vector<char>> lab;
    ifstream InFile(INPUT_PATH);
    int direction = 0b10;
    // 1 0
    // | | 0 x-axis, 1 y-axis
    // | 0 positive, 1 negative
    string currentLine;
    pair<int, int> guard;
    for (int row = 0; getline(InFile, currentLine); ++row) {
        vector<char> tempRow;
        for (int column = 0; column < currentLine.size(); ++column) {
            switch (currentLine[column]) {
                case '#':
                    tempRow.push_back(blocked);
                    break;
                case '^':
                    guard = make_pair(row, column);
                    tempRow.push_back(visited);
                    break;
                default:
                    tempRow.push_back(unvisited);
            }
        }
        lab.push_back(tempRow);
    }
    int height = static_cast<int>(lab.size()) - 1;
    int width = static_cast<int>(lab.at(0).size()) - 1;

    while (guard.first < height && guard.first > 0 && guard.second < width && guard.second > 0) {
        int nextY = guard.first + ((!(direction & 0b01)) * (0b01 - (direction & 0b10))); //Determine movement
        int nextX = guard.second + ((direction & 0b01) * (0b01 - (direction & 0b10))); //Determine movement
        if (lab[nextY][nextX] != blocked) {
            guard.first = nextY;
            guard.second = nextX;
            result += lab[nextY][nextX]; //Add value of field
            lab[nextY][nextX] = visited;
        } else {
            direction = (direction + 3) % 4; //Turn right
        }
    }
    cout << result;
    return 0;
}
