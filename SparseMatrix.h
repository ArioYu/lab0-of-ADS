#pragma once

#include <string>
#include <vector>
#define max_size 100000
class Triple{
public:
  int i,j;//矩阵元素的行数列数
  int val;//矩阵元素value
};
class SparseMatrix {
private:
  int _row=0;
  int _col=0;
  int _num=0;//非0元素个数
  std::vector<int> Ax;
  std::vector<int> Aj;
  std::vector<int> Ap;
  /* TODO: Add any necessary data structure here. */

public:
  SparseMatrix() = default;

  SparseMatrix(const std::string input_file);

  void to_file(const std::string output_file);

  SparseMatrix operator*(const SparseMatrix &right);
};