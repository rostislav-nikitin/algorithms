using namespace std;

template<typename T>
void Matrix<T>::copy(const Matrix<T> &m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	if(&m == this)
		return;

	if(data != nullptr)
	{
		cout << "data != nullptr: " << *data << endl;
		this->~Matrix();
	}

	rows = m.rows;
	cols = m.cols;
	data = new T*[rows];
	for(int i = 0; i < rows; ++i)
	{
		data[i] = new T[cols];
		for(int j = 0; j < cols; ++j)
		{
			data[i][j] = m.data[i][j];
		}
	}
}

template<typename T>
void Matrix<T>::move(Matrix<T> &&m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	if(&m == this)
		return;

	if(data != nullptr)
		this->~Matrix();
	rows = m.rows;
	cols = m.cols;
	data = m.data;

	m.data = nullptr;
	m.rows = 0;
	m.cols = 0;
}



template<typename T>
Matrix<T>::Matrix(const int rows, const int cols) : rows {rows}, cols {cols}
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	data = new T*[rows];
	for(int i = 0; i < rows; ++i)
	{
		data[i] = new T[cols];
		for(int j = 0; j < cols; ++j)
			data[i][j] = T{};
	}
}

template<typename T>
Matrix<T>::Matrix(vector<vector<T>> init)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	rows = init.size();
	cols = init[0].size();

	data = new T*[rows];
	for(int i = 0; i < rows; ++i)
	{
		data[i] = new T[cols];
		for(int j = 0; j < cols; ++j)
		{
			data[i][j] = init[i][j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	copy(m);
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	move(std::move(m));
}
/*
template<typename T>
Matrix<T>::Matrix(const Matrix<T> *m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	copy(m);
}
*/

template<typename T>
int Matrix<T>::get_rows() const
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	return rows;
}

template<typename T>
int Matrix<T>::get_cols() const
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	return cols;
}

template<typename T>
T* Matrix<T>::operator [] (int row)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	return data[row];
}

template<typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix<T> &m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	copy(m);
	return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator = (Matrix<T> &&m)
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	move(std::move(m));
	return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	for(int i = 0; i < rows; ++i)
		delete[] data[i];

	delete[] data;
}

template<typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T> &m) const
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	//cout << rows << ":" << m.cols << endl;
	Matrix<T> res{rows, m.cols};

	for(int i = 0; i < res.rows; ++i)
	{
		for(int j = 0; j < res.cols; ++j)
		{
			for(int k = 0; k < cols; ++k)
			{
				res.data[i][j] += data[i][k] * m.data[k][j];
			}
		}
	}

	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator ^ (int n) const
{
	#ifdef DEBUG
		cout << __PRETTY_FUNCTION__<< endl;
	#endif
	Matrix<T> res {MATRIX_ONE_2x2};
	int k = n;
	Matrix<T> c {*const_cast<Matrix<T>*>(this)};

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
