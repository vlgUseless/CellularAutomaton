﻿/*
    № = 11 * 11 * 2004 * 1 * 10 = 2 424 840
                                = 1001010000000000001000 - 22 символа
                           => f = (00000000001001010000000000001000) - 2^5 = 32 символа
*/

#include "CellularAutomaton.h"
#include "UserInteraction.h"
#include <iostream>

int main()
{
	while (true) {
		bool exit = 0;
		while (true) {
			std::cout << "Select option:\n";
			std::cout << "[0] Exit\n";
			std::cout << "[1] Create new cellular automaton\n";

			int choice = -1;
			if (std::cin >> choice && (choice == 0 || choice == 1)) {
				exit = 1 - choice;
				break;
			}
			else {
				std::cout << "Incorrect input. Please, enter 0 or 1.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		if (exit) break;

		int width = getInt("width");
		int height = getInt("height");
		std::string rule = "00000000001001010000000000001000";

		bool randomInit = false;
		while (true) {
			std::cout << "Do you want to:\n";
			std::cout << "[0] Manually enter initial field\n";
			std::cout << "[1] Auto - generate initial field\n";

			if (std::cin >> randomInit && (randomInit == 0 || randomInit == 1)) {
				break;
			}
			else {
				std::cout << "Incorrect input. Please, enter 0 or 1.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		std::string boundaryCondition = "zero";
		while (true) {
			
			std::cout << "Select boundary condition:\n";
			std::cout << "[0] Zero\n";
			std::cout << "[1] One\n";
			std::cout << "[2] Toroidal\n";

			int choice = -1;
			if (std::cin >> choice && (choice == 0 || choice == 1 || choice == 2)) {
				switch (choice)
				{
					case 0:
						boundaryCondition = "zero"; break;
					case 1:
						boundaryCondition = "one"; break;
					case 2:
						boundaryCondition = "toroidal"; break;
					default:
						break;
				}
				break;
			}
			else {
				std::cout << "Incorrect input. Please, enter 0, 1 or 2.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		CellularAutomaton ca(width, height, rule, boundaryCondition, randomInit);

		// Считываем количество итераций
		int iters = getInt("number of iterations");

		for (int i = 0; i < iters; i++) {
			system("cls");
			ca.display();
			std::cout << '\n';
			ca.evolve();
		}
		//system("cls");

	}
    return 0;
}