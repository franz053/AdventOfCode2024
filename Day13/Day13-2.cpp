#include <complex>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day13\\input.txt"

typedef unsigned long long ull;

typedef struct {
    int Ax, Ay;
    int Bx, By;
    ull X, Y;
} machine;

int main() {
    ull result = 0;

    std::vector<machine> machines;
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    while (getline(InFile, currentLine)) {
        machine tempMachine;
        tempMachine.Ax = stoi(currentLine.substr(currentLine.find('+') + 1, currentLine.find(',')));
        tempMachine.Ay = stoi(currentLine.substr(currentLine.rfind('+') + 1));
        getline(InFile, currentLine);
        tempMachine.Bx = stoi(currentLine.substr(currentLine.find('+') + 1, currentLine.find(',')));
        tempMachine.By = stoi(currentLine.substr(currentLine.rfind('+') + 1));
        getline(InFile, currentLine);
        tempMachine.X = stoi(currentLine.substr(currentLine.find('=') + 1, currentLine.find(',')));
        tempMachine.Y = stoi(currentLine.substr(currentLine.rfind('=') + 1));

        //Task 2
        tempMachine.X += 10000000000000;
        tempMachine.Y += 10000000000000;

        machines.push_back(tempMachine);
        getline(InFile, currentLine);
    }
    InFile.close();

    //check which button is more economical
    for (machine M: machines) {
        //TODO ???
    }

    std::cout << result;
    return 0;
}
