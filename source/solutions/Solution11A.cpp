#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions11A
{

	void print_grid(std::vector<std::string> grid)
	{
		for (const auto &line : grid)
		{
			for (const auto &character : line)
			{
				std::cout << character;
			}
			std::cout << std::endl;
		}
	}

	std::vector<std::string> expand_grid(std::vector<std::string> grid)
	{
		return grid;
	}

	std::set<std::pair<int, int>> get_pairs(std::vector<std::string> grid)
	{
		return {};
	}

	int manahanttan_distance(std::set<std::pair<int, int>> set)
	{
		return 0;
	}

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto input = Utilities::file_into_string_vector(inputFile); // GET INPUT
		auto grid = expand_grid(input);
		print_grid(grid);

		// EXPAND GRID
		auto set = get_pairs(grid);											// GET PAIRS
		auto result = manahanttan_distance(set);							// CALCULATE DISTANCE
		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl; // PRINT
	}
} // namespace Solutions11A
