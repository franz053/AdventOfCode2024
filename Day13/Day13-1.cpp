#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day13\\input.txt"

using namespace std;

typedef struct{
    int Ax, Ay;
    int Bx, By;
    int X, Y;
} machine;

int main(){
    int result = 0;

    vector<machine> machines;
    ifstream InFile(INPUT_PATH);
    string currentLine;
    while (getline(InFile, currentLine)){
        machine tempMachine;
        tempMachine.Ax = stoi(currentLine.substr(currentLine.find('+')+1,currentLine.find(',')));
        tempMachine.Ay = stoi(currentLine.substr(currentLine.rfind('+')+1));
        getline(InFile, currentLine);
        tempMachine.Bx = stoi(currentLine.substr(currentLine.find('+')+1,currentLine.find(',')));
        tempMachine.By = stoi(currentLine.substr(currentLine.rfind('+')+1));
        getline(InFile, currentLine);
        tempMachine.X = stoi(currentLine.substr(currentLine.find('=')+1,currentLine.find(',')));
        tempMachine.Y = stoi(currentLine.substr(currentLine.rfind('=')+1));
        machines.push_back(tempMachine);
        getline(InFile, currentLine);
    }
    InFile.close();

    // An = X-Bn*Bx/Ax
    for(machine M : machines){
        int lowestTokens = 0;
        for (int Bn = 0; Bn <= 100; Bn++){
            int An = (M.X-(Bn*M.Bx))/(M.Ax);
            //If An is whole number
            if(M.X == An*M.Ax + Bn*M.Bx && An <= 100){
                if(M.Y == An*M.Ay + Bn*M.By){
                    int tempTokens = An*3+Bn;
                    if(tempTokens < lowestTokens || lowestTokens == 0) lowestTokens = tempTokens;
                }
            }
        }
        if(lowestTokens) result += lowestTokens;
    }

    cout << result;
    return 0;
}
