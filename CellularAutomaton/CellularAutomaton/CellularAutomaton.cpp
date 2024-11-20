#include "CellularAutomaton.h"
#include "UserInteraction.h"
#include <iostream>
#include <chrono>
#include <thread>

CellularAutomaton::CellularAutomaton(int width, int height, std::string rule, std::string boundaryCondition, bool randomInit)
	: width(width), height(width), rule(rule), boundaryCondition(boundaryCondition) {

	field.resize(width, std::vector<int>(height, 0));
	nextField.resize(width, std::vector<int>(height, 0));

	if (randomInit) {
		generateInitialState();
	}
	else {
		setInitialState();
	}
}

void CellularAutomaton::generateInitialState() {
	rng.seed(time(0));
	std::uniform_int_distribution<int> dist(0, 1);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			field[x][y] = dist(rng);
		}
	}
}

void CellularAutomaton::setInitialState() {
	std::cout << "Enter the initial state of the field (" << width << " x " << height << ").\n";
	std::cout << "Enter 0 for dead cell and 1 for alive.\n";

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int cellValue;
			while(true) {
				std::cin >> cellValue;

				if (cellValue == 0 || cellValue == 1) {
					field[x][y] = cellValue;
					break;
				}
				else {
					std::cout << "Input error. Please, enter 0 or 1.\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}

}



void CellularAutomaton::evolve() {
	// Проходим по каждой клетке
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			// Подсчитываем количество живых соседей для клетки (x, y)
			int aliveNeighbors = countAliveNeighbors(x, y);

			// Текущий статус клетки
			int currentState = field[x][y];

			// Вычисляем индекс в правиле для данной клетки и соседей
			int ruleIndex = (currentState << 4) | aliveNeighbors;
			int newState = (rule[ruleIndex] == '1') ? 1 : 0;

			// Обновляем nextField для данной клетки
			nextField[x][y] = newState;
		}
	}

	// Копируем nextField в field для следующего поколения
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			field[x][y] = nextField[x][y];
		}
	}
}

void CellularAutomaton::display() const{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	for (int x = 0; x < width; x++) {
		std::string row = "";
		for (int y = 0; y < height; y++) {
			// Используем символы для живой и мёртвой клетки
			row.append(field[x][y] == 1 ? "▮" : "▯");
		}
		std::cout << row + "\n";
	}

	// Добавляем задержку, чтобы наблюдать изменения
	sleep_for(milliseconds(500));
}




unsigned int CellularAutomaton::countAliveNeighbors(int x, int y) const {
	unsigned int s1 = getCell(x, y - 1);
	unsigned int s2 = getCell(x, y + 1);
	unsigned int s3 = getCell(x - 1, y);
	unsigned int s4 = getCell(x + 1, y);

	return (s1 << 3) + (s2 << 2) + (s3 << 1) + s4;
}


int CellularAutomaton::getCell(int x, int y) const {
	if (boundaryCondition == "toroidal") {
		x = (x + width) % width;
		y = (y + height) % height;
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return field[y][x];
		}
		else {
			return field[x][y];
		}
	}
	else if (boundaryCondition == "zero") {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return 0;
		}
		return field[x][y];
	}
	else if (boundaryCondition == "one") {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return 1;
		}
		return field[x][y];
	}
	return 0;
}