#include "Vector.hpp"

#include <iostream>

Vector::Vector() {
	real_size = 0;
	capacity = 1;
	data_ptr = new double[1];
}

Vector::Vector(int N) {
	real_size = N;
	capacity = 2 * N;
	data_ptr = new double[capacity];
}

Vector::Vector(const Vector& V) {
	double* temp_storage_ptr = new double[V.capacity];
	for (int i = 0; i < V.real_size; i++) {
		temp_storage_ptr[i] = V.data_ptr[i];
	}

	this->real_size = V.real_size;
	this->capacity = V.capacity;
	delete[] this->data_ptr;
	this->data_ptr = temp_storage_ptr;
}

Vector::~Vector() {
	delete[] data_ptr;
}

Vector& Vector::operator=(const Vector& V) {
	double* temp_storage_ptr = new double[V.capacity];
	for (int i = 0; i < V.real_size; i++) {
		temp_storage_ptr[i] = V.data_ptr[i];
	}

	this->real_size = V.real_size;
	this->capacity = V.capacity;
	delete[] this->data_ptr;
	this->data_ptr = temp_storage_ptr;

	return (*this);
}

unsigned int Vector::size() const {
	return real_size;
}

bool Vector::empty() const {
	return (real_size == 0);
}

void Vector::clear() {
	while (!empty()) {
		pop_back();
	}
}

void Vector::storage_expansion() {
	if (real_size == capacity) {
		double* temp_storage_ptr = new double[capacity * 2];
		for (int i = 0; i < capacity; i++) {
			temp_storage_ptr[i] = this->data_ptr[i];
		}

		this->capacity *= 2;
		delete[] this->data_ptr;
		this->data_ptr = temp_storage_ptr;
	}
}

void Vector::push_back(double value) {
	data_ptr[real_size++] = value;
	storage_expansion();
}

void Vector::storage_decrease() {
	if ((real_size + 1 <= capacity / 4) && (capacity > 1)) {
		double* temp_storage_ptr = new double[capacity / 2];
		for (int i = 0; i < real_size; i++) {
			temp_storage_ptr[i] = this->data_ptr[i];
		}

		this->capacity /= 2;
		delete[] this->data_ptr;
		this->data_ptr = temp_storage_ptr;
	}
}

void Vector::pop_back() {
	if (real_size == 0) throw "The absence of the last element of the empty Vector!";

	real_size--;
	storage_decrease();
}

double Vector::back() const {
	if (real_size == 0) throw "The absence of the last element of the empty Vector!";

	return data_ptr[real_size - 1];
}

double& Vector::operator[](int i) {
	if (i >= real_size) throw "The Vector index out of range!";

	return data_ptr[i];
}

double Vector::operator[](int i) const {
	if (i >= real_size) throw "The Vector index out of range!";
	return data_ptr[i];
}

void Vector::swap(Vector& V1, Vector& V2) {
	std::swap(V1.data_ptr, V2.data_ptr);
	std::swap(V1.capacity, V2.capacity);
	std::swap(V1.real_size, V2.real_size);
}