#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle01A
{
	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		int result = 0;
		std::vector<int> calibrationValues;

		for (const std::string& line : ReadAllLinesInFile(inputFile))
		{
			std::vector<char> digitVector;
			for (const char character : line)
			{
				if (isdigit(character))
				{
					digitVector.push_back(character);
				}
			}

			char firstNumber = digitVector[0];
			char lastNumber = digitVector[digitVector.size() - 1];
			digitVector = {};

			std::string value;
			value += firstNumber;
			value += lastNumber;

			calibrationValues.push_back(stoi(value));
		}

		for (int i : calibrationValues)
		{
			result += i;
		}

		std::cout << "\n\t\t" << result << std::endl;
	}
} // namespace Puzzle01A