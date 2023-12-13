#include "pch.h"

#include "File.h"

namespace Utilities
{

	std::vector<std::string> file_into_string_vector(const std::string& filename)
	{
		std::vector<std::string> lines;

		std::string line;
		std::ifstream file(filename);
		while (getline(file, line))
		{
			lines.push_back(line);
		}

		return lines;
	}

} // namespace Utilities
