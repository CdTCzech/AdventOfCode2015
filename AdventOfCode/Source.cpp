#include <algorithm>
#include <iostream>
#include <iterator>
#include <locale>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "Libraries/md5.h"
#include "FileReader.h"


namespace day1
{
	void part1()
	{
		const auto& line = getLine("day1.txt");
		int result = 0;

		for (auto character : line)
		{
			if (character == '(') ++result;
			else --result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day1.txt");
		int floor = 0, result = 0;

		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == '(') ++floor;
			else --floor;

			if (floor == -1)
			{
				result = i;
				break;
			}
		}

		std::cout << result + 1 << std::endl;
	}
}

namespace day2
{
	struct Dimensions
	{
		int l;
		int w;
		int h;
	};

	void part1()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [&result](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto sideA = line.l * line.w;
			auto sideB = line.l * line.h;
			auto sideC = line.w * line.h;
			auto sideM = std::min(sideA, std::min(sideB, sideC));
			result += 2 * sideA + 2 * sideB + 2 * sideC + sideM;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		auto result = 0;

		for (const auto& line : getLineByLine<Dimensions>("day2.txt", [&result](std::string& var)
		{
			std::replace(var.begin(), var.end(), 'x', ' ');
			std::istringstream iss(var);
			int l, w, h;
			iss >> l >> w >> h;
			return Dimensions{ l, w, h };
		}))
		{
			auto ribbon = (line.l + line.w + line.h - std::max(line.l, std::max(line.w, line.h))) * 2;
			auto bow = line.l * line.w * line.h;
			result += ribbon + bow;
		}

		std::cout << result << std::endl;
	}
}

namespace day3
{
	struct Point
	{
		int x;
		int y;

		bool operator< (const Point& other) const
		{
			if (x < other.x) return true;
			if (x == other.x && y < other.y) return true;
			return false;
		}
	};

	void part1()
	{
		Point currentPosition{ 0, 0 };
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		for (auto character : line)
		{
			points.insert(currentPosition);

			if (character == '^') ++currentPosition.y;
			else if (character == 'v') --currentPosition.y;
			else if (character == '<') --currentPosition.x;
			else if (character == '>') ++currentPosition.x;
		}

		std::cout << points.size() << std::endl;
	}

	void part2()
	{
		Point currentPositionSanta{ 0, 0 };
		Point currentPositionRobo{ 0, 0 };
		Point* current;
		std::set<Point> points;

		const auto& line = getLine("day3.txt");
		bool isSantaTurn = true;
		for (auto character : line)
		{
			if (isSantaTurn) current = &currentPositionSanta;
			else current = &currentPositionRobo;

			isSantaTurn = !isSantaTurn;

			points.insert(*current);

			if (character == '^') ++current->y;
			else if (character == 'v') --current->y;
			else if (character == '<') --current->x;
			else if (character == '>') ++current->x;
		}

		std::cout << points.size() << std::endl;
	}
}

namespace day4
{
	void part1()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 0; number < 1000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 5) == "00000")
			{
				std::cout << std::to_string(number) << std::endl;
				break;
			}
		}
	}

	void part2()
	{
		const auto& line = getLine("day4.txt");
		for (unsigned int number = 282749; number < 10000000; ++number)
		{
			auto hash = md5(line + std::to_string(number));
			if (hash.substr(0, 6) == "000000")
			{
				std::cout << std::to_string(number) << std::endl;
				break;
			}
		}
	}
}

namespace day5
{
	void part1()
	{
		int result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [&result](std::string& var) { return var; }))
		{
			int vowels = 0;
			bool twice = false;
			bool banned = false;
			char previous = '\0';

			for (const auto& character : line)
			{
				if (character == 'a' || character == 'e' || character == 'i'
					|| character == 'o' || character == 'u')
					++vowels;

				if (previous == character) twice = true;

				if ((previous == 'a' && character == 'b') ||
					(previous == 'c' && character == 'd') ||
					(previous == 'p' && character == 'q') ||
					(previous == 'x' && character == 'y'))
					banned = true;

				previous = character;
			}

			if (vowels >= 3 && twice && !banned) ++result;
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		int result = 0;

		for (const auto& line : getLineByLine<std::string>("day5.txt", [&result](std::string& var) { return var; }))
		{
			bool pair = false;
			bool between = false;

			for (unsigned int i = 0; i < line.size() - 2; ++i)
			{
				if (line[i] == line[i + 2])
				{
					between = true;
					break;
				}
			}

			for (unsigned int i = 0; i < line.size() - 3; ++i)
			{
				bool end = false;

				for (auto j = i + 2; j < line.size() - 1; ++j)
				{
					if (line[i] == line[j] && line[i + 1] == line[j + 1])
					{
						pair = true;
						end = true;
						break;
					}
				}

				if (end == true) break;
			}

			if (pair && between) ++result;
		}

		std::cout << result << std::endl;
	}
}

namespace day6
{
	enum class Type
	{
		on,
		off,
		toggle
	};

	struct Command
	{
		day3::Point start;
		day3::Point end;
		Type type;
	};

	void part1()
	{
		std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [&grid](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] = !grid[y][x];
					else if (line.type == Type::off) grid[y][x] = false;
					else grid[y][x] = true;
				}
			}
		}

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				if (x == true) ++result;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
		unsigned int result = 0;

		for (const auto& line : getLineByLine<Command>("day6.txt", [&grid](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::string buffer;
			Command command;
			if (var[1] == 'o')
			{
				command.type = Type::toggle;
				iss >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			else
			{
				command.type = (var[6] == 'f') ? Type::off : Type::on;
				iss >> buffer >> buffer >> command.start.x >> command.start.y >> buffer >> command.end.x >> command.end.y;
			}
			return command;
		}))
		{
			for (auto y = line.start.y; y <= line.end.y; ++y)
			{
				for (auto x = line.start.x; x <= line.end.x; ++x)
				{
					if (line.type == Type::toggle) grid[y][x] += 2;
					else if (line.type == Type::on) grid[y][x] += 1;
					else
					{
						if (grid[y][x] > 0) grid[y][x] -= 1;
					}
				}
			}
		}

		for (const auto& y : grid)
		{
			for (const auto x : y)
			{
				result += x;
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day7
{
	std::map<std::string, std::vector<std::string>> instructions;
	std::map<std::string, unsigned short> results;

	inline bool isNumber(const std::string& toCheck)
	{
		return std::find_if(toCheck.begin(), toCheck.end(), [](char c) { return !std::isdigit(c, std::locale()); }) == toCheck.end();
	}

	unsigned short getResult(const std::string& key)
	{
		if (results.find(key) != results.end()) return results.at(key);

		if (isNumber(key)) return std::stoi(key);

		const auto& tokens = instructions.at(key);

		if (tokens.size() == 1)
		{
			results.insert({ key, getResult(tokens[0]) });
			return results.at(key);
		}
		if (tokens.size() == 2)
		{
			results.insert({ key, ~getResult(tokens[1]) });
			return results.at(key);
		}
		
		if (tokens[1][0] == 'A') results.insert({ key, getResult(tokens[0]) & getResult(tokens[2]) });
		else if (tokens[1][0] == 'O') results.insert({ key, getResult(tokens[0]) | getResult(tokens[2]) });
		else if (tokens[1][0] == 'L') results.insert({ key, getResult(tokens[0]) << getResult(tokens[2]) });
		else if (tokens[1][0] == 'R') results.insert({ key, getResult(tokens[0]) >> getResult(tokens[2]) });
		return results.at(key);
	}

	void part1()
	{
		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [] (std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}

		std::cout << getResult("a") << std::endl;

		instructions.clear();
		results.clear();
	}

	void part2()
	{
		for (const auto& line : getLineByLine<std::vector<std::string>>("day7.txt", [](std::string& var)
		{
			std::istringstream iss(var);
			return std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
		}))
		{
			instructions.insert({ line.back(),{ line.begin(), line.end() - 2 } });
		}

		auto part1Result = getResult("a");
		results.clear();

		instructions.at("b").clear();
		instructions.at("b").push_back(std::to_string(part1Result));
		std::cout << getResult("a") << std::endl;

		instructions.clear();
		results.clear();
	}
}

namespace day8
{
	void part1()
	{
		unsigned int result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [&result](std::string& var) { return var; }))
		{
			result += line.size();

			for (size_t index = 0; index < line.size(); ++index)
			{
				if (line[index] == '\\')
				{
					if (line[index + 1] == 'x') index += 3;
					else index += 1;
				}
				else if (line[index] == '\"') result += 1;

				result -= 1;
			}
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		unsigned int result = 0;

		for (const auto& line : getLineByLine<std::string>("day8.txt", [&result](std::string& var) { return var; }))
		{
			result += 2;

			for (const auto character : line)
			{
				if (character == '\\' || character == '\"') result += 1;
			}
		}

		std::cout << result << std::endl;
	}
}

namespace day10
{
	void part1()
	{
		const auto& line = getLine("day10.txt");
		std::string temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 40; ++iteration)
		{
			unsigned int count = 1;
			char last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		std::cout << result.size() << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day10.txt");
		std::string temp = line;
		std::string result;

		for (unsigned int iteration = 0; iteration < 50; ++iteration)
		{
			unsigned int count = 1;
			char last = temp[0];
			result.clear();

			for (size_t index = 1; index < temp.size(); ++index)
			{
				if (temp[index] != last)
				{
					result += std::to_string(count);
					result += last;
					count = 1;
					last = temp[index];
				}
				else ++count;
			}

			result += std::to_string(count);
			result += last;
			temp = result;
		}

		std::cout << result.size() << std::endl;
	}
}

namespace day11
{
	void increaseString(std::string& line, size_t index)
	{
		if (line[index] != 'z')
		{
			++line[index];
		}
		else
		{
			line[index] = 'a';
			increaseString(line, index - 1);
		}
	}

	void part1()
	{
		auto& line = getLine("day11.txt");

		bool increasing = false;
		bool banned = false;
		bool pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			bool first = true;
			char temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		std::cout << line << std::endl;
	}

	void part2()
	{
		std::string line = "hepxxyzz";

		bool increasing = false;
		bool banned = false;
		bool pairs = false;

		while (!increasing || !banned || !pairs)
		{
			increasing = false;
			banned = false;
			pairs = false;

			increaseString(line, line.size() - 1);

			for (size_t index = 0; index < line.size() - 2; ++index)
			{
				if (line[index] + 1 == line[index + 1] &&
					line[index] + 2 == line[index + 2])
				{
					increasing = true;
					break;
				}
			}

			if (line.find_first_of("iol") == std::string::npos) banned = true;

			bool first = true;
			char temp = ' ';

			for (size_t index = 0; index < line.size() - 1; ++index)
			{
				if (line[index] == line[index + 1])
				{
					if (first)
					{
						first = false;
						temp = line[index];
						++index;
					}
					else if (line[index] != temp)
					{
						pairs = true;
						break;
					}
				}
			}
		}

		std::cout << line << std::endl;
	}
}

namespace day12
{
	void part1()
	{
		const auto& line = getLine("day12.txt");

		int result = 0;
		std::string buffer;

		for (const auto character : line)
		{
			if (character == '-' && buffer.empty()) buffer += character;
			else if (character >= '0' && character <= '9') buffer += character;
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		std::cout << result << std::endl;
	}

	void part2()
	{
		const auto& line = getLine("day12.txt");
		std::map<size_t, size_t> toSkip;
		int result = 0;
		std::string buffer;

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (line[index + 0] == ':' && line[index + 1] == '\"' && line[index + 2] == 'r' &&
				line[index + 3] == 'e' && line[index + 4] == 'd' && line[index + 5] == '\"')
			{
				size_t start = index;
				int counter = 0;

				while (counter != -1)
				{
					--start;
					if (start == -1) return;
					if (line[start] == '{') --counter;
					else if (line[start] == '}') ++counter;
				}

				counter = 0;

				while (counter != -1)
				{
					++index;
					if (index == line.size()) return;
					if (line[index] == '{') ++counter;
					else if (line[index] == '}') --counter;
				}

				toSkip.insert({ start, index });
			}
		}

		for (size_t index = 0; index < line.size(); ++index)
		{
			if (toSkip.find(index) != toSkip.end())
			{
				if (!buffer.empty())
				{
					result += std::stoi(buffer);
					buffer.clear();
				}

				index = toSkip.at(index);
				continue;
			}

			if (line[index] == '-' && buffer.empty()) buffer += line[index];
			else if (line[index] >= '0' && line[index] <= '9') buffer += line[index];
			else if (!buffer.empty())
			{
				result += std::stoi(buffer);
				buffer.clear();
			}
			else buffer.clear();
		}

		std::cout << result << std::endl;
	}
}

namespace day14
{
	struct ReindeerStats
	{
		int speed;
		int flyTime;
		int restTime;
		bool phase;
		int secondsRemaining;
		int distance;
		int points;
	};

	void part1()
	{
		int time = 2503;
		int maximal = 0;

		for (const auto& line : getLineByLine<ReindeerStats>("day14.txt", [&time, &maximal](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return ReindeerStats{std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13])};
		}))
		{
			int distance = 0;

			int full = time / (line.flyTime + line.restTime);
			int half = time - (full * (line.flyTime + line.restTime));
			if (half >= line.flyTime) distance += line.speed * line.flyTime;
			else distance = half * line.speed;
			distance += full * line.speed * line.flyTime;

			if (distance > maximal) maximal = distance;
		}

		std::cout << maximal << std::endl;
	}

	void part2()
	{
		std::vector<ReindeerStats> reindeers;

		for (const auto& line : getLineByLine<ReindeerStats>("day14.txt", [&reindeers](std::string& var)
		{
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return ReindeerStats{ std::stoi(splitted[3]), std::stoi(splitted[6]), std::stoi(splitted[13]), true, std::stoi(splitted[6]), 0, 0 };
		}))
		{
			reindeers.push_back(line);
		}

		for (size_t iteration = 0; iteration < 2503; ++iteration)
		{
			for (auto& reindeer : reindeers)
			{
				if (reindeer.phase) reindeer.distance += reindeer.speed;
				--reindeer.secondsRemaining;
				if (reindeer.secondsRemaining == 0)
				{
					if (reindeer.phase) reindeer.secondsRemaining = reindeer.restTime;
					else reindeer.secondsRemaining = reindeer.flyTime;
					reindeer.phase = !reindeer.phase;
				}
			}

			int maximum = 0;
			for (auto& reindeer : reindeers) if (reindeer.distance > maximum) maximum = reindeer.distance;
			for (auto& reindeer : reindeers) if (reindeer.distance == maximum) ++reindeer.points;
		}

		int maximum = 0;
		for (auto& reindeer : reindeers) if (reindeer.points > maximum) maximum = reindeer.points;

		std::cout << maximum << std::endl;
	}
}

namespace day15
{
	struct Cookie
	{
		int capacity;
		int durability;
		int flavor;
		int texture;
		int calories;
	};

	void part1()
	{
		std::vector<Cookie> cookies;
		unsigned long long int result = 0;

		for (const auto& line : getLineByLine<Cookie>("day15.txt", [&cookies](std::string& var)
		{
			std::replace(var.begin(), var.end(), ',', ' ');
			std::istringstream iss(var);
			std::vector<std::string> splitted(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
			return Cookie{ std::stoi(splitted[2]), std::stoi(splitted[4]), std::stoi(splitted[6]), std::stoi(splitted[8]), std::stoi(splitted[10]) };
		}))
		{
			cookies.push_back(line);
		}

		for (int i = 1; i <= 100; ++i)
		{
			for (int j = 1; j <= 100 - i; ++j)
			{
				for (int k = 1; k <= 100 - i - j; ++k)
				{
					int l = 100 - i - j - k;

					long long int capacity = i * cookies[0].capacity + j * cookies[1].capacity + k * cookies[2].capacity + l * cookies[3].capacity;
					long long int durability = i * cookies[0].durability + j * cookies[1].durability + k * cookies[2].durability + l * cookies[3].durability;
					long long int flavor = i * cookies[0].flavor + j * cookies[1].flavor + k * cookies[2].flavor + l * cookies[3].flavor;
					long long int texture = i * cookies[0].texture + j * cookies[1].texture + k * cookies[2].texture + l * cookies[3].texture;

					if (capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0) continue;

					unsigned long long int score = capacity * durability * flavor * texture;

					if (score > result) result = score;
				}
			}
		}

		std::cout << result << std::endl;
	}
}

int main()
{
	std::cout << "Day 1 Part 1: "; day1::part1();
	std::cout << "Day 1 Part 2: "; day1::part2();
	std::cout << "Day 2 Part 1: "; day2::part1();
	std::cout << "Day 2 Part 2: "; day2::part2();
	std::cout << "Day 3 Part 1: "; day3::part1();
	std::cout << "Day 3 Part 2: "; day3::part2();
	std::cout << "Day 4 Part 1: "; day4::part1();
	std::cout << "Day 4 Part 2: "; day4::part2();
	std::cout << "Day 5 Part 1: "; day5::part1();
	std::cout << "Day 5 Part 2: "; day5::part2();
	std::cout << "Day 6 Part 1: "; day6::part1();
	std::cout << "Day 6 Part 2: "; day6::part2();
	std::cout << "Day 7 Part 1: "; day7::part1();
	std::cout << "Day 7 Part 2: "; day7::part2();
	std::cout << "Day 8 Part 1: "; day8::part1();
	std::cout << "Day 8 Part 2: "; day8::part2();
	std::cout << "Day 10 Part 1: "; day10::part1();
	std::cout << "Day 10 Part 2: "; day10::part2();
	std::cout << "Day 11 Part 1: "; day11::part1();
	std::cout << "Day 11 Part 2: "; day11::part2();
	std::cout << "Day 12 Part 1: "; day12::part1();
	std::cout << "Day 12 Part 2: "; day12::part2();
	std::cout << "Day 14 Part 1: "; day14::part1();
	std::cout << "Day 14 Part 2: "; day14::part2();
	std::cout << "Day 15 Part 1: "; day15::part1();
	system("pause");
	return 0;
}
 