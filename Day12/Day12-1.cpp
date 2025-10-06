#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#define INPUT_PATH "..\\Day12\\input.txt"

struct record {
    long area = 0;
    long perimeter = 0;
};

int main() {
    std::vector<std::string> farm;

    //Read in file
    std::ifstream inputFile;
    inputFile.open(INPUT_PATH);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) farm.push_back("  " + line + " "); //Padding for later
        inputFile.close();
    } else {
        std::cerr << "Error opening file " << INPUT_PATH << std::endl;
    }

    //Add padding
    farm.insert(farm.begin(), std::string(farm[0].length(), ' '));
    farm.insert(farm.begin(), std::string(farm[0].length(), ' '));
    farm.emplace_back(farm[0].length(), ' ');

    //first = area, second = perimeter
    std::unordered_map<char, record> records;

    for (int row = 2; row < farm.size() - 1; ++row) {
        for (int column = 2; column < farm[0].length() - 1; ++column) {
            char element = farm[row][column];

            //calc area
            records[element].area += 1; //counts all areas

            //calc perimeter
            if (farm[row + 1][column] != element) records[element].perimeter += 1; //if element south is different
            if (farm[row - 1][column] != element) records[element].perimeter += 1; //if element south is different
            if (farm[row][column + 1] != element) records[element].perimeter += 1; //if element south is different
            if (farm[row][column - 1] != element) records[element].perimeter += 1; //if element south is different
        }
    }

    //calculate price
    unsigned long price = 0;
    for (auto [key, value]: records) {
        price += value.area * value.perimeter;
    }
    std::cout << price << std::endl;
    return 0;
}
