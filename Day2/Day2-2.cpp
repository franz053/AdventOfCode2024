#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define INPUT_PATH "..\\Day2\\input.txt"

int main() {
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    bool ascending;
    int level, result = 0;
    while (std::getline(InFile, currentLine)) {
        std::vector<int> levels;
        std::stringstream currentLineStream(currentLine);
        while (currentLineStream >> level) levels.push_back(level); //vector holding report
        for (int i = 0; i <= levels.size(); ++i) {
            bool safe = true;
            std::vector<int> levelsTemp = levels;
            if (i != levels.size())levelsTemp.erase(levelsTemp.begin() + i);
            ascending = (levelsTemp.at(1) > levelsTemp.at(0));
            for (int j = 0; j < levelsTemp.size()-1 && safe; ++j) {
                int diff = levelsTemp.at(j + 1) - levelsTemp.at(j);
                if (ascending) {
                    //ascending
                    if (diff > 3 || diff <= 0) {
                        safe = false;
                    }
                } else {
                    //descending
                    if (diff < -3 || diff >= 0) {
                        safe = false;
                    }
                }
            }
            if (safe) {
                result++;
                break;
            }
        }
    }
    std::cout << result;
}