#include <iostream>
#include <chrono>

using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (m > 0 && n == 0) {
        return ackermann_recursive(m - 1, 1);
    }
    else {
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
    }
}

int main() {
    int m, n;

    cout << "輸入 m 和 n 的值: ";
    cin >> m >> n;

    auto start = chrono::high_resolution_clock::now();
    int result = ackermann_recursive(m, n);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::micro> duration = end - start;

    cout << "Ackermann(" << m << ", " << n << ") (遞迴) = " << result << endl;
    cout << "執行時間: " << duration.count() << " 微秒" << endl;

    return 0;
}
