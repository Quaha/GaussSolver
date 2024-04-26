#include <iostream>

#include "Matrix.hpp"

Matrix::Matrix(int N, int M) {
	matrix.resize(N, Vector(M));
}

double& Matrix::operator()(int i, int j) {
	return matrix[i][j];
}
double Matrix::operator()(int i, int j) const{
	return matrix[i][j];
}

std::pair<int, int> Matrix::size() const {
	int N = matrix.size();
	int M = 0;
	if (N != 0) {
		M = matrix[0].size();
	}
	return { N, M };
}