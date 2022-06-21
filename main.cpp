#include <iostream>
#include <algorithm>
#include <chrono>

#include "pagerank.h"

using namespace std::chrono;

inline void set_random(pagerank::matrix::matrix_t &matrix, const int size) {
    matrix.resize(size);

    for(int i = 0; i < size; ++i) {
        matrix[i].resize(size);
        for(int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 2;
        }
    }
}

int main() {
    pagerank::matrix::matrix_t matrix = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},  //<-- simple
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            /*{0, 1, 0},
            {0, 0, 1},  //<-- cycle
            {1, 0, 0},*/
    };

    //set_random(matrix, 1000);

    auto start_time = high_resolution_clock::now();
    auto score = pagerank::compute(matrix);
    auto end_time = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(end_time - start_time).count() << " ms" << std::endl;

    for (int i = 0; i < matrix.size(); i++) {
        std::cout << i << "-" << score[i] << std::endl;
    }
}