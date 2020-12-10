#include <iostream>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<string> Strings;

template<typename T>
	using PowerArgs = pair<T, int>;

template<typename T>
	T power(T a, int n);

template<typename T>
	fplus::result<T, string> get_power(PowerArgs<T> args);

template<typename T>
	result<T, string> parse(string value);
	 
template<typename T>
	fplus::result<PowerArgs<T>, string> get_power_args(Strings input);

template<typename T>
	fplus::result<T, string> get_power(PowerArgs<T> args)
	{
		T a = args.first;
		int n = args.second;

		T res = power<T>(a, n);


		return fplus::ok<T, string>(res);
	};

template<typename T>
	result<T, string> parse(string value)
	{
		T res;
		istringstream {value} >> res;

		return ok<T, string>(res);
	}
	 
template<typename T>
	fplus::result<PowerArgs<T>, string> get_power_args(Strings input)
	{
		if(input.size() < 3)
			return fplus::error<PowerArgs<T>, string>(string {"Invalid arguments.\n\tUse: power {a} {n}."});
		auto a_result = parse<T>(input[1]);
		if(a_result.is_error())
			return fplus::error<PowerArgs<T>, string>(string{"Invalid {a}. Should be a number."});
		T a = a_result.unsafe_get_ok();

		auto n_result = parse<int>(input[2]);
		if(n_result.is_error())
			return fplus::error<PowerArgs<T>, string>(string{"Invalid {n}. Should be a number."});
		int n = n_result.unsafe_get_ok();

		return fplus::ok<PowerArgs<T>, string>(PowerArgs<T>{a, n});
			
	}
