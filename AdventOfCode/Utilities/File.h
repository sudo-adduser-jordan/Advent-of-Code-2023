#pragma once
#include "pch.h"

namespace Utilities
{
	/**
	 *  @brief  Read a text file into a 2d vector of ints.
	 *  @param  file path to file.
	 *  @return Copy of vector.
	 *
	 *  Creates an ifstream to read file line by line and push_back to fill vector. 
	 *  Uses string_to_int() to create vectors.
	 **/
	std::vector<std::vector<int>> file_into_int_grid(const std::filesystem::path& path);

	/**
	 *  @brief  Read a text file into a string vector.
	 *  @param  file path to file.
	 *  @return Copy of vector.
	 *
	 *  Creates an ifstream to read file line by line and push_back to fill vector.
	 **/
	std::vector<std::string> file_into_string_vector(const std::filesystem::path& path);

} // namespace Utilities