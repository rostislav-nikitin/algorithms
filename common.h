#include <iostream>
#include <vector>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

typedef vector<string> Strings;

template<typename T>
	result<T, string> parse(string value);
	 
template<typename T>
	result<T, string> parse(string value)
	{
		T res;
		istringstream {value} >> res;

		return ok<T, string>(res);
	}

Strings slice_first(const Strings &input)
{
	// Remove fiest element
	Strings res {};
	res.reserve(input.size() - 1);
	auto itr_begin = begin(input) + 1;
	while(itr_begin != end(input))
		res.push_back(*itr_begin++);

	return res;
}
	 
template<typename T, int count>
	fplus::result<vector<T>, string> get_args(const Strings &input)
	{
		if(count !=0 && input.size() < (count + 1))
			return fplus::error<vector<T>, string>(string {"Invalid arguments.\n\tUse: cmd a1[,...an]"});

		auto res_result = fwd::apply
		(
			input,
			slice_first,
		 	fwd::transform(parse<T>)
		);

		if(!fplus::all_by(fplus::is_ok<T, string>, res_result))
			return fplus::error<vector<T>, string>(string{"Some values can not be parsed"});
		vector<T> res = fwd::apply
		(
		 	res_result,
			fwd::transform([](auto arg)
				{
					return arg.unsafe_get_ok();
				})
		);

		return fplus::ok<vector<T>, string>(res);
	}
