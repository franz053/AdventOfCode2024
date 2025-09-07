#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define INPUT_PATH "..\\Day1\\input.txt"


void swap(std::vector<int> &v, int x, int y) {
    int temp = v.at(x);
    v.at(x) = v.at(y);
    v.at(y) = temp;
}

void quicksort(std::vector<int> &vec, int L, int R) {
    if (L == R) return;
    int piv = vec.at(R);
    int split = R;
    for (int i = R - 1; i >= L; --i) {
        if (piv < vec.at(i)) {
            swap(vec, split, i);
            --split;
            swap(vec, split, i);
        }
    }
    quicksort(vec, 0, split - 1);
    quicksort(vec, split, R);
}


int main() {
    std::ifstream InFile(INPUT_PATH);
    std::string currentLine;
    std::vector<int> list1;
    std::vector<int> list2;
    while (std::getline(InFile, currentLine)) {
        std::stringstream currentLineStream(currentLine);
        std::string word;
        currentLineStream >> word;
        list1.push_back(stoi(word));
        currentLineStream >> word;
        list2.push_back(stoi(word));
    }

    quicksort(list1, 0, list1.size() - 1);
    quicksort(list2, 0, list2.size() - 1);

    int result = 0;

    int list2Index = 0;
    for (int list1Index = 0; list1Index < list1.size(); ++list1Index) {
        if (list1.at(list1Index) > list2.back()) break;
        int currentNumAmount = 1;
        while (list1.at(list1Index) == list1.at(list1Index + 1)) {
            ++list1Index;
            ++currentNumAmount;
        }
        while (list2.at(list2Index) < list1.at(list1Index)) ++list2Index;
        while (list2.at(list2Index) == list1.at(list1Index)) {
            result += (list1.at(list1Index) * currentNumAmount);
            ++list2Index;
        }
    }

    std::cout << result;

    return 0;
}
