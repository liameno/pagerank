#include <iostream>
#include <algorithm>

#include "pagerank.h"

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

    auto score = pagerank::compute(matrix);

    for (int i = 0; i < matrix.size(); i++) {
        std::cout << i << "-" << score[i] << std::endl;
    }
}