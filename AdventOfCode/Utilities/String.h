#pragma once
#include "pch.h"

namespace Utilities
{
	/**
	 *  @brief  Parse a string of long long ints into vector.
	 *  @param  str String of long long ints.
	 *  @return Copy of string.
	 *
	 *  Creates an isstream to read string of ints and pushback to fill vector.
	 **/
	std::vector<unsigned long long int> string_to_long_long_vector(const std::string& str);

	/**
	 *  @brief  Find a string in another string.
	 *  @param  match String to match.
	 *  @param  str String to search.
	 *  @return Boolean.
	 *
	 *  Uses string::find() and string::length() to search string and return a boolean value.
	 **/
	bool isFound(const std::string& match, const std::string& str);

	// todo
	static std::vector<std::string> split_string_by_delimiter(std::string s, const std::string& delimiter);

} // namespace Utilities