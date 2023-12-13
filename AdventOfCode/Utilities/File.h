#pragma once
#include "pch.h"

namespace Utilities
{
	/**
	 *  @brief  Read a text file into a string vector.
	 *  @param  file Path to file.
	 *  @return Copy of vector.
	 *
	 *  Creates an ifstream to read file line by line and push_back to fill vector.
	 **/
	std::vector<std::string> file_into_string_vector(const std::string& filename);

} // namespace Utilities