#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day15\\input.txt"

struct robot {
    unsigned int xPos, yPos;
};

int main() {
    std::string instructions;
    std::vector<std::string> warehouse;
    robot robot{}; {
        //Read in the task
        std::ifstream InFile(INPUT_PATH);
        std::string currentLine;
        getline(InFile, currentLine);
        int line = 0;
        while (!currentLine.empty()) {
            if (currentLine.find('@') != std::string::npos) {
                robot.yPos = currentLine.find('@');
                robot.xPos = line;
                currentLine.at(currentLine.find('@')) = '.'; //delete robot marker from map
            }
            warehouse.push_back(currentLine);
            getline(InFile, currentLine);
            line++;
        }
        while (getline(InFile, currentLine)) instructions += currentLine;
        InFile.close();
    }

    for (const char instr: instructions) {
        int probe = 1;
        switch (instr) {
            case '^':
                while (warehouse[robot.xPos - probe][robot.yPos] == 'O') probe++;
                if (warehouse[robot.xPos - probe][robot.yPos] != '#') {
                    for (; probe > 1; probe--) warehouse[robot.xPos - probe][robot.yPos] = 'O';
                    warehouse[robot.xPos - probe][robot.yPos] = '.';
                    robot.xPos--;
                }
                break;

            case 'v':
                while (warehouse[robot.xPos + probe][robot.yPos] == 'O') probe++;
                if (warehouse[robot.xPos + probe][robot.yPos] != '#') {
                    for (; probe > 1; probe--) warehouse[robot.xPos + probe][robot.yPos] = 'O';
                    warehouse[robot.xPos + probe][robot.yPos] = '.';
                    robot.xPos++;
                }
                break;

            case '<':
                while (warehouse[robot.xPos][robot.yPos - probe] == 'O') probe++;
                if (warehouse[robot.xPos][robot.yPos - probe] != '#') {
                    for (; probe > 1; probe--) warehouse[robot.xPos][robot.yPos - probe] = 'O';
                    warehouse[robot.xPos][robot.yPos - probe] = '.';
                    robot.yPos--;
                }
                break;

            case '>':
                while (warehouse[robot.xPos][robot.yPos + probe] == 'O') probe++;
                if (warehouse[robot.xPos][robot.yPos + probe] != '#') {
                    for (; probe > 1; probe--) warehouse[robot.xPos][robot.yPos + probe] = 'O';
                    warehouse[robot.xPos][robot.yPos + probe] = '.';
                    robot.yPos++;
                }
                break;

            default:
                throw std::invalid_argument("Invalid Instruction");
        }
    }

    unsigned long result = 0;
    for (int i = 0; i < warehouse.size(); i++) {
        for (int j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == 'O') result += (100*i)+j;
        }
    }

    std::cout << result << std::endl;
    return 0;
}
