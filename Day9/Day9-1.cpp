#include <iostream>
#include <fstream>
#include <string>

#define INPUT_PATH "..\\Day9\\input.txt"


using namespace std;

int main() {
    unsigned long long result = 0;
    ifstream InFile(INPUT_PATH);
    string inString;
    getline(InFile, inString);
    InFile.close();

    int right = static_cast<int>(inString.size() / 2); //index from right
    int left = 0; //index from left

    int input[inString.size()];
    int values[right];
    int amountFiles = 0;
    for (int i = 0; i < inString.size(); ++i) {
        input[i] = inString[i] - '0';
        if (!(i % 2)) {
            values[i / 2] = input[i];
            amountFiles += input[i];
        }
    }

    int pointer = 0; //position in input string
    for (int position = 0; position < amountFiles;) {
        if (pointer % 2) {
            //odd = right
            if (input[pointer]) {
                if (!values[right]) right--;
                values[right]--;
                result += position * right;
                input[pointer]--;
                position++;
            } else {
                pointer++;
            }
        } else {
            //even = left
            if (input[pointer]) {
                result += position * left;
                input[pointer]--;
                position++;
            } else {
                pointer++;
                left++;
            }
        }
    }

    cout << result;
    return 0;
}

