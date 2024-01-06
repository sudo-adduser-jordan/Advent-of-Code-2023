#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions11B
{

	struct Node
	{
		long long int positionX;
		long long int positionY;

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

	Node get_location(long long int column, long long int row, std::vector<long long int> xValues, std::vector<long long int> yValues)
	{
		Node node;
		long long counter = 0;
		for (const auto &value : xValues)
		{
			if (column < value)
			{
				break;
			}
			else
			{
				counter++;
			}
		}
		node.positionX = ((counter * 1000000) - counter) + column;

		counter = 0;
		for (const auto &value : yValues)
		{
			if (row < value)
			{
				break;
			}
			else
			{
				counter++;
			}
		}

		node.positionY = ((counter * 1000000) - counter) + row;
		return node;
	}

	std::set<std::pair<Node, Node>> get_routes(std::vector<std::string> &grid)
	{
		long long int row = 0;
		long long int column = 0;
		std::vector<long long int> xValues;
		std::vector<long long int> yValues;

		for (const auto &line : grid)
		{
			bool isEmpty = true;
			for (const auto &character : line)
			{
				if (character == '#')
				{
					isEmpty = false;
					break;
				}
				column++;
			}
			if (isEmpty)
			{
				yValues.push_back(row);
			}
			row++;
			column = 0;
		}

		row = 0;
		column = 0;
		while (column < (long long int)grid[0].size())
		{
			bool isEmpty = true;
			for (const auto &line : grid)
			{
				if (line[column] == '#')
				{
					isEmpty = false;
					break;
				}
			}
			if (isEmpty)
			{
				xValues.push_back(column);
			}
			column++;
		}

		row = 0;
		column = 0;
		std::set<Node> locations;
		for (const auto &line : grid)
		{
			for (const auto &character : line)
			{
				if (character == '#')
				{
					Node node = get_location(column, row, xValues, yValues);
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

	long long int manahanttan_distance_sum(std::set<std::pair<Node, Node>> &set)
	{
		long long int result = 0;
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
		auto set = get_routes(input);										// GET PAIRS
		auto result = manahanttan_distance_sum(set);						// CALCULATE DISTANCE
		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl; // PRINT
	}
} // namespace Solutions11B
