#include <cstdio>
#include <cmath>
#include <vector>

#ifndef PAGERANK_H
#define PAGERANK_H

namespace pagerank {
    namespace matrix {
        typedef std::vector<double> column_t;
        typedef std::vector<std::vector<double>> matrix_t;

        // Multiply matrix by scalar
        // Product stored in the matrix
        void scalar_multiplication(matrix_t &matrix, int num_rows, int num_cols, double scalar) {
            for (int i = 0; i < num_rows; i++)
                for (int j = 0; j < num_cols; j++)
                    matrix[i][j] *= scalar;
        }
        void scalar_multiplication(column_t &matrix, int num_rows, double scalar) {
            for (int i = 0; i < num_rows; i++)
                matrix[i] *= scalar;
        }

        // Multiply matrix by column
        // Product stored in the column
        // Column must have num_cols rows
        void column_multiplication(matrix_t &matrix, int num_rows, int num_cols, column_t &column) {
            double product[num_cols];

            for (int i = 0; i < num_rows; i++) {
                double sum = 0;

                for (int j = 0; j < num_cols; j++)
                    sum += matrix[i][j] * column[j];

                product[i] = sum;
            }

            // Copy entries in the column
            for (int i = 0; i < num_cols; i++)
                column[i] = product[i];
        }

        // Sum two matrices
        // Sum stored in the first matrix
        // Matrices must have the same dimensions
        void addition(column_t &matrix1, column_t &matrix2, int num_rows) {
            for (int i = 0; i < num_rows; i++)
                matrix1[i] += matrix2[i];
        }

        // Return Euclidean norm of column
        double norm(column_t &column, int num_rows) {
            double sum = 0;

            for (int i = 0; i < num_rows; i++)
                sum += std::pow(column[i], 2);

            return std::sqrt(sum);
        }
    }

    //weight(d, damping factor) - real in (0, 1), best at 0.15
    //error(min score) - real in (0, +inf), best at 0.0001
    matrix::column_t compute(matrix::matrix_t &link_matrix, const double weight = 0.15, const double error = 0.0001) {
        using namespace matrix;
        auto size = (int)link_matrix.size();


        for (int i = 0; i < size; ++i) {
            uint count = 0;

            for (int j = 0; j < size; ++j)
                if (link_matrix[j][i] == 1)
                    count++;

            if (count <= 1) continue;

            for (int j = 0; j < size; ++j)
                if (link_matrix[j][i] == 1)
                    link_matrix[j][i] = 1 / double(count);
        }

        // Initialize mean column and score column
        column_t mean_column(size), score_column(size);
        for (int i = 0; i < size; i++) {
            double entry = 1 / (double) size;
            mean_column[i] = entry;
            score_column[i] = entry;
        }

        // Weigh link matrix and mean column
        scalar_multiplication(link_matrix, size, size, 1 - weight);
        scalar_multiplication(mean_column, size, weight);

        double score_norm;

        do {
            // Store score column before operations
            column_t score_diff(size);

            for (int i = 0; i < size; i++)
                score_diff[i] = score_column[i];

            // Multiply score column by weighted link matrix
            column_multiplication(link_matrix, size, size, score_column);

            // Add weighted mean column to score column
            addition(score_column, mean_column, size);

            // Subtract previous score column from score column
            scalar_multiplication(score_diff, size, -1);
            addition(score_diff, score_column, size);

            // Calculate norm of the difference
            score_norm = norm(score_diff, size);

            // Repeat until score norm is smaller than error
        } while (score_norm > error);

        return score_column;
    }
}

#endif