// Single-line comment
/*
 * Multiple line comment
*/

#include "common.h"

template<typename T>
	T power(T a, int n)
	{

		T res = 1;
		int k = n;
		T c = a;
		while(k != 0)
		{
			if(k % 2 == 0)
			{
				c *= c;
				k = k / 2;
			}
			else
			{
				k--;
				res *= c;

			}
		}

		return res;
	}

int main(int argc, char *argv[])
{
	Strings args = Strings{argv, argv + argc};

	auto res = fwd::apply
		(
		 	args,
			fplus::compose_result(
				get_power_args<double>,
				get_power<double>)
		);

	if(res.is_error())
		cout << res.unsafe_get_error() << endl;
	else
		cout << res.unsafe_get_ok() << endl;

	return 0;
}
