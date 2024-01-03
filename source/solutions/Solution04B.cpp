#include "Solutions.h"
#include "../../packages/utilities/Utilities.h"

namespace Solutions04B
{
	struct Card
	{
		int cardNumber;
		std::vector<int> winningNumbers;
		std::vector<int> numbers;
		int totalMatches;
		int totalAmountOfCard;
	};
	int getTotalMatches(Card &card)
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
	void PrintSolution(const std::filesystem::path &inputFile)
	{
		auto input = Utilities::file_into_string_vector(inputFile);
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

		for (Card card : cards) // one of ea card w/ score
		{
			cards[card.cardNumber - 1].totalMatches = getTotalMatches(card);
			cards[card.cardNumber - 1].totalAmountOfCard = 1;
			result += 1;
		}

		for (Card card : cards)
		{
			while (card.totalAmountOfCard > 0)
			{
				for (int index = 0; index < card.totalMatches; index++)
				{
					cards[card.cardNumber + index].totalAmountOfCard++;
					result += 1;
				}
				card.totalAmountOfCard--;
			}
		}
		std::cout << "\t\t" << GREEN_TEXT << "\t\t" << result << std::endl;
	}
} // namespace Solutions04B
