#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions11A
{

	struct Node
	{
		int positionX;
		int positionY;

		bool operator==(Node node) const
		{
			return (positionX == node.positionX and positionY == node.positionY);
		}

		bool operator!=(Node node) const
		{
			return !(positionX == node.positionY and positionY == node.positionY);
		}

		bool operator<(Node node) const
		{
			return std::tie(positionX, positionY) < std::tie(node.positionX, node.positionY);
		}
	};

	void print_grid(std::vector<std::string> &grid)
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

	std::vector<std::string> expand_grid(std::vector<std::string> &grid)
	{
		int row = 0;
		std::vector<std::string> temp = grid;
		for (const auto &line : grid)
		{
			bool isEmpty = true;
			for (const auto &character : line)
			{
				if (character != '.')
				{
					isEmpty = false;
					break;
				}
			}
			if (isEmpty)
			{
				temp.insert(temp.begin() + row, line);
				row++;
			}
			row++;
		}

		int columnIndex = 0;
		int tempIndex = 0;
		while (columnIndex < (int)grid[0].size())
		{
			bool isEmpty = true;
			for (const auto &line : grid)
			{
				if (line[columnIndex] != '.')
				{
					isEmpty = false;
					break;
				}
			}
			if (isEmpty)
			{
				for (auto &line : temp)
				{
					line.insert(line.begin() + tempIndex, '.');
				}
				tempIndex++;
			}
			tempIndex++;
			columnIndex++;
		}

		return temp;
	}

	std::set<std::pair<Node, Node>> get_routes(std::vector<std::string> &grid)
	{
		int row = 0;
		int column = 0;
		std::set<Node> locations;
		for (const auto &line : grid)
		{
			for (const auto &character : line)
			{
				if (character == '#')
				{
					Node node{column, row};
					locations.emplace(node);
				}
				column++;
			}
			row++;
			column = 0;
		}

		std::set<std::pair<Node, Node>> routes;
		for (const auto &node : locations)
		{
			for (const auto &nodeTwo : locations)
			{
				if (node == nodeTwo)
				{
					continue;
				}

				if (routes.contains(std::make_pair(node, nodeTwo)) or
					routes.contains(std::make_pair(nodeTwo, node)))
				{
					continue;
				}

				auto route = std::make_pair(node, nodeTwo);
				routes.emplace(route);
			}
		}
		return routes;
	}

	int manahanttan_distance_sum(std::set<std::pair<Node, Node>> &set)
	{
		int result = 0;
		for (auto &route : set)
		{
			auto distance = std::abs(route.first.positionX - route.second.positionX) +
							std::abs(route.first.positionY - route.second.positionY);
			result += distance;
		}
		return result;
	}

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto input = Utilities::file_into_string_vector(inputFile);			// GET INPUT
		auto grid = expand_grid(input);										// EXPAND GRID
		auto set = get_routes(grid);										// GET PAIRS
		auto result = manahanttan_distance_sum(set);						// CALCULATE DISTANCE
		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl; // PRINT
	}
} // namespace Solutions11A
