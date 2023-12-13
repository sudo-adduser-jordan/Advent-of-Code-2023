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
		// line # 9, 15, 17
		// namespace Puzzle
		//		std::cout << "Puzzle not yet solved!";
		// } // namespace Puzzle

		std::string line9 = "namespace Puzzle";
		std::string line15a = R"(		std::cout << "\t\tPuzzle)";
		std::string line15b = R"( not yet solved !";)";
		std::string line17 = "} // namespace Puzzle";

		std::ifstream input_file("PuzzleTemplate.txt");
		std::vector<std::string> lines;
		std::string input;

		while (std::getline(input_file, input))
		{
			lines.push_back(input);
		}
		input_file.close();

		for (auto i = 6; i <= 25; i++)
		{
			for (auto j = 0; j < 2; ++j)
			{
				char part = (j == 0 ? 'A' : 'B');
				std::string day = (i < 10 ? '0' + std::to_string(i) : std::to_string(i));
				std::string output_file = "Puzzle" + day + part + ".cpp";

				std::string line9New = line9;
				std::string line22New = line15a;
				std::string line17New = line17;

				line9New += day + part;
				line22New += day + part + line15b;
				line17New += day + part;

				lines[8] = line9New;
				lines[14] = line22New;
				lines[16] = line17New;

				Utilities::WriteAllLinesToFile(output_file, lines);
				// std::cout << "File created.\n";
			}
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
				builder << "Puzzle" << std::setfill('0') << std::setw(2) << i << "SampleA.input";
				Utilities::WriteAllLinesToFile(builder.str(), lines);
			}
		}
	}

	void GeneratePuzzleMarkDownFiles()
	{
		auto lines = std::vector<std::string>{ "" };
		for (auto i = 1; i <= 25; ++i)
		{
			for (auto j = 0; j < 2; ++j)
			{
				char part = (j == 0 ? 'A' : 'B');
				auto builder = std::stringstream{};
				builder << "Puzzle" << std::setfill('0') << std::setw(2) << i << part << ".md";
				Utilities::WriteAllLinesToFile(builder.str(), lines);
			}
		}
	}
} // namespace CodeGenerator