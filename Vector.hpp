#pragma once

class Vector {

protected:
	unsigned int real_size = 0;
	unsigned int capacity = 0;
	double* data_ptr = nullptr;

	void storage_expansion();
	void storage_decrease();

public:
	Vector();
	Vector(int N);
	Vector(const Vector& V);
	~Vector();

	Vector& operator=(const Vector& V);

	unsigned int size() const;
	bool empty() const;

	void clear();

	void push_back(double value);
	void pop_back();
	double back() const;

	double& operator[](int i);
	double operator[](int i) const;

	static void swap(Vector& V1, Vector& V2);

};