#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle06A
{
	struct Race
	{
		int time = 0;
		int record = 0;
		int wins = 0;
	};

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		int result = 1;

		// Sample input.
		// std::array<Race, 3> races = {};
		// races[0] = { 7, 9 };
		// races[1] = { 15, 40 };
		// races[2] = { 30, 200 };

		std::array<Race, 4> races = {};
		races[0] = { 48, 296 };
		races[1] = { 93, 1928 };
		races[2] = { 85, 1236 };
		races[3] = { 95, 1391 };

		for (auto& race : races)
		{
			for (int index = 0; index <= race.time; index++)
			{
				if (race.record < ((race.time - index) * index))
				{
					race.wins++;
				}
			}
			result *= race.wins;
		}

		std::cout << "\t\t" << GREEN_TEXT << result << RESET_COLOR;
	}
} // namespace Puzzle06A