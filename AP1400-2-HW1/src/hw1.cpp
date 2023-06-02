#include "hw1.h"

#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

namespace algebra {

Matrix zeros(std::size_t n, std::size_t m) {
  Matrix matrix(n, std::vector<double>(m, 0));
  return matrix;
}

Matrix ones(std::size_t n, std::size_t m) {
  Matrix matrix(n, std::vector<double>(m, 1));
  return matrix;
}

Matrix random(std::size_t n, std::size_t m, double min, double max) {
  if (min > max) {
    throw std::logic_error("min can't be greater than max\n");
  }

  Matrix matrix(n, std::vector<double>(m, 0));
  std::default_random_engine e;
  std::uniform_real_distribution<double> u(min, max);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = u(e);
    }
  }
  return matrix;
}

void show(const Matrix &matrix) {
  for (auto &i : matrix) {
    for (auto &j : i) {
      std::cout << std::fixed << std::setprecision(3) << j << " ";
    }
    std::cout << std::endl;
  }
}

Matrix multiply(const Matrix &matrix, double c) {
  Matrix ans = zeros(matrix.size(), matrix[0].size());
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      ans[i][j] = matrix[i][j] * c;
    }
  }
  return ans;
}

Matrix multiply(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.empty() && matrix2.empty()) {
    return Matrix{};
  }

  if (matrix1.empty() || matrix2.empty()) {
    throw std::logic_error("calculation error\n");
  }

  if (matrix1[0].size() != matrix2.size()) {
    throw std::logic_error("dimenssion errors\n");
  }

  Matrix ans = zeros(matrix1.size(), matrix2[0].size());
  for (int i = 0; i < matrix1.size(); i++) {
    for (int j = 0; j < matrix2[0].size(); j++) {
      for (int k = 0; k < matrix1[0].size(); k++) {
        ans[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return ans;
}

Matrix sum(const Matrix &matrix, double c) {
  if (matrix.empty()) {
    return Matrix{};
  }
  
  Matrix ans = zeros(matrix.size(), matrix[0].size());
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      ans[i][j] = matrix[i][j] + c;
    }
  }
  return ans;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
  if (matrix1.empty() && matrix2.empty()) {
    return Matrix{};
  }
  if (matrix1.empty() || matrix2.empty()) {
    throw std::logic_error("calculation error\n");
  }
  if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
    throw std::logic_error("dimenssion errors\n");
  }

  Matrix ans = zeros(matrix1.size(), matrix1[0].size());
  for (int i = 0; i < matrix1.size(); i++) {
    for (int j = 0; j < matrix1[0].size(); j++) {
      ans[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
  return ans;
}

Matrix transpose(const Matrix& matrix) {
  if (matrix.empty()) {
    return Matrix{};
  }
  Matrix ans = zeros(matrix[0].size(), matrix.size());
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      ans[j][i] = matrix[i][j];
    }
  }
  return ans;
}

Matrix minor(const Matrix& matrix, std::size_t n, std::size_t m) {
  if (n < 0 || n >= matrix.size() || m < 0 || m >= matrix[0].size()) {
    throw std::logic_error("out of bound\n");
  }
  
  Matrix ans = zeros(matrix.size() - 1, matrix[0].size() - 1);
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (i == n || j == m) {
        continue;
      }
      ans[i - (i > n)][j - (j > m)] = matrix[i][j];
    }
  }
  return ans;
}

double determinant(const Matrix& matrix) {
  if (matrix.empty()) {
    return 1;
  }
  auto n = matrix.size();
  auto m = matrix[0].size();
  if (n != m) {
    throw std::logic_error("matrix is not square\n");
  }
  if (n == 1) {
    return matrix[0][0];
  }
  double ans = 0;
  for (int i = 0; i < n; i++) {
    ans += matrix[i][0] * determinant(minor(matrix, i, 0)) * ((i % 2) ? -1 : 1);
  }
  return ans;
}

Matrix inverse(const Matrix& matrix) {
  if (matrix.empty()) {
    return Matrix{};
  }
  auto n = matrix.size();
  auto m = matrix[0].size();
  if (n != m || determinant(matrix) == 0) {
    throw std::logic_error("matrix is not square or determinant is zero\n");
  }

  Matrix ans = zeros(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans[i][j] = determinant(minor(matrix, j, i)) * (((i + j) % 2) ? -1 : 1);
    }
  }

  return multiply(ans, 1 / determinant(matrix));
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
  auto n1 = matrix1.size();
  auto m1 = matrix1[0].size();
  auto n2 = matrix2.size();
  auto m2 = matrix2[0].size();
  if (axis == 0) {
    if (m1 != m2) {
      throw std::logic_error("dimenssion errors\n");
    }

    Matrix ans = zeros(n1 + n2, m1);
    for (int i = 0; i < n1 + n2; i++) {
      for (int j = 0; j < m1; j++) {
        if (i < n1) {
          ans[i][j] = matrix1[i][j];
        } else {
          ans[i][j] = matrix2[i - n1][j];
        }
      }
    }

    return ans;
  } else {
    if (n1 != n2) {
      throw std::logic_error("dimenssion errors\n");
    }

    Matrix ans = zeros(n1, m1 + m2);
    for (int i = 0; i < n1; i++) {
      for (int j = 0; j < m1 + m2; j++) {
        if (j < m1) {
          ans[i][j] = matrix1[i][j];
        } else {
          ans[i][j] = matrix2[i][j - m1];
        }
      }
    }

    return ans;
  }
}

Matrix ero_swap(const Matrix& matrix, std::size_t r1, std::size_t r2) {
  if (r1 >= matrix.size() || r2 >= matrix.size()) {
    throw std::logic_error("out of bound\n");
  }
  auto ans = matrix;
  std::swap(ans[r1], ans[r2]);
  return ans;
}

Matrix ero_multiply(const Matrix& matrix, std::size_t r, double c) {
  if (r >= matrix.size()) {
    throw std::logic_error("out of bound\n");
  }
  auto ans = matrix;
  for (int i = 0; i < matrix[0].size(); i++) {
    ans[r][i] *= c;
  }
  return ans;
}

Matrix ero_sum(const Matrix& matrix, std::size_t r1, double c, std::size_t r2) {
  if (r1 >= matrix.size() || r2 >= matrix.size()) {
    throw std::logic_error("out of bound\n");
  }
  auto ans = matrix;
  for (int i = 0; i < matrix[0].size(); i++) {
    ans[r2][i] += c * ans[r1][i];
  }
  return ans;
}

Matrix upper_triangular(const Matrix& matrix) {
  if (matrix.empty()) {
    return Matrix{};
  }
  if (matrix.size() != matrix[0].size()) {
    throw std::logic_error("matrix is not square\n");
  }

  Matrix ans = matrix;
  auto n = matrix.size();
  for (int i = 0; i < n; i++) {
    int row = i;
    while (row < n && ans[row][i] == 0) {
      row++;
    }
    if (row == n) {
      throw std::logic_error("matrix is not invertible\n");
    }
    std::swap(ans[i], ans[row]);
    for (int j = i + 1; j < n; j++) {
      ans = ero_sum(ans, i, -ans[j][i] / ans[i][i], j);
    }
  }
  return ans;
}
}  // namespace algebra