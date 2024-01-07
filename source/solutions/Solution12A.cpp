#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions12A
{
	void PrintSolution(const std::filesystem::path &inputFile)
	{
		std::string line;
		std::ifstream file(inputFile);
		while (getline(file, line))
		{
			std::string row;
			std::string token;
			std::vector<int> locations;
		}

		int result = 0;
		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl;
	}
} // namespace Solutions12A
