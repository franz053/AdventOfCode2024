#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day7\\input.txt"

typedef unsigned long long ull;

using namespace std;

bool isCalculationGood(ull x, vector<ull> &numbers, ull currentValue = 0, ull position = 0) {
    //Guard
    if (position == numbers.size()) {
        if (currentValue == x) return true;
        else return false;
    }

    //Check plus
    ull currentValuePlus = currentValue + numbers.at(position);
    if (currentValuePlus <= x) {
        if (isCalculationGood(x, numbers, currentValuePlus, position + 1)) return true;
    }

    //Check mul
    if (position == 0) currentValue = 1; //Account for neutral element of multiplication
    ull currentValueMul = currentValue * numbers.at(position);
    if (currentValueMul <= x) {
        if (isCalculationGood(x, numbers, currentValueMul, position + 1)) return true;
    }
    return false;
}

int main() {
    ull result = 0;
    ifstream InFile(INPUT_PATH);
    string currentLine;
    while (getline(InFile, currentLine)) {
        ull x, y;
        vector<ull> numbers;
        stringstream lineStream(currentLine);
        lineStream >> x; //x holds result of equation
        lineStream.ignore(); //Skip the colon
        while (lineStream >> y) numbers.push_back(y);
        if (isCalculationGood(x, numbers)) result += x;
    }
    cout << result;
    return 0;
}
