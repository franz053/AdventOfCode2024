#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day7\\input.txt"

typedef unsigned long long ull;

using namespace std;

bool isCalculationGood(ull x, vector<int> &numbers, ull currentValue = 0, int position = 0) {
    //Guard
    if (position == numbers.size()) {
        if (currentValue == x) return true;
        else return false;
    }

    ull tmpValue;
    //Check mul
    tmpValue = (position == 0) ? numbers.at(position) : currentValue * numbers.at(position);
    if (tmpValue <= x) {
        if (isCalculationGood(x, numbers, tmpValue, position + 1)) return true;
    }

    //Check concat
    tmpValue = numbers.at(position) + [&numbers, position, currentValue]() {
        int x = 1;
        while (numbers.at(position) >= x) x *= 10;
        return currentValue * x;
    }();
    if (tmpValue <= x) {
        if (isCalculationGood(x, numbers, tmpValue, position + 1)) return true;
    }

    //Check plus
    tmpValue = currentValue + numbers.at(position);
    if (tmpValue <= x) {
        if (isCalculationGood(x, numbers, tmpValue, position + 1)) return true;
    }
    return false;
}


int main() {
    ull result = 0;
    ifstream InFile(INPUT_PATH);
    string currentLine;
    while (getline(InFile, currentLine)) {
        ull x;
        int y;
        vector<int> numbers;
        stringstream lineStream(currentLine);
        lineStream >> x; //x holds result of equation
        lineStream.ignore(); //Skip the colon
        while (lineStream >> y) numbers.push_back(y);
        if (isCalculationGood(x, numbers)) result += x;
    }
    cout << result;
    return 0;
}
