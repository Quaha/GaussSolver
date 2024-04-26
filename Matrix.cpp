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