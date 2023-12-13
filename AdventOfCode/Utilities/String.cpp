#include "pch.h"

#include "String.h"

namespace Utilities
{

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

	static std::vector<std::string> split_string_by_delimiter(std::string s, const std::string& delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		size_t pos = 0;
		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			tokens.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		tokens.push_back(s);
		return tokens;
	}
} // namespace Utilities
