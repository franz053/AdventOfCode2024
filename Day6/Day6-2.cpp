#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day6\\input.txt"

using namespace std;

int main() {
    int result = 0;

    vector<vector<char>> labClear;
    ifstream InFile(INPUT_PATH);

    string currentLine;
    pair<int, int> guardStart;
    for (int row = 0; getline(InFile, currentLine); ++row) {
        vector<char> tempRow;
        for (int column = 0; column < currentLine.size(); ++column) {
            switch (currentLine[column]) {
                case '#':
                    tempRow.push_back(-1);
                    break;
                case '^':
                    guardStart = make_pair(row, column);
                default:
                    tempRow.push_back(0);
            }
        }
        labClear.push_back(tempRow);
    }
    int height = static_cast<int>(labClear.size()) - 1;
    int width = static_cast<int>(labClear.at(0).size()) - 1;

    //mark path of possibilities
    pair<int, int> guard = guardStart;
    int direction = 0b10;
    while (guard.first < height && guard.first > 0 && guard.second < width && guard.second > 0) {
        int nextY = guard.first + ((!(direction & 0b01)) * (0b01 - (direction & 0b10))); //Determine movement
        int nextX = guard.second + ((direction & 0b01) * (0b01 - (direction & 0b10))); //Determine movement
        if(labClear[nextY][nextX] > 3){
            //loop, visited same field at least 3 times
            ++result;
            break;
        }else if (labClear[nextY][nextX] == -1) {
            //obstacle
            direction = (direction + 3) % 4;
        } else {
            //no obstacle
            guard.first = nextY;
            guard.second = nextX;
            labClear[nextY][nextX] = 1;
        }
    }

    //check all possibilities
    for (int boxRow = 0; boxRow <= height; ++boxRow) {
        for (int boxColumn = 0; boxColumn <= width; ++boxColumn) {
            if(labClear[boxRow][boxColumn] != 1) continue;
            //RESET
            guard = guardStart;
            vector<vector<char>> lab = labClear;
            direction = 0b10;
            // 1 0
            // | | 0 x-axis, 1 y-axis
            // | 0 positive, 1 negative

            //Place Box
            lab[boxRow][boxColumn] = -1;

            while (guard.first < height && guard.first > 0 && guard.second < width && guard.second > 0) {
                int nextY = guard.first + ((!(direction & 0b01)) * (0b01 - (direction & 0b10))); //Determine movement
                int nextX = guard.second + ((direction & 0b01) * (0b01 - (direction & 0b10))); //Determine movement
                if(lab[nextY][nextX] > 3){
                    //loop, visited same field more than 3 times
                    ++result;
                    break;
                }else if (lab[nextY][nextX] == -1) {
                    //obstacle
                    direction = (direction + 3) % 4;
                } else {
                    //no obstacle
                    guard.first = nextY;
                    guard.second = nextX;
                    lab[nextY][nextX] += 1;
                }
            }

        }
    }
    cout << result;
    return 0;
}
