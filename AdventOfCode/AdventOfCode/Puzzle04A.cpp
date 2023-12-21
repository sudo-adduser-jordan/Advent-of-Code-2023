#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

struct Card
{
	int cardNumber;
	std::vector<int> winningNumbers;
	std::vector<int> numbers;
	int totalMatches;
	int totalAmountOfCard;
};

namespace Puzzle04A
{

	int getPointTotal(Card& card)
	{
		int totalMatches = 0;
		for (int winningNumber : card.winningNumbers)
		{
			for (int number : card.numbers)
			{
				if (number == winningNumber)
				{
					totalMatches++;
				}
			}
		}

		if (totalMatches == 0)
		{
			return 0;
		}

		if (totalMatches == 1)
		{
			return 1;
		}
		else
		{
			int total = 1;
			for (int i = 1; i < totalMatches; i++)
			{
				total *= 2;
			}

			return total;
		}
	}

	int getTotalMatches(Card& card)
	{
		int totalMatches = 0;
		for (int winningNumber : card.winningNumbers)
		{
			for (int number : card.numbers)
			{
				if (number == winningNumber)
				{
					totalMatches++;
				}
			}
		}
		return totalMatches;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = file_into_string_vector(inputFile);

		int result = 0;
		std::vector<Card> cards;

		for (const auto line : input)
		{
			std::string cardNumber = line.substr(line.find(' '), line.find(':') - line.find(' '));
			std::string winningNumbers = line.substr(line.find(':') + 1, line.find('|') - line.find(':') - 1);
			std::string numbers = line.substr(line.find('|') + 1);

			Card card;
			card.cardNumber = stoi(cardNumber);

			int number;
			std::stringstream streamTwo(winningNumbers);
			while (streamTwo >> number)
			{
				card.winningNumbers.push_back(number);
			}

			std::stringstream streamOne(numbers);
			while (streamOne >> number)
			{
				card.numbers.push_back(number);
			}

			cards.push_back(card);
		}

		for (Card card : cards)
		{
			result += getPointTotal(card);
		}

		std::cout << "\t\t" << GREEN_TEXT << result << RESET_COLOR;
	}
} // namespace Puzzle04A