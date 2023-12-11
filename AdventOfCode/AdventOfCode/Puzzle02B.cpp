#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

struct Set
{
	int red;
	int green;
	int blue;
};

struct Game
{
	int game;
	std::vector<Set> sets;
};

struct Results
{
	std::vector<Game> results;
};

const Set loadout = { 12, 13, 14 };

namespace Puzzle02B
{

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadAllLinesInFile(inputFile);

		Results results;

		for (const auto line : input)
		{
			Set set;
			set.red = 0;
			set.blue = 0;
			set.green = 0;

			Game game;
			game.game = stoi(line.substr(line.find(" "), line.find(":")));

			std::string str = line.substr(line.find(": ") + 2, line.length()) + ";";
			while (str.find("red") != std::string::npos)
			{
				str.replace(str.find("red"), sizeof("red") - 1, "r");
			}
			while (str.find("green") != std::string::npos)
			{
				str.replace(str.find("green"), sizeof("green") - 1, "g");
			}
			while (str.find("blue") != std::string::npos)
			{
				str.replace(str.find("blue"), sizeof("blue") - 1, "b");
			}

			int num;
			std::string value;
			for (char character : str)
			{
				if (isdigit(character))
				{
					value += character;
					num = stoi(value);
				}

				switch (character)
				{
					case ';':
						game.sets.push_back(set);
						set.red = 0;
						set.blue = 0;
						set.green = 0;
						value = "";
						num = 0;
						break;
					case 'r':
						set.red = num;
						value = "";
						num = 0;
						break;
					case 'g':
						set.green = num;
						value = "";
						num = 0;
						break;
					case 'b':
						set.blue = num;
						value = "";
						num = 0;
						break;
					default:
						break;
				}
			}
			results.results.push_back(game);
		}

		std::vector<int> powers;
		for (Game game : results.results)
		{
			int red = 0;
			int green = 0;
			int blue = 0;

			for (Set set : game.sets)
			{
				if (red < set.red)
				{
					red = set.red;
				}
				if (green < set.green)
				{
					green = set.green;
				}
				if (blue < set.blue)
				{
					blue = set.blue;
				}
			}

			int power = red * green * blue;
			powers.push_back(power);
		}

		int sum = 0;
		for (int n : powers)
		{
			sum += n;
		}

		std::cout << "\t\t" << GREEN_TEXT << sum << RESET_COLOR;
	}
} // namespace Puzzle02B