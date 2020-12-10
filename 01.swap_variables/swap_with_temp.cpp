// Single-line comment
/*
 * Multiple line comment
 */

#include "../common.h"
template<typename T>
	void swap_elements(T &x, T &y)
	{
		T temp = x;
		x = y;
		y = temp;
	}

int main(int argc, char *argv[])
{
	Strings args {argv, argv + argc};
	auto int_args_result = get_args<char, 2>(args);

	if(int_args_result.is_error())
	{
		cout << int_args_result.unsafe_get_error() << endl;
		return 0;
	}
	
	auto int_args = int_args_result.unsafe_get_ok();

	char x = int_args.at(0);
	char y = int_args.at(1);

	cout << "[original]\tx=" << x << "; y=" << y << endl;

	swap_elements(x, y);

	cout << "[swaped]\tx=" << x << "; y=" << y << endl;

	return 0;
}
