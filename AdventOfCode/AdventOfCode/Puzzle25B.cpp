#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle25B
{
	auto ReadInput(const std::filesystem::path& inputFile)
	{
		auto input = ReadAllLinesInFile(inputFile);

		return input;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadInput(inputFile);

		SetConsoleTextColor(ConsoleForegroundColor::IntenseYellow);
		std::cout << "\t\tPuzzle25B not yet solved !";
		SetConsoleTextColor(ConsoleForegroundColor::IntenseWhite);

	}
} // namespace Puzzle25B