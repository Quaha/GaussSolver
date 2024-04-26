#pragma once

#include <vector>
#include "Vector.hpp"

class Matrix {

public:
	std::vector<Vector> matrix;

	Matrix(int N, int M);
	double& operator()(int i, int j);
	double operator()(int i, int j) const;

};