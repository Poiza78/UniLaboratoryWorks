﻿#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int size;
	Cell** cells;
	void AllocateCells(int);
	void FreeCells();
public:
	Matrix() : size(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int);							// Конструктор нулевой матрицы
	Matrix(int, Cell*);						// Конструктор матрицы из списка
	~Matrix();								// Деструктор

	Cell& operator()(int i, int j) { return cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int Size)
{
	AllocateCells(Size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int Size, Cell* list)
{
	AllocateCells(Size);
	for (int i = 0; i < Size; ++i)
		memcpy(cells[i], &list[i * Size], Size * sizeof(Cell));
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if (size != M.size)
	{
		FreeCells();
		AllocateCells(M.size);
	}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (size == M.size)
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (size == M.size)
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	int minSize = min(this->size, M.size); // по условию все матрицы квадратные!!11!

	Matrix<Cell> res(minSize);
	//Cell list[minSize * minSize];
	//memset(list, 0, minSize * minSize * sizeof Cell);
	
	for (int i = 0; i < minSize; ++i)
		for (int j = 0; j < minSize; ++j)
			for (int k = 0; k < minSize; ++k)
				res.cells[i][j] += this->cells[i][k] * M.cells[k][j];

	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Size)
{
	cells = new Cell * [Size];
	for (int i = 0; i < Size; i++)
		cells[i] = new Cell[Size];
	size = Size;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < size; i++)
		delete cells[i];
	delete cells;
	size = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.size; i++)
		for (int j = 0; j < M.size; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.size; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.size; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H