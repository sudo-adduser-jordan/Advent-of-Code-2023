#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle09A
{
	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadAllLinesInFile(inputFile);
		auto grid = file_into_int_grid(inputFile);

		std::vector<int> predictions;
		std::vector<std::vector<int>> predictionGrid;
		for (const auto& line : grid)
		{
			predictionGrid.push_back(line);
			while (true)
			{
				std::vector<int> temp;
				auto& container = predictionGrid.back();
				for (auto index = 0; index < container.size() - 1; index++)
				{
					temp.push_back(container[index + 1] - container[index]);
				}
				predictionGrid.push_back(temp);

				if (std::ranges::all_of(temp, [&](int i) { return i == 0; }))
				{
					break;
				}
			}

			int prediction = 0;
			for (auto& line : predictionGrid | std::views::reverse)
			{
				prediction += line.back();
			}
			predictions.push_back(prediction);
			predictionGrid.clear();
		}

		int result = 0;
		for (const auto& prediction : predictions)
		{
			result += prediction;
		}
		std::cout << GREEN_TEXT << result << RESET_COLOR << std::endl;
	}
} // namespace Puzzle09A