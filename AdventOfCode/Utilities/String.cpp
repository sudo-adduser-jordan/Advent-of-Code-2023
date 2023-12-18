#include "pch.h"

#include "String.h"

namespace Utilities
{

	std::vector<int> string_to_int_vector(const std::string& str)
	{
		int number;
		std::vector<int> ints;
		std::stringstream iss(str);
		while (iss >> number)
		{
			ints.push_back(number);
		}
		return ints;
	}

	std::vector<unsigned long long int> string_to_long_long_vector(const std::string& str)
	{
		std::vector<unsigned long long int> ints;

		unsigned long long int number;
		std::stringstream iss(str);
		while (iss >> number)
		{
			ints.push_back(number);
		}

		return ints;
	}

	bool isFound(const std::string& match, const std::string& str)
	{
		if (str.find(match) < str.length())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

} // namespace Utilities
