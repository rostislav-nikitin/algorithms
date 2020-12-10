#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix
{
	private:
		int rows;
		int cols;
		T **data {};
		void copy(const Matrix<T> &m);
		void move(Matrix<T> &&m);
	public:
		Matrix(const int rows, const int cols);
		Matrix(vector<vector<T>> init);
		Matrix(const Matrix<T> &m);
		Matrix(Matrix<T> &&m);
		//Matrix(const Matrix<T> *m);

		int get_rows() const;
		int get_cols() const;

		T* operator [] (int row);
		Matrix<T> & operator = (const Matrix<T> &m);
		Matrix<T> & operator = (Matrix<T> &&m);
		Matrix<T> operator * (const Matrix<T> &m) const;
		Matrix<T> operator ^ (int n) const;
		friend ostream & operator << (ostream &out, const Matrix<T> &m)
		{
			#ifdef DEBUG
				cout << __PRETTY_FUNCTION__<< endl;
			#endif
			for(int i = 0; i < m.rows; ++i)
			{
				for(int j = 0; j < m.cols; ++j)
					out << m.data[i][j] << " ";

				cout << endl;
			}

			return out;
		}
		~Matrix();
};

const Matrix<double> MATRIX_FIBONACCI 	({ {1, 1}, {1, 0} });
const Matrix<double> MATRIX_ONE_2x2 	({ {1, 0}, {0, 1} });
const Matrix<double> MATRIX_EMPTY_1x1 	{0, 0};

#include "matrix.tpp"

#endif
