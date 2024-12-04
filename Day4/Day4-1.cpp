#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day4\\input.txt"

int search(int row, int column, std::vector<std::string> &map, std::string &searchString, int right = 0, int down = 0) {
    int wordPos = 0;
    while (searchString[wordPos + 1]) {
        row += down;
        column += right;
        wordPos++;
        if (row < 0 || row >= map.size() || column < 0 ||
            column >= map[0].length() ||
            map[row][column] != searchString[wordPos])
            return 0;
    }
    return 1;
}

int main() {
    int result = 0;
    std::string searchString = "XMAS";
    std::vector<std::string> map;
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    for (int i = 0; std::getline(InFile, currentLine); ++i) map.push_back(currentLine);
    InFile.close();
    int rows = map.size();
    for (int row = 0; row < rows; ++row) {
        int column = map[row].find('X');

        while (column != -1) {
            for (int right = -1; right <= 1; ++right) {
                for (int down = -1; down <= 1; ++down) {
                    if (!(right | down)) continue;
                    result += search(row, column, map, searchString, right, down);
                }
            }
            column = map[row].find('X', column + 1);
        }
    }
    std::cout << result;

    return 0;
}
