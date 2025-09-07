#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INPUT_PATH "..\\Day9\\input.txt"


using namespace std;

struct Node {
    int fileIndex;
    int length;
    int freeSpace;
};

int main() {
    ifstream InFile(INPUT_PATH);
    string inString;
    getline(InFile, inString);
    InFile.close();
    vector<Node> files;
    unsigned long long result = 0;

    for (int pos = 0; pos < inString.size(); pos += 2) {
        Node tmpNode{pos / 2, inString[pos] - '0', inString[pos + 1] - '0'};
        files.push_back(tmpNode);
    }
    files[files.size() - 1].freeSpace = 0; //fix read out of bounds error


    for (auto fileIndex = files.size() - 1; fileIndex > 0; --fileIndex) {
        int searchIndex = 0;
        while (files[searchIndex].fileIndex != fileIndex) ++searchIndex;
        int insertIndex = 0;
        while (files[searchIndex].length > files[insertIndex].freeSpace && searchIndex > insertIndex) ++insertIndex;
        if (searchIndex > insertIndex) {
            files[searchIndex - 1].freeSpace += files[searchIndex].freeSpace + files[searchIndex].length;
            files[searchIndex].freeSpace = files[insertIndex].freeSpace - files[searchIndex].length;
            files[insertIndex].freeSpace = 0;
            files.insert(files.begin() + insertIndex + 1, files[searchIndex]);
            files.erase(files.begin() + searchIndex + 1);
        }
    }

    int filePointer = 0;
    for (int pos = 0; files[files.size() - 1].length; ++pos) {
        if (files[filePointer].length == 0) {
            if (files[filePointer].freeSpace == 0) {
                filePointer++;
            } else {
                files[filePointer].freeSpace--;
                continue;
            }
        }
        files[filePointer].length--;
        result += pos * files[filePointer].fileIndex;
    }

    cout << result;
    return 0;
}
