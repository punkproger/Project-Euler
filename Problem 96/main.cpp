#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdlib>
#include <exception>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <atomic>


#define LOG_INFO(x) std::cout << x << " [line " << __LINE__ << "]" << std::endl


constexpr int digitsPerRow{9};

using SuDoku = std::array<std::array<int, digitsPerRow>, digitsPerRow>; //matrix 9x9
using PossibleValues = std::vector<int>;
using PossibleValuesMatrix = std::array<std::array<PossibleValues, digitsPerRow>, digitsPerRow>;

struct Position {
	size_t x;
	size_t y;

	Position(size_t _x, size_t _y) : x(_x), y(_y) {}
};


PossibleValues getPossibleValues(const SuDoku & puzzle, size_t x, size_t y) {
	constexpr size_t digitsCount{10};
	bool appearedDigits[digitsCount] = {false};
	PossibleValues possibleValues;

	for(int i = 0; i < digitsPerRow; ++i) {
		appearedDigits[puzzle[i][y]] = true;
		appearedDigits[puzzle[x][i]] = true;
	}

	for(int i = (x/3)*3; i < (x/3 + 1)*3; ++i) {
		for(int j = (y/3)*3; j < (y/3 + 1)*3; ++j) {
			appearedDigits[puzzle[i][j]] = true;
		}
	}

	for(int i = 1; i < digitsCount; ++i) {
		if(!appearedDigits[i]) {
			possibleValues.push_back(i);
		}
	}

	return possibleValues;
}

SuDoku solveSuDoku(const SuDoku & puzzle) {
	SuDoku changedPuzzle(puzzle);

	std::function<bool(SuDoku&)> solve;
	solve = [&solve](SuDoku & puzzle) -> bool {
		std::vector<Position> zeroPositions;
		PossibleValuesMatrix possibleValues;

		for(int i = 0; i < digitsPerRow; ++i) {
			for(int j = 0; j < digitsPerRow; ++j) {
				if(puzzle[i][j] == 0) {
					zeroPositions.push_back(Position(i, j));
					possibleValues[i][j] = getPossibleValues(puzzle, i, j);
				}
			}

			for(const auto & position : zeroPositions) {
				for(auto value : possibleValues[position.x][position.y]) {
					puzzle[position.x][position.y] = value;
					if(solve(puzzle)) {
						return true;
					}
				}
				
				puzzle[position.x][position.y] = 0;
				return false;
			}
		}
		return true;
	};

	solve(changedPuzzle);

	return changedPuzzle;
}

int main() {
	srand(time(NULL));
	int solved{0};

	constexpr int puzzlesCount{50};
	std::array<SuDoku, puzzlesCount> puzzles;
	int result{0};

	std::ifstream file("p096_sudoku.txt");
	std::string line;

	std::vector<std::thread> threads;


	for(int puzzleID = 0; puzzleID < puzzlesCount; ++puzzleID) {
		std::getline(file, line); //Skip Grid Number Line

		if(isdigit(line.c_str()[0])) {
			LOG_INFO("ERROR: digit in skipped line, you are an idiot!");
		}

		for(int y = 0; y < digitsPerRow; ++y) {
			std::getline(file, line);

			for(int x = 0; x < digitsPerRow; ++x) {
				if((!isdigit(line.c_str()[x]))) {
					LOG_INFO("IDIOT");
				}

				puzzles[puzzleID][y][x] = line.c_str()[x] - '0';
			}
		}
	}

	for(const auto & puzzle : puzzles) {
		threads.push_back(std::thread([&result, &solved, puzzle](){
			auto solvedSudoku = solveSuDoku(puzzle);
			result += solvedSudoku[0][0] * 100 + solvedSudoku[0][1] * 10 + solvedSudoku[0][2];
			std::cout << "Solved: " << ++solved << std::endl;
		}));
	}

	for(auto & thread : threads) {
		thread.join();
	}

	std::cout << "Result: " << result << std::endl;

	file.close();

	return 0;
}