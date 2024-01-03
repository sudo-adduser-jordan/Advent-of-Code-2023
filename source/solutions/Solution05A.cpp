#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions05A
{
	using ulint = unsigned long long int;

	struct Range
	{
		ulint destRangeStart;
		ulint sourceRangeStart;
		ulint RangeLen;
	};

	struct SeedRange
	{
		ulint start;
		ulint end;
	};
	bool isFound(const std::string &match, const std::string &str)
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

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		// Initialize variables.
		ulint result = 0;																						   // End result.
		auto input = Utilities::file_into_string_vector(inputFile);												   // File input.
		std::vector<ulint> seeds = Utilities::string_to_long_long_vector(input[0].substr(input[0].find(':') + 1)); // List of seeds.
		std::list<std::vector<Range>> listOfMaps;																   // List of Maps

		std::vector<Range> map;
		for (std::string line : input)
		{
			if (line.length() == 0)
			{
				continue;
			}

			if (isFound("map", line))
			{
				if (!map.empty())
				{
					listOfMaps.push_back(map);
				}
				map.clear();
				continue;
			}

			if (isdigit(line.at(0)))
			{
				std::vector<ulint> numbers = Utilities::string_to_long_long_vector(line);

				Range range = {0, 0, 0};
				range.destRangeStart = numbers[0];
				range.sourceRangeStart = numbers[1];
				range.RangeLen = numbers[2];

				map.push_back(range);
			}
		}
		listOfMaps.push_back(map);

		// Process Data.
		for (ulint &seed : seeds) // for each seed
		{
			for (std::vector<Range> map : listOfMaps) // for each map
			{
				for (Range range : map) // for each range in map
				{
					if (range.sourceRangeStart <= seed && seed <= range.RangeLen + range.sourceRangeStart) // if seed in destination range
					{
						seed = range.destRangeStart + (seed - range.sourceRangeStart); // convert seed to destination
						break;
					}
				}
			}
		}

		result = seeds[0]; // return smallest value in array
		for (ulint seed : seeds)
		{
			if (result > seed)
			{
				result = seed;
			}
		}

		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl;
	}
} // namespace Solutions05A
