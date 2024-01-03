#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions03B
{

	struct PartNumber
	{
		int startIndex;
		int endIndex;
		int value;
		int rowNumber;

		PartNumber(int start, int row)
		{
			startIndex = start;
			endIndex = start;
			rowNumber = row;
			value = 0;
		}
	};

	struct SymbolPosition
	{
		int col;
		int row;

		SymbolPosition(int c, int r)
		{
			col = c;
			row = r;
		}
	};

	bool adjacent(const PartNumber *part, const SymbolPosition *symbol)
	{
		return symbol->col >= part->startIndex - 1 and symbol->col <= part->endIndex + 1;
	}

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto input = Utilities::file_into_string_vector(inputFile);

		std::vector<PartNumber *> partNumbers;
		std::vector<SymbolPosition *> symbolPositions;

		int row = 0;
		int sum = 0;

		for (const auto &line : input)
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (isdigit(line.at(i)))
				{
					partNumbers.push_back(new PartNumber(i, row));

					while (isdigit(line.at(i)))
					{
						partNumbers.back()->endIndex = i;
						partNumbers.back()->value = (10 * partNumbers.back()->value) + line.at(i) - '0';

						i++;
						if (i >= line.length())
						{
							break;
						}
					}

					if (i >= line.length())
					{
						break;
					}
				}

				if (line.at(i) == '*')
				{
					symbolPositions.push_back(new SymbolPosition(i, row));
				}
			}

			row++;
		}

		int count;
		std::vector<int> gear;
		for (SymbolPosition *symbol : symbolPositions)
		{
			count = 0;
			for (PartNumber *part : partNumbers)
			{
				if (symbol->row < part->rowNumber - 1)
				{
					break;
				}
				if (symbol->row > part->rowNumber + 1)
				{
					continue;
				}

				if (adjacent(part, symbol))
				{
					count++;
					gear.push_back(part->value);
				}
			}
			if (count == 2)
			{
				sum += gear.at(0) * gear.at(1);
			}
			gear.clear();
		}

		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << sum << std::endl;
	}
} // namespace Solutions03B
