// Single-line comment
/*
 * Multiple line comment
 */

#include "../common.h"

#define DEBUG

using namespace std;

template<typename T, int size>
	using Col = T[size];

template<typename T, int rows, int cols>
	using Row = Col<T, cols>[rows];

template<typename T, int rows, int cols>
	using Matrixx = Row<T, rows, cols>;

template<typename T> 
	using Matrix = vector<vector<T>>;


const Matrix<double> MATRIX_FIBONACCI { {1, 1}, {1, 0} };
const Matrix<double> MATRIX_ONE_2x2 { {1, 0}, {0, 1} };
const Matrix<double> MATRIX_EMPTY { };

template<typename T>
	Matrix<T> operator * (const Matrix<T> &m1, const Matrix<T> &m2)
	{
		Matrix<T> res{m1.size()};

		for(int i = 0; i < m1.size(); ++i)
		{
			res[i] = std::move(vector<T>(m2[0].size()));

			for(int j = 0; j < m2[0].size(); ++j)
			{
				for(int k = 0; k < m1[0].size(); ++k)
				{
					res[i][j] += m1[i][k] * m2[k][j];
				}
			}
		}

		return res;
	}

template<typename T>
	Matrix<T> operator ^ (const Matrix<T> &m, int n)
	{
		Matrix<T> res {MATRIX_ONE_2x2};
		int k = n;
		Matrix<T> c = m;

		while(k != 0)
		{
			if(k % 2 == 0)
			{
				c = c * c;
				k /= 2;
			}
			else
			{
				res = res * c;
				k--;
			}
		}

		return res;
	}

template<typename T>
	ostream & operator << (ostream &out, const Matrix<T> &m)
	{
		for(int i = 0; i < m.size(); ++i)
		{
			for(int j = 0; j < m[0].size(); ++j)
				out << m[i][j] << " ";
			cout << endl;
		}

		return out;
	}


int main(int argc, char *argv[])
{
	Strings args {argv, argv + argc};
	auto int_args_result = get_args<int, 1>(args);

	if(int_args_result.is_error())
	{
		cout << int_args_result.unsafe_get_error() << endl;
		return 0;
	}

	long n = int_args_result.unsafe_get_ok()[0];

	auto res = MATRIX_FIBONACCI ^ n;

	cout << res << endl;

	cout << n << " -> (" << res[1][0] << ", " << res[1][1] << ")" << endl;

	return 0;
}
