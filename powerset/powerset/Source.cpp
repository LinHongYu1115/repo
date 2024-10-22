#include <iostream>
#include <chrono>
using namespace std;

void printSubset(char subset[][100], int size) {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << subset[i] << " ";
    }
    cout << "}" << endl;
}

void generatePowerSet(char S[][100], int n, char subset[][100], int size, int index) {
    if (index == n) {
        printSubset(subset, size);
        return;
    }

    generatePowerSet(S, n, subset, size, index + 1);

    for (int i = 0; i < 100; i++) {
        subset[size][i] = S[index][i];
    }
    generatePowerSet(S, n, subset, size + 1, index + 1);
}

void parseInput(char input[], char S[][100], int& n, int index = 0, int tempIndex = 0) {
    static char temp[100];

    if (input[index] == '\0') {
        if (tempIndex != 0) {
            for (int i = 0; i < tempIndex; i++) {
                S[n][i] = temp[i];
            }
            S[n][tempIndex] = '\0';
            n++;
        }
        return;
    }

    if (input[index] == ' ') {
        if (tempIndex != 0) {
            for (int i = 0; i < tempIndex; i++) {
                S[n][i] = temp[i];
            }
            S[n][tempIndex] = '\0';
            n++;
            tempIndex = 0;
        }
    }
    else {
        temp[tempIndex++] = input[index];
    }

    parseInput(input, S, n, index + 1, tempIndex);
}

int main() {
    char input[1000];
    cout << "請輸入集合的元素(以空格分隔): ";
    cin.getline(input, 1000);

    char S[100][100];
    int n = 0;

    auto startParse = chrono::high_resolution_clock::now();
    parseInput(input, S, n);
    auto endParse = chrono::high_resolution_clock::now();
    auto parseDuration = chrono::duration_cast<chrono::milliseconds>(endParse - startParse);

    char subset[100][100];

    cout << "冪集合為:" << endl;
    auto startPowerSet = chrono::high_resolution_clock::now();
    generatePowerSet(S, n, subset, 0, 0);
    auto endPowerSet = chrono::high_resolution_clock::now();
    auto powerSetDuration = chrono::duration_cast<chrono::milliseconds>(endPowerSet - startPowerSet);

    cout << "解析時間: " << parseDuration.count() << " 毫秒" << endl;
    cout << "冪集合計算時間: " << powerSetDuration.count() << " 毫秒" << endl;

    return 0;
}
