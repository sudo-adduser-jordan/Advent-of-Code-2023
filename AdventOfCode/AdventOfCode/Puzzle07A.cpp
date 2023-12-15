#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

namespace Puzzle07A
{

	struct Hand
	{
		int type;
		std::vector<int> cards;
		int bid;
	};

	struct Types
	{
		const int fiveKind = 6;
		const int fourKind = 5;
		const int fullHouse = 4;
		const int threeKind = 3;
		const int twoPair = 2;
		const int onePair = 1;
		const int highCard = 0;
	};
	Types types;

	const std::map<char, int> conversionMap = {
		{ '2', 1 }, { '3', 2 }, { '4', 3 },  { '5', 4 },  { '6', 5 },  { '7', 6 },  { '8', 7 },
		{ '9', 8 }, { 'T', 9 }, { 'J', 10 }, { 'Q', 11 }, { 'K', 12 }, { 'A', 13 },
	};

	static std::vector<int> ConvertCharacters(std::string str)
	{
		std::vector<int> vector;
		for (auto& character : str)
		{
			vector.push_back(conversionMap.at(character));
		}
		return vector;
	}

	static int GetTotal(const auto& str, const char card)
	{
		int total = 0;
		for (const auto& character : str)
		{
			if (character == card)
			{
				total++;
			}
		}
		return total;
	}

	static int SetType(std::string cards)
	{
		int total = 0;
		const char card = cards[0];
		for (const auto& card : cards)
		{
			if (cards.contains(card))
			{
				total = GetTotal(cards, card);
				switch (total)
				{
					case 2:
					{
						std::string str = cards;
						str.erase(std::remove(str.begin(), str.end(), card), str.end());

						if (str[0] == str[1] and str[1] == str[2])
						{
							return types.fullHouse;
						}
						if (str[0] == str[1])
						{
							return types.twoPair;
						}
						if (str[1] == str[2])
						{
							return types.twoPair;
						}
						if (str[0] == str[2])
						{
							return types.twoPair;
						}
						return types.onePair;
					}
					case 3:
					{
						std::string str = cards;
						str.erase(std::remove(str.begin(), str.end(), card), str.end());

						if (str[0] == str[1])
						{
							return types.fullHouse;
						}
						return types.threeKind;
					}
					case 4:
						return types.fourKind;
					case 5:
						return types.fiveKind;
				}
			}
		}
		return types.highCard;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		auto input = ReadAllLinesInFile(inputFile);

		std::list<Hand> listOfHands;
		std::list<Hand> fiveKind;
		std::list<Hand> fourKind;
		std::list<Hand> fullHouse;
		std::list<Hand> threeKind;
		std::list<Hand> twoPair;
		std::list<Hand> onePair;
		std::list<Hand> highCard;

		for (const auto& line : input)
		{
			const auto vector = SplitString(line, " ");
			Hand hand;
			hand.type = SetType(vector.at(0));            // set type of hand
			hand.cards = ConvertCharacters(vector.at(0)); // set cards to int value
			hand.bid = stoi(vector.at(1));                // set bid

			if (hand.type == types.fiveKind) // switch type
			{
				fiveKind.push_back(hand); // push to sort by type
			}
			if (hand.type == types.fourKind)
			{
				fourKind.push_back(hand);
			}
			if (hand.type == types.fullHouse)
			{
				fullHouse.push_back(hand);
			}
			if (hand.type == types.threeKind)
			{
				threeKind.push_back(hand);
			}
			if (hand.type == types.twoPair)
			{
				twoPair.push_back(hand);
			}
			if (hand.type == types.onePair)
			{
				onePair.push_back(hand);
			}
			if (hand.type == types.highCard)
			{
				highCard.push_back(hand);
			}
		}

		auto cmp = [](const auto& a, const auto& b) { return a.cards < b.cards; };
		fiveKind.sort(cmp); // sort type by value
		fourKind.sort(cmp);
		fullHouse.sort(cmp);
		threeKind.sort(cmp);
		twoPair.sort(cmp);
		onePair.sort(cmp);
		highCard.sort(cmp);

		listOfHands.splice(listOfHands.end(), highCard); // concat types
		listOfHands.splice(listOfHands.end(), onePair);
		listOfHands.splice(listOfHands.end(), twoPair);
		listOfHands.splice(listOfHands.end(), threeKind);
		listOfHands.splice(listOfHands.end(), fullHouse);
		listOfHands.splice(listOfHands.end(), fourKind);
		listOfHands.splice(listOfHands.end(), fiveKind);

		int result = 0;
		int index = 1;
		for (const auto& hand : listOfHands) // sum rank times bid
		{
			result += index * hand.bid;
			index++;
		}

		std::cout << "\t\t" << GREEN_TEXT << result << RESET_COLOR;
	}
} // namespace Puzzle07A