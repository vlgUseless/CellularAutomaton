#include "UserInteraction.h"
#include <iostream>

int getInt(std::string message) {
	int input = 0;
	
	while (true) {
		std::cout << "Enter the " << message << ": ";

		if (std::cin >> input && input > 0) {
			return input;
		}
		else {
			std::cout << "Incorrect input. Please, enter the positive integer number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

int getInt(std::string message,int leftBound, int rightBound) {
	int input = 0;

	while (true) {
		std::cout << "Enter the " << message << ": ";

		if (std::cin >> input && input >= leftBound && input <= rightBound) {
			return input;
		}
		else {
			std::cout << "Incorrect input. Please, enter the integer number in [" << leftBound << "; " << rightBound << "].\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}