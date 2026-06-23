#pragma once

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class Matrix {
private:
	int rows;
	int columns;
	E** matrix;

public:
	Matrix(int rows, int columns) {
		if (rows <= 0 || columns <= 0) 
			throw runtime_error("ERROR: Number of rows and cols must be greater than zero");
		this->rows = rows;
		this->columns = columns;
		this->matrix = new E*[rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new E[columns];
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	E getValue(int row, int column) {
		if (row < 0 || row >= rows)
			throw runtime_error("ERROR: Invalid row.");
		if (column < 0 || column >= columns)
			throw runtime_error("ERROR: Invalid column.");
		return matrix[row][column];
	}
	void setValue(int row, int column, E value) {
		if (row < 0 || row >= rows)
			throw runtime_error("ERROR: Invalid row.");
		if (column < 0 || column >= columns)
			throw runtime_error("ERROR: Invalid column.");
		matrix[row][column] = value;
	}
	int getRows() const {
		return rows;
	}
	int getColumns() const {
		return columns;
	}
	void setAll(E value) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = value;
			}
		}
	}
	void transpose() {
		E** trans = new E*[columns];
		for (int i = 0; i < columns; i++) {
			trans[i] = new E[rows];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				trans[j][i] = matrix[i][j];
			}
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = trans;
		int temp = rows;
		rows = columns;
		columns = temp;
	}

	void addRow(E value) {
		E** newMatrix = new E*[rows + 1];
		for (int r = 0; r < rows; r++)
			newMatrix[r] = matrix[r];
		newMatrix[rows] = new E[columns];
		for (int c = 0; c < columns; c++)
			newMatrix[rows][c] = value;
		delete[] matrix;
		matrix = newMatrix;
		rows++;
	}

	void addColumn(E value) {
		for (int i = 0; i < rows; i++) {
			E* nuevaFila = new E[columns + 1];
			for (int j = 0; j < columns; j++)
				nuevaFila[j] = matrix[i][j];
			nuevaFila[columns] = value;
			delete[] matrix[i];
			matrix[i] = nuevaFila;
		}
		columns++;
	}

	void removeRow(int row) {
		if (row < 0 || row >= rows)
			throw runtime_error("Invalid row.");
		E** newMatrix = new E * [rows - 1];
		for (int r = 0; r < row; r++)
			newMatrix[r] = matrix[r];
		for (int r = row + 1; r < rows; r++)
			newMatrix[r - 1] = matrix[r];
		delete[] matrix[row];
		delete[] matrix;
		matrix = newMatrix;
		rows--;
	}
	void removeColumn(int column) {
		if (column < 0 || column >= columns)
			throw runtime_error("ERROR: Invalid column.");
		for (int i = 0; i < rows; i++) {
			E* newRow = new E[columns - 1];
			for (int j = 0; j < column; j++)
				newRow[j] = matrix[i][j];
			for (int j = column + 1; j < columns; j++)
				newRow[j - 1] = matrix[i][j];
			delete[] matrix[i];
			matrix[i] = newRow;
		}
		columns--;
	}
	void print() {
		for (int i = 0; i < rows; i++) {
			cout << "[ "; 
			for (int j = 0; j < columns; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << "]" << endl;
		}
	}
};

