#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle08A
{

	struct Node
	{
		std::string name;
		std::string left;
		std::string right;
	};

	const std::string START = "AAA";
	const std::string END = "ZZZ";

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadAllLinesInFile(inputFile);
		std::vector<Node> nodes;
		std::string intructions = input[0];
		input.erase(input.begin(), input.begin() + 2);
		for (auto& line : input)
		{
			Node node;
			std::string token;

			token = line.substr(0, line.find(" "));
			line.erase(0, line.find("(") + 1);
			node.name = token;

			token = line.substr(0, line.find(","));
			line.erase(0, line.find(" ") + 1);
			node.left = token;

			token = line.substr(0, line.find(")"));
			node.right = token;

			nodes.push_back(node);
		}

		Node node;
		for (const auto& searchNode : nodes)
		{
			if (searchNode.name == START)
			{
				node = searchNode;
				break;
			}
		}

		int result = 0;
		while (true)
		{
			for (const auto& instruction : intructions)
			{

				if (node.name == END)
				{
					std::cout << "\t\t" << GREEN_TEXT << result << RESET_COLOR;
					return;
				}

				if (instruction == 'L')
				{
					for (const auto& searchNode : nodes)
					{
						if (node.left == searchNode.name)
						{
							node = searchNode;
							result++;
							break;
						}
					}
				}

				if (instruction == 'R')
				{
					for (const auto& searchNode : nodes)
					{
						if (node.right == searchNode.name)
						{
							node = searchNode;
							result++;
							break;
						}
					}
				}
			}
		}
	}
} // namespace Puzzle08A