#pragma once

#include <iostream>
#include <vector>

#include "Vector.hpp"

class Matrix {
private:
	std::vector<Vector> matrix;
public:

	Matrix(int N, int M);
	double& operator()(int i, int j);
	double operator()(int i, int j) const;

	std::pair<int, int> size() const;

};