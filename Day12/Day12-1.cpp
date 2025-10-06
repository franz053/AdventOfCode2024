#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day12\\input.txt"


void traversePlot(const int row, const int column, std::vector<std::string> &farm, int& area, int& perimeter) {
    char plant = farm[row][column];
    farm[row][column] = '#'; //already visited marker
    area++;
    //Check around for perimeter
    if (farm[row-1][column] != plant && farm[row-1][column] != '#') perimeter++;
    if (farm[row+1][column] != plant && farm[row+1][column] != '#') perimeter++;
    if (farm[row][column-1] != plant && farm[row][column-1] != '#') perimeter++;
    if (farm[row][column+1] != plant && farm[row][column+1] != '#') perimeter++;

    //Check for neighbors to continue
    if (farm[row-1][column] == plant) traversePlot(row-1,column,farm,area,perimeter);
    if (farm[row+1][column] == plant) traversePlot(row+1,column,farm,area,perimeter);
    if (farm[row][column-1] == plant) traversePlot(row,column-1,farm,area,perimeter);
    if (farm[row][column+1] == plant) traversePlot(row,column+1,farm,area,perimeter);

    farm[row][column] = ' ';
}

//returns price of plot and deletes it from the map
int settlePlot(int row, int column, std::vector<std::string> &farm) {
    int area = 0, perimeter = 0;
    traversePlot(row, column, farm, area, perimeter);
    return area*perimeter;
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
    farm.insert(farm.begin(),std::string(farm[0].length(),' '));
    farm.emplace_back(farm[0].length(), ' ');

    for (int row = 1; row < farm.size() - 1; ++row) {
        for (int column = 1; column < farm[0].length() - 1; ++column) {
            if (farm[row][column] != ' ') price += settlePlot(row, column, farm);
        }
    }

    std::cout << price << std::endl;
    return 0;
}
