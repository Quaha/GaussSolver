#pragma once

#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"

class GaussSolver {

public:
	static inline const long double EPS = 1e-12;
	std::vector<Vector> solve(const Matrix &A, const Vector &B);

};