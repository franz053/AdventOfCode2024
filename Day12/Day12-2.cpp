#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day12\\input.txt"

//Additional challenge: use only one vector

//I am not a fan of this, but I couldn't get it to work with just one vector otherwise
void cleanup(std::vector<std::string> &farm) {
    for (int row = 1; row < farm.size() - 1; ++row) {
        for (int column = 1; column < farm[0].length() - 1; ++column) {
            if (farm[row][column] == '#') farm[row][column] = ' ';
        }
    }
}

void traversePlot(const int row, const int column, std::vector<std::string> &farm, long &area, long &corners) {
    const char plant = farm[row][column];
    farm[row][column] = '#'; //already visited marker
    area++;

    //Check corners
    for (int i = -1; i <= 2; i += 2) {
        for (int j = -1; j <= 2; j += 2) {
            //Check outward corners
            if (farm[row + i][column] != plant && farm[row + i][column] != '#') {
                if (farm[row][column + j] != plant && farm[row][column + j] != '#') corners++;
            }

            //Check inward corners
            if (farm[row + i][column] == plant || farm[row + i][column] == '#') {
                if (farm[row][column + j] == plant || farm[row][column + j] == '#') {
                    if (farm[row + i][column + j] != plant && farm[row + i][column + j] != '#') corners++;
                }
            }
        }
    }

    //Check for neighbors to continue
    if (farm[row][column - 1] == plant) traversePlot(row, column - 1, farm, area, corners);
    if (farm[row][column + 1] == plant) traversePlot(row, column + 1, farm, area, corners);
    if (farm[row - 1][column] == plant) traversePlot(row - 1, column, farm, area, corners);
    if (farm[row + 1][column] == plant) traversePlot(row + 1, column, farm, area, corners);

}

//returns price of plot and deletes it from the map
//number of sides is equal to number of corners (both inwards and outwards)
unsigned long settlePlot(const int row, const int column, std::vector<std::string> &farm) {
    long area = 0, corners = 0;
    traversePlot(row, column, farm, area, corners);
    cleanup(farm);
    return area * corners;
}

int main() {
    unsigned long price = 0;

    std::vector<std::string> farm;

    //Read in file
    std::ifstream inputFile;
    inputFile.open(INPUT_PATH);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) farm.push_back(" " + line + " "); //Padding for later
        inputFile.close();
    } else {
        std::cerr << "Error opening file " << INPUT_PATH << std::endl;
    }

    //Add padding
    farm.insert(farm.begin(), std::string(farm[0].length(), ' '));
    farm.emplace_back(farm[0].length(), ' ');

    for (int row = 1; row < farm.size() - 1; ++row) {
        for (int column = 1; column < farm[0].length() - 1; ++column) {
            if (farm[row][column] != ' ') price += settlePlot(row, column, farm);
        }
    }

    std::cout << price << std::endl;
    return 0;
}
