#include "pch.h"

#include "../Utilities/Utilities.h"
#include "Colors.h"
#include "PuzzleSolvers.h"

using namespace Utilities;

using ulint = unsigned long long int;

namespace Puzzle05B
{

	class Range
	{
	public:
		ulint start;
		ulint range;

		ulint end() const
		{
			return start + range;
		}

		std::optional<Range> intersection(const Range& range) const
		{
			ulint start = std::max(this->start, range.start);
			ulint end = std::min(this->end(), range.end());
			if (start < end)
			{
				return Range{ start, end - start };
			}
			return std::nullopt;
		}
	};

	class RangeMap
	{
	public:
		ulint source;
		ulint destination;
		ulint range;

		Range getKeyRange() const
		{
			return { source, range };
		}

		ulint getVal(ulint key) const
		{
			return destination + (key - source);
		}

		std::array<Range, 3> getVal(const Range& keyRange) const
		{
			const Range currentRange = getKeyRange();
			const auto intersection = currentRange.intersection(keyRange);

			assert(intersection.has_value());
			const Range& intersectionRange = *intersection;
			std::array<Range, 3> result{};

			result[0] = { keyRange.start, intersectionRange.start - keyRange.start };
			result[1] = { getVal(intersectionRange.start), intersectionRange.range };
			result[2] = { intersectionRange.end(), keyRange.end() - intersectionRange.end() };

			return result;
		}
	};

	class FullMap
	{
	public:
		FullMap() = default;

		void addRange(ulint source, ulint dest, ulint range)
		{
			ranges.insert(ranges.begin(), { source, dest, range });
		}

		std::vector<Range> getValue(const Range& keyRange) const
		{
			std::vector<Range> result;
			std::vector<Range> remainingRanges = { keyRange };

			while (remainingRanges.size())
			{
				Range currentRange = remainingRanges.back();
				remainingRanges.pop_back();
				bool hasIntersection = false;
				for (const auto& range : ranges)
				{
					if (!range.getKeyRange().intersection(currentRange))
					{
						continue;
					}
					hasIntersection = true;
					const auto subRanges = range.getVal(currentRange);
					if (subRanges[0].range)
					{
						remainingRanges.push_back(subRanges[0]);
					}
					if (subRanges[2].range)
					{
						remainingRanges.push_back(subRanges[2]);
					}
					result.push_back(subRanges[1]);
					break;
				}
				if (!hasIntersection)
				{
					result.push_back(currentRange);
				}
			}
			return result;
		}

		void transform(std::vector<Range>& ranges) const
		{
			std::vector<Range> result;
			for (const auto& range : ranges)
			{
				std::vector<Range> mappedRange = getValue(range);
				result.insert(result.end(), mappedRange.begin(), mappedRange.end());
			}
			ranges = result;
		}

		void clear()
		{
			ranges.clear();
		}

	private:
		std::vector<RangeMap> ranges;
	};

	static std::vector<std::string> split(std::string s)
	{
		std::vector<std::string> tokens;
		std::string token;
		size_t pos = 0;
		while ((pos = s.find(" ")) != std::string::npos)
		{
			token = s.substr(0, pos);
			if (token != "")
			{
				tokens.push_back(token);
			}
			s.erase(0, pos + 1);
		}
		tokens.push_back(s);
		return tokens;
	}

	void PrintSolution(const std::filesystem::path& inputFile, bool shouldRender)
	{
		std::ifstream file(inputFile);
		std::string line;
		std::getline(file, line);
		std::vector<Range> seedRanges;
		std::vector<ulint> seeds = string_to_long_long_vector(line.substr(line.find(':') + 1));

		for (int i = 0; i < seeds.size() / 2; ++i)
		{
			ulint start = seeds[i * 2];
			ulint range = seeds[i * 2 + 1];
			seedRanges.push_back({ start, range });
		}

		std::getline(file, line);
		assert(line == "");

		FullMap fullMap;
		while (std::getline(file, line))
		{
			if (line == "")
			{
				fullMap.transform(seedRanges);
				fullMap.clear();
				continue;
			}
			if (line.contains("-to-"))
			{
				continue;
			}

			auto lineSplit = split(line);
			assert(lineSplit.size() == 3);

			ulint destination = stoul(lineSplit[0]);
			ulint source = stoul(lineSplit[1]);
			ulint range = stoul(lineSplit[2]);

			fullMap.addRange(source, destination, range);
		}
		fullMap.transform(seedRanges);

		ulint result = ranges::min(ranges::views::all(seedRanges) | std::views::transform([](auto& range) { return range.start; }));

		std::cout << "\t\t" << GREEN_TEXT << result << RESET_COLOR;
	}

} // namespace Puzzle05B