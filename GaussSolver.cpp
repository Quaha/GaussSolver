#include <vector>
#include <iostream>

#include "Vector.hpp"
#include "Matrix.hpp"
#include "GaussSolver.hpp"

bool isZero(long double V) {
	return (abs(V) < GaussSolver::EPS);
}

std::vector<Vector> GaussSolver::solve(const Matrix &A, const Vector &B) {
	if (A.matrix.size() == 0 || A.matrix.size() != B.size()) {
		return {};
	}

	int N = A.matrix.size();
	int M = A.matrix[0].size();

	std::vector<std::vector<long double>> SLE(N, std::vector<long double>(M + 1, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			SLE[i][j] = A(i, j);
		}
	}

	for (int i = 0; i < N; i++) {
		SLE[i][M] = B[i];
	}
	
	std::vector<std::pair<int, int>> swaps_stack(0);
	for (int i = 0, j = 0; i < N && j < M; i++, j++) {
		int best = i;
		for (int k = i + 1; k < N; k++) {
			if (abs(SLE[k][j]) > abs(SLE[best][j])) {
				best = k;
			}
		}
		if (isZero(SLE[best][j])) {
			i--;
			continue;
		}
		swap(SLE[best], SLE[i]);
		for (int k = j + 1; k < M + 1; k++) {
			SLE[i][k] /= SLE[i][j];
		}
		SLE[i][j] = 1;
		for (int i1 = 0; i1 < N; i1++) {
			if (i1 == i) continue;
			long double C = SLE[i1][j] / SLE[i][j];
			for (int k = j + 1; k < M + 1; k++) {
				SLE[i1][k] -= SLE[i][k] * C;
			}
			SLE[i1][j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		bool flag = true;
		for (int j = 0; j < M; j++) {
			if (!isZero(SLE[i][j])) {
				flag = false;
			}
		}
		if (!isZero(SLE[i][M]) && flag) {
			return {};
		}
	}

	std::vector<std::vector<long double>> result(M, std::vector<long double>(M + 1));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M + 1; j++) {
			result[i][j] = 0;
		}
	}

	for (int i = 0; i < M; i++) {
		result[i][i] = 1;
	}

	for (int i = 0; i < N; i++) {
		int j = 0;
		while (j < M + 1 && isZero(SLE[i][j])) j++;
		if (j == M + 1) continue;
		result[j][j] = 0;
		for (int k = j + 1; k < M; k++) {
			result[j][k] = -SLE[i][k];
		}
		result[j][M] = SLE[i][M];
	}

	std::vector<Vector> Tresult(M + 1, Vector(M));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M + 1; j++) {
			Tresult[j][i] = result[i][j];
		}
	}

	Vector::swap(Tresult[0], Tresult.back());
	for (int i = 0; i < Tresult[0].size(); i++) {
		if (isZero(Tresult[0][i])) {
			Tresult[0][i] = 0;
		}
	}

	for (int i = 1; i < Tresult.size(); i++) {
		bool flag = true;
		for (int j = 0; j < M; j++) {
			if (!isZero(Tresult[i][j])) {
				flag = false;
			}
			else {
				Tresult[i][j] = 0;
			}
		}
		if (flag) {
			Vector::swap(Tresult[i], Tresult.back());
			Tresult.pop_back();
			i--;
		}
	}
	return Tresult;

	return {};
}