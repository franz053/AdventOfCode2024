#include <iostream>
#include <regex>
#include <string>
#include <fstream>

#define INPUT_PATH "..\\Day3\\input.txt"

int main(){
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    const std::regex expression("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    int result = 0;

    while (std::getline(InFile, currentLine)) {
        
        std::smatch match;
        while(std::regex_search(currentLine,match,expression)){
            std::string found = match.str();
            int num1 = std::stoi(found.substr(4,found.find(',')-1));
            int num2 = std::stoi(found.substr(found.find(',')+1,found.length()-1));
            result += num1*num2;
            currentLine = match.suffix().str();
        }
    }
    std::cout << result;
}