#include "CodeGenerator.h"

#include "pch.h"

#include "../Utilities/Utilities.h"

namespace CodeGenerator
{
	void GeneratePuzzleSolversHeader()
	{
		auto lines = std::vector<std::string>{ "#pragma once" };

		for (auto i = 1; i <= 25; ++i)
		{
			for (auto j = 0; j < 2; ++j)
			{
				const auto suffix = j == 0 ? 'A' : 'B';

				lines.emplace_back("");

				auto builder = std::stringstream{};
				builder << "namespace Puzzle" << std::setfill('0') << std::setw(2) << i << suffix;
				lines.emplace_back(builder.str());
				lines.emplace_back("{");
				lines.emplace_back("\tvoid PrintSolution(const std::filesystem::path& inputFile, bool shouldRender);");
				lines.emplace_back("}");
			}
		}

		Utilities::WriteAllLinesToFile("PuzzleSolvers.h", lines);
	}

	void GeneratePuzzleSolvers()
	{

		// line # 8, 21, 23
		// namespace Puzzle
		//		std::cout << "Puzzle not yet solved!";
		// } // namespace Puzzle

		std::string line8 = "namespace Puzzle";
		std::string line22a = R"(		std::cout << "\t\tPuzzle)";
		std::string line22b = R"( not yet solved !";)";
		std::string line26 = "} // namespace Puzzle";

		std::ifstream input_file("PuzzleTemplate.txt");
		std::vector<std::string> lines;
		std::string input;

		while (std::getline(input_file, input))
			lines.push_back(input);
		input_file.close();

		for (auto i = 1; i <= 25; i++)
			for (auto j = 0; j < 2; ++j)
			{
				char part = (j == 0 ? 'A' : 'B');
				std::string day = (i < 10 ? '0' + std::to_string(i) : std::to_string(i));
				std::string output_file = "Puzzle" + day + part + ".cpp";

				std::string line8New = line8;
				std::string line22New = line22a;
				std::string line26New = line26;

				line8New += day + part;
				line22New += day + part + line22b;
				line26New += day + part;

				lines[7] = line8New;
				lines[21] = line22New;
				lines[25] = line26New;

				Utilities::WriteAllLinesToFile(output_file, lines);
				//std::cout << "File created.\n";
			}
	}

	void GeneratePuzzleInputFiles()
	{
		auto lines = std::vector<std::string>{ "" };
		for (auto i = 1; i <= 25; ++i)
		{
			{
				auto builder = std::stringstream{};
				builder << "Puzzle" << std::setfill('0') << std::setw(2) << i << ".input";
				Utilities::WriteAllLinesToFile(builder.str(), lines);
			}

			{
				auto builder = std::stringstream{};
				builder << "Puzzle" << std::setfill('0') << std::setw(2) << i << "Sample.input";
				Utilities::WriteAllLinesToFile(builder.str(), lines);
			}
		}
	}
} // namespace CodeGenerator