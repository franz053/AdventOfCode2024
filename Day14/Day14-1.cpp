#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#define INPUT_PATH "..\\Day14\\input.txt"

struct space {
    int dimX, dimY;
};

class robot {
    int posX, posY;
    const int velX, velY;
    space &hall;

public:
    robot(const int posX, const int posY, const int velX, const int velY, space &hall) : posX(posX), posY(posY),
        velX(velX), velY(velY), hall(hall) {
    }

    void move(const int steps = 1) {
        posX = (posX + (velX * steps)) % hall.dimX;
        posY = (posY + (velY * steps)) % hall.dimY;
        if (posX < 0) posX += hall.dimX;
        if (posY < 0) posY += hall.dimY;
    }

    [[nodiscard]] int getQuadrant() const {
        if (posX > hall.dimX / 2 && posY < hall.dimY / 2) return 1;
        if (posX > hall.dimX / 2 && posY > hall.dimY / 2) return 2;
        if (posX < hall.dimX / 2 && posY > hall.dimY / 2) return 3;
        if (posX < hall.dimX / 2 && posY < hall.dimY / 2) return 4;
        return 0;
    }
};

int main() {
    std::vector<robot> robots;
    space hall(101, 103);

    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    while (getline(InFile, currentLine)) {
        std::string tmpPos(currentLine.substr(currentLine.find("p=") + 2, currentLine.find(' ') - 2));
        std::string tmpVel(currentLine.substr(currentLine.find("v=") + 2, currentLine.back() - 2));

        int tmpPosX = std::stoi(tmpPos.substr(0, tmpPos.find(',')));
        int tmpPosY = std::stoi(tmpPos.substr(tmpPos.find(',') + 1));
        int tmpVelX = std::stoi(tmpVel.substr(0, tmpVel.find(',')));
        int tmpVelY = std::stoi(tmpVel.substr(tmpVel.find(',') + 1));

        robots.emplace_back(tmpPosX, tmpPosY, tmpVelX, tmpVelY, hall);
    }
    InFile.close();

    std::array<int, 5> quadrants = {};
    for (robot r: robots) {
        r.move(100);
        quadrants.at(r.getQuadrant()) += 1;
    }

    unsigned long result = quadrants[1] * quadrants[2] * quadrants[3] * quadrants[4];
    std::cout << result << std::endl;

    return 0;
}
