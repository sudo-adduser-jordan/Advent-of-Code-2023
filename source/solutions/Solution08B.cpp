#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions08B
{
	struct Node
	{
		std::string name;
		std::string left;
		std::string right;
	};

	const std::string START = "AAA";
	const std::string END = "ZZZ";
	typedef long long int llint;

	static llint GCD(llint a, llint b)
	{
		if (b == 0)
		{
			return a;
		}
		return GCD(b, a % b);
	}

	static llint LCM(std::vector<llint> vector, llint size)
	{
		llint ans = vector[0];
		for (llint i = 1; i < size; i++)
		{
			ans = (((vector[i] * ans)) / (GCD(vector[i], ans)));
		}
		return ans;
	}

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto input = Utilities::file_into_string_vector(inputFile);
		std::vector<Node> nodes;
		std::vector<Node> startNodes;
		std::string intructions = input[0];
		input.erase(input.begin(), input.begin() + 2);
		for (auto &line : input)
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
			if (node.name[2] == 'A')
			{
				startNodes.push_back(node);
			}
		}

		std::vector<llint> results;
		for (auto &startingNode : startNodes)
		{
			llint result = 0;
			bool isFound = false;
			while (!isFound)
			{
				for (const auto &instruction : intructions)
				{
					result++;
					if (instruction == 'L')
					{
						auto cmp = [startingNode](Node node)
						{ return startingNode.left == node.name; };
						auto it = std::find_if(nodes.begin(), nodes.end(), cmp);
						if (it != nodes.end())
						{
							startingNode = *it;
						}

						if (startingNode.name[2] == 'Z')
						{
							results.push_back(result);
							isFound = true;
						}
					}

					if (instruction == 'R')
					{
						auto cmp = [startingNode](Node node)
						{ return startingNode.right == node.name; };
						auto it = std::find_if(nodes.begin(), nodes.end(), cmp);
						if (it != nodes.end())
						{
							startingNode = *it;
						}

						if (startingNode.name[2] == 'Z')
						{
							results.push_back(result);
							isFound = true;
						}
					}
				}
			}
		}

		std::cout << "\t\t" << GREEN_TEXT << LCM(results, results.size()) << RESET_COLOR;
	}
} // namespace Solutions08B
