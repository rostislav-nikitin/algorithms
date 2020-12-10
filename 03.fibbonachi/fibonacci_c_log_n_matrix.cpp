//#define DEBUG

#include <iostream>
#include <sstream>
#include "../matrix.h"

using namespace std;

template<typename T>
	T parse(string str)
	{
		T result;
		istringstream {str} >> result;

		return result;
	}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout << "Invalid arguments.\n\tUsage: fibonacci {n}" << endl;
		return 0;
	}

	int n = parse<int>(string{argv[1]});

	auto mtx = MATRIX_FIBONACCI ^ n;

	cout << n << " -> (" << mtx[1][0] << ", " << mtx[1][1] << ")" << endl;

	return 0;
}
