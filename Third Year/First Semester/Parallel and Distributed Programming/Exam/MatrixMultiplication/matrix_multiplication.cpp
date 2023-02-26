#include <iostream>
#include <thread>
#include <future>

void multiply_line(
    int line,
    const std::vector<std::vector<int>>& mat1,
    const std::vector<std::vector<int>>& mat2,
    std::vector<std::vector<int>>& res) {

    for (int i = 0; i < res[line].size(); ++i) {
        for (int j = 0; j < mat1[line].size(); ++j) {
            res[line][i] += mat1[line][j] * mat2[j][i];
        }
    }
}

void multiply(
    int start,
    int end,
    int nrThreads,
    const std::vector<std::vector<int>>& mat1,
    const std::vector<std::vector<int>>& mat2,
    std::vector<std::vector<int>>& res) {

    if (start == end) {
        multiply_line(start, mat1, mat2, res);
        return;
    }

    if (nrThreads == 1) {
        for (int i = start; i <= end; ++i) {
            multiply_line(i, mat1, mat2, res);
        }
        return;
    }

    int mid = (start + end) / 2;

    std::thread t1([mid, end, nrThreads, &mat1, &mat2, &res] {
        multiply(mid + 1, end, nrThreads / 2, mat1, mat2, res);
        });

    multiply(start, mid, nrThreads - (nrThreads / 2), mat1, mat2, res);

    t1.join();
}

int main() {
    std::vector<std::vector<int>> mat1 = { {11, 3}, {7, 11}, {2, 4} };
    std::vector<std::vector<int>> mat2 = { {8, 0, 1}, {0, 3, 5} };

    std::vector<std::vector<int>> res = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

    multiply(0, 2, 4, mat1, mat2, res);

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            std::cout << res[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}