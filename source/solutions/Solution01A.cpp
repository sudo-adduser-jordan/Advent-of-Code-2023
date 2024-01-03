#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions01A
{
	void PrintSolution(const std::filesystem::path &inputFile)
	{
		int result = 0;
		std::vector<int> calibrationValues;
		for (const std::string &line : Utilities::file_into_string_vector(inputFile))
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

		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl;
	}
} // namespace Solutions01A
