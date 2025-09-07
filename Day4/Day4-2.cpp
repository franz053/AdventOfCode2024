#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_PATH "..\\Day4\\input.txt"

inline int search(int row, int column, std::vector<std::string> &map) {
    if ((map[row - 1][column - 1] + map[row + 1][column + 1]) != 160) return 0;//diagonal
    if ((map[row - 1][column + 1] + map[row + 1][column - 1]) != 160) return 0;//diagonal
    return 1;
}

int main() {
    int result = 0;
    std::vector<std::string> map;
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    for (int i = 0; std::getline(InFile, currentLine); ++i) map.push_back(currentLine);
    InFile.close();
    for (int row = 1; row < map.size() - 1; ++row) {
        int column = static_cast<int>(map[row].find('A', 1));
        while (column >= 0 && column < map[0].length() - 1) {
            result += search(row, column, map);
            column = static_cast<int>(map[row].find('A', column + 1));
        }
    }
    std::cout << result;
    return 0;
}
