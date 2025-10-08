#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day14\\input.txt"

struct space {
    int dimX;
    int dimY;
};

class robot {
    int posX, posY;
    int velX, velY;
    space& hall;

public:
    robot(const int posX, const int posY, const int velX, const int velY, space& hall) :
        posX(posX), posY(posY), velX(velX), velY(velY), hall(hall) {}

    void move(const long steps = 1) {
        posX += (velX*steps)%hall.dimX;
        posY += (velY*steps)%hall.dimY;
        if (posX < 0) posX += hall.dimX;
        if (posY < 0) posY += hall.dimY;
    }
};

int main() {
    std::vector<robot> robots;
    space hall(11,7);

    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    while (getline(InFile, currentLine)) {
        std::string tmpPos(currentLine.substr(currentLine.find("p=")+2, currentLine.find(' ')-2));
        std::string tmpVel(currentLine.substr(currentLine.find("v=")+2, currentLine.back()-2));

        int tmpPosX = std::stoi(tmpPos.substr(0, tmpPos.find(',')));
        int tmpPosY = std::stoi(tmpPos.substr(tmpPos.find(',')+1));
        int tmpVelX = std::stoi(tmpVel.substr(0, tmpVel.find(',')));
        int tmpVelY = std::stoi(tmpVel.substr(tmpVel.find(',')+1));

        robots.emplace_back(tmpPosX, tmpPosY, tmpVelX,tmpVelY, hall);
    }
    InFile.close();

    //TODO Move all robots
    //TODO Calculate score

    return 0;
}
