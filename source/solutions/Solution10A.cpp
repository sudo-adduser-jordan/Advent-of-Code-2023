#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions10A
{
	struct Point
	{
		int row;
		int column;

		Point() : Point(-1, -1){};

		Point(int row, int column)
		{
			this->row = row;
			this->column = column;
		};

		bool operator==(Point other)
		{
			return this->row == other.row && this->column == other.column;
		}

		Point operator+(Point other)
		{
			return Point(this->row + other.row, this->column + other.column);
		}

		bool isInRange(int rows, int columns) const
		{
			return this->row >= 0 and this->row < rows and this->column >= 0 and
				   this->column < columns;
		}
	};

	struct Connection
	{
		Point pointOne;
		Point pointTwo;

		Connection() : Connection(Point(-1, -1), Point(-1, -1)){};

		Connection(Point pointOne, Point pointTwo)
		{
			this->pointOne = pointOne;
			this->pointTwo = pointTwo;
		};
	};

	std::unordered_map<char, Connection> pipeConnections = {
		{'|', Connection(Point(-1, 0), Point(1, 0))},
		{'-', Connection(Point(0, -1), Point(0, 1))},
		{'L', Connection(Point(-1, 0), Point(0, 1))},
		{'J', Connection(Point(-1, 0), Point(0, -1))},
		{'7', Connection(Point(0, -1), Point(1, 0))},
		{'F', Connection(Point(0, 1), Point(1, 0))},
	};
	std::vector<Point> neighbourConnections = {Point(-1, 0), Point(0, 1),
											   Point(1, 0), Point(0, -1)};

	static Point findFirstConnection(std::vector<std::string> &pipes,
									 Point startPoint, int rows, int columns)
	{
		for (Point neighbourConnection : neighbourConnections)
		{
			Point connectionPoint = startPoint + neighbourConnection;
			if (!connectionPoint.isInRange(rows, columns))
			{
				continue;
			}

			char pipe = pipes.at(connectionPoint.row).at(connectionPoint.column);
			Connection connection = pipeConnections[pipe];
			if (connectionPoint + connection.pointOne == startPoint or
				connectionPoint + connection.pointTwo == startPoint)
			{
				return connectionPoint;
			}
		}
		throw std::invalid_argument("There is no valid first connection!");
	}

	static int findDistance(std::vector<std::string> &pipes, Point currentPoint,
							Point previousPoint, int currentDistance, int rows,
							int columns)
	{
		while (true)
		{
			char pipe = pipes.at(currentPoint.row).at(currentPoint.column);
			if (pipes[currentPoint.row][currentPoint.column] == 'S')
			{
				return currentDistance;
			}
			Connection connection = pipeConnections[pipe];
			if (currentPoint + connection.pointOne == previousPoint)
			{
				previousPoint = currentPoint;
				currentPoint = currentPoint + connection.pointTwo;
			}
			else
			{
				previousPoint = currentPoint;
				currentPoint = currentPoint + connection.pointOne;
			}
			currentDistance++;
		}
	}

	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto pipes = Utilities::file_into_string_vector(inputFile);
		int result = 0;
		int rows = (int)pipes.size() - 1;
		int columns = (int)pipes.at(0).length() - 1;

		Point startPoint;
		for (int row = 0; row < rows; row++)
		{
			for (int column = 0; column < columns; column++)
			{
				if (pipes.at(row).at(column) == 'S')
				{
					startPoint.row = row;
					startPoint.column = column;
				}
			}
		}

		Point firstConnection = findFirstConnection(pipes, startPoint, rows, columns);
		result = findDistance(pipes, firstConnection, startPoint, 1, rows, columns);
		std::cout << GREEN_TEXT
				  << "\t\t"
				  << result * 0.5
				  << RESET_COLOR
				  << std::endl;
	}
} // namespace Solutions10A
