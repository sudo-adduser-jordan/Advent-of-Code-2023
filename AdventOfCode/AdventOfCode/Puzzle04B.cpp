#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle04B
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
		std::cout << "\t\tPuzzle04B not yet solved !";
		SetConsoleTextColor(ConsoleForegroundColor::IntenseWhite);

	}
} // namespace Puzzle04B