#include <iostream>
#include <fstream>
#include <sstream>

#define INPUT_PATH "C:\\Users\\franz\\CLionProjects\\AdventOfCode2024\\Day2\\input.txt"

int main() {
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    bool ascending;
    int num1, num2, result = 0;
    while (std::getline(InFile, currentLine)) {
        std::stringstream currentLineStream(currentLine);
        currentLineStream >> num1;
        currentLineStream >> num2;
        ascending = (num2 > num1);
        bool safe = true;
        do{
            int diff = num2-num1;
            if(ascending){
                //ascending
                if(diff > 3 || diff <= 0) {
                    safe = false;
                }
            }else{
                //descending
                if(diff < -3 || diff >= 0){
                    safe = false;
                }
            }
            num1 = num2;
        }while(currentLineStream >> num2 && safe);
        if(safe) result++;
    }
    std::cout << result;
}