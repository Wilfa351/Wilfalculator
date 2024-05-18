// ConsoleCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//TO DO LIST:

//	Add floating point support -- DONE
//	Add negative values support
//	Refactor to make more readable -- add constants, new functions, ect. Possibly include multiple files. 
//	Functionality of trigonometric functions
//	Add keywords like e and pi
//	Add logarithmic support
//	Store answer, so it can be used again
//	Add variable support
//	Add equation solving support
//	Add a filter so that it will throw a syntax error when on improper input
//	Add a help command, that instructs the user on how to use the program, and provides a list of supplemental commands
//	(OPTIONAL) possibly mess with the setprecision function, for better functionality with floating point numbers.
//	After that, who knows? Maybe I'll be done with it, or maybe I'll convert it to a GUI program and add graphing capabilities. Sky's the limit.

#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <math.h>

const int PARENTHESIS_ID = 0;
const int EXPONENT_ID = 2;
const int MULTIPLICATION_ID = 3;
const int DIVISION_ID = 4;
const int ADDITION_ID = 5;
const int NULL_ID = 7;

void UpdatePointers(std::vector<double*>& pointerArray, double* pointerBeingUpdated, double* newPointerAddress) {
	for (int i = 0; i < pointerArray.size(); ++i) {
		if (pointerArray.at(i) == pointerBeingUpdated) {
			pointerArray.at(i) = newPointerAddress;
		}
	}
}

void CalculateExponents(std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = 0; j < operators.size(); ++j) {
		if (operators.at(j) == EXPONENT_ID) {
			*pointerToNumbers.at(j) = pow(*pointerToNumbers.at(j), *pointerToNumbers.at(j + 1));
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID; // ensures code wont be run twice
		}
	}
}

void CalculateExponents(int openParethesisIndex, int closedParenthesisIndex, std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = openParethesisIndex; j < closedParenthesisIndex; ++j) {
		if (operators.at(j) == EXPONENT_ID) {
			*pointerToNumbers.at(j) = pow(*pointerToNumbers.at(j), *pointerToNumbers.at(j + 1));
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
	}

}

void CalculateMultiplicationAndDivision(std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = 0; j < operators.size(); ++j) {
		if (operators.at(j) == MULTIPLICATION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) * *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID; 
		}
		if (operators.at(j) == DIVISION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) / *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
	}
}

void CalculateMultiplicationAndDivision(int openParethesisIndex, int closedParenthesisIndex, std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = openParethesisIndex; j < closedParenthesisIndex; ++j) {
		if (operators.at(j) == MULTIPLICATION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) * *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
		if (operators.at(j) == DIVISION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) / *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
	}
}


void CalculateAdditionAndSubtraction(std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = 0; j < operators.size(); ++j) {
		if (operators.at(j) == ADDITION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) + *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
	}
}

void CalculateAdditionAndSubtraction(int& openParethesisIndex, int& closedParenthesisIndex, std::vector<int>& operators, std::vector<double*>& pointerToNumbers) {
	for (int j = openParethesisIndex; j < closedParenthesisIndex; ++j) {
		if (operators.at(j) == ADDITION_ID) {
			*pointerToNumbers.at(j) = *pointerToNumbers.at(j) + *pointerToNumbers.at(j + 1);
			UpdatePointers(pointerToNumbers, pointerToNumbers.at(j + 1), pointerToNumbers.at(j));
			operators.at(j) = NULL_ID;
		}
	}

}

void CalculateParenthetheticalExpressions(std::vector<int>& openParenthesisIndex, std::vector<int>& closedParenthesisIndex, std::vector<int>& operators,
										  std::vector<double*>& pointerToNumbers, std::vector<int>& parenthesisPriority, int maxParenthesisDepth) 
{
	std::cout << "Max Parenthesis Depth in Parenthesis Function: " << maxParenthesisDepth << std::endl;

	for (int k = 1; k <= maxParenthesisDepth; ++k) {
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < closedParenthesisIndex.size(); ++j) {
				if (i == EXPONENT_ID && parenthesisPriority.at(j) == k) {
					CalculateExponents(openParenthesisIndex.at(j), closedParenthesisIndex.at(j), operators, pointerToNumbers);

				}
				if ((i == MULTIPLICATION_ID || i == DIVISION_ID) && parenthesisPriority.at(j) == k) {
					CalculateMultiplicationAndDivision(openParenthesisIndex.at(j), closedParenthesisIndex.at(j), operators, pointerToNumbers);
				}
				if ((i == ADDITION_ID) && parenthesisPriority.at(j) == k) {
					CalculateAdditionAndSubtraction(openParenthesisIndex.at(j), closedParenthesisIndex.at(j), operators, pointerToNumbers);
					//
					std::cout << "CALCULATING AT" << k << std::endl;
				}
			}
		}
	}
}

void FindAndPairParentheses(std::vector<int>& closedParenthesisIndex, std::vector<int>& openParenthesisIndex, std::string userString,
	std::vector<int>& parenthesisPriority, int& maxParenthesisDepth)
{

	int openParenthesisCount = 0;
	int closedParenthesisCount = 0;
	int operatorCount = 0;

	for (int i = 0; i < userString.size(); ++i) {

		//For the record, I do NOT like this, but this was the only way I found to pair the closed parentheses with the open ones
		// while still retaining the parentheses index correct values

		// it feels like there's a better way, but for now this will suffice.



		switch (userString.at(i)) {
		case '^':
			++operatorCount;
			break;
		case '*':
			++operatorCount;
			break;
		case '/':
			++operatorCount;
			break;
		case '+':
			++operatorCount;
			break;
			//case '-':
			//	++operatorCount;
			//	break;
		}
		if (userString.at(i) == '(') {
			openParenthesisIndex.push_back(operatorCount);
			int temporaryOperatorCount = operatorCount;


			for (int j = i; j < userString.size(); ++j) {
				switch (userString.at(j)) {
				case '^':
					++temporaryOperatorCount;
					break;
				case '*':
					++temporaryOperatorCount;
					break;
				case '/':
					++temporaryOperatorCount;
					break;
				case '+':
					++temporaryOperatorCount;
					break;
					//case '-':
					//	++temporaryOperatorCount;
					//	break;
				}
				if (userString.at(j) == '(') {
					++openParenthesisCount;
				}
				if (userString.at(j) == ')') {
					++closedParenthesisCount;
				}
				if (closedParenthesisCount == openParenthesisCount) {
					closedParenthesisIndex.push_back(temporaryOperatorCount);
					parenthesisPriority.push_back(closedParenthesisCount);

					std::cout << temporaryOperatorCount << "TEMPOPERATORCOUNT" << std::endl;
					std::cout << closedParenthesisCount << "PARENTHESISCOUNT" << std::endl;
					std::cout << operatorCount << "OPERATORSCOUNT" << std::endl;

					if (maxParenthesisDepth < closedParenthesisCount) {
						maxParenthesisDepth = closedParenthesisCount;
					}

					std::cout << "Max parenthesis depth in the parenthesis pairing function: " << maxParenthesisDepth << std::endl;

					openParenthesisCount = 0;
					closedParenthesisCount = 0;
					temporaryOperatorCount = operatorCount;
					break;
				}
			}
		}
	}

	/*int tempIndex;
	tempIndex = closedParenthesisIndex.at(lastParenthesis - 1);
	closedParenthesisIndex.at(lastParenthesis - 1) = closedParenthesisIndex.at(lastParenthesis);
	closedParenthesisIndex.at(lastParenthesis) = tempIndex;*/
}

std::string returnTruncatedStringWithTerminator(std::string userString) {

	bool insertedNumbers = false;
	int minusCount = 0;



	for (int i = 0; i < userString.size(); ++i) {

		if (userString.at(i) == '-') {

			bool operatorDetected = false;
			bool digitDetected = false;



			for (int k = i; k > 0; --k) {
				switch (userString.at(k)) {
				case '^':
				case '*':
				case '/':
				case '+':
					operatorDetected = true;
				}



				if (k > 0 && std::isdigit(userString.at(k - 1))) {
					digitDetected = true;
					std::cout << "DIGIT DETECTED";
					break;
				}
			}

			// DEBUG

			/*for (int k = 0; k < userString.size(); ++k) {
				std::cout << userString.at(k);
			}*/

			std::cout << std::endl;

			std::replace(userString.begin() + i, userString.begin() + i + 1, '-', ' ');

			int charactersAdded;

			if ((operatorDetected && digitDetected) || !digitDetected) {
				userString.std::string::insert(i, "(-1*");
				charactersAdded = 4;
				i += charactersAdded;
			}
			else {
				userString.std::string::insert(i, "+(-1*");
				charactersAdded = 5;
				i += charactersAdded;
			}

			int closedParenthesisCount = 0;
			int openParenthesisCount = 0;

			for (int k = i; k < userString.size(); ++k) {

				if (userString.at(k) == '(') {
					++openParenthesisCount;
				}

				if (userString.at(k) == ')') {
					++closedParenthesisCount;
					if (openParenthesisCount == closedParenthesisCount - 1) {
						userString.std::string::insert(k, ")");
						++k;

						closedParenthesisCount = 0;
						openParenthesisCount = 0;

						break;
					}
				}


				// -2 + -2
				// (-1 * 2) + (-1 * 2)

				bool parenthesesInserted = false;

				if (openParenthesisCount == closedParenthesisCount) {
					switch (userString.at(k)) {
					case '^':
					case '*':
					case '/':
					case '+':
						userString.std::string::insert(k, ")");
						++k;

						parenthesesInserted = true;

						closedParenthesisCount = 0;
						openParenthesisCount = 0;

						break;
					}

					if (parenthesesInserted) {
						break;
					}
				}

				std::cout << openParenthesisCount << std::endl;
				std::cout << closedParenthesisCount << std::endl;

				if (k == userString.size() - 1 && openParenthesisCount != closedParenthesisCount && closedParenthesisCount > 0) {
					userString.push_back(')');
					++k;

					closedParenthesisCount = 0;
					openParenthesisCount = 0;

					break;
				}

				

			}

			for (int k = 0; k < userString.size(); ++k) {
				std::cout << userString.at(k);
			}

			std::cout << std::endl;

		}
	}
	
	int whiteSpaceCount = 0;

	for (int k = 0; k < userString.size(); ++k) {
		if (userString.at(k) == ' ') {
			++whiteSpaceCount;
		}
	}

	std::remove(userString.begin(), userString.end(), ' ');
	userString.std::string::resize(userString.size() - whiteSpaceCount);


	std::cout << std::endl;

	std::cout << std::endl;

	return userString + " ";
}

double parseString(std::string userString) {
	std::vector<double> numbers;
	std::vector<int> operators;

	std::vector<int> openParenthesisIndex;
	std::vector<int> closedParenthesisIndex;

	double results = 0.0;
	std::string temporaryNumbers = "";

	for (int i = 0; i < userString.size(); ++i) {
		if (std::isdigit(userString.at(i)) || userString.at(i) == '.' || userString.at(i) == '-') {
			temporaryNumbers.push_back(userString.at(i));
			continue;
		}
		else if (temporaryNumbers != "") {
			numbers.push_back(std::stod(temporaryNumbers));
			temporaryNumbers.clear();
		}
	}

	for (int i = 0; i < userString.size(); ++i) {
		switch (userString.at(i)) {
		case '^':
			operators.push_back(EXPONENT_ID);
			break;
		case '*':
			operators.push_back(MULTIPLICATION_ID);
			break;
		case '/':
			operators.push_back(DIVISION_ID);
			break;
		case '+':
			operators.push_back(ADDITION_ID);
			break;
		}
	}

	std::vector<int> parenthesisPriority;
	int maxParenthesisDepth = 0;

	FindAndPairParentheses(closedParenthesisIndex, openParenthesisIndex, userString, parenthesisPriority, maxParenthesisDepth);

	std::vector<double*> pointerToNumbers;

	for (int i = 0; i < numbers.size(); ++i) {
		pointerToNumbers.push_back(&numbers.at(i));
	}

	for (int i = 0; i < 7; ++i) {
		if (i == PARENTHESIS_ID) {
			CalculateParenthetheticalExpressions(openParenthesisIndex, closedParenthesisIndex, operators, pointerToNumbers, parenthesisPriority, maxParenthesisDepth);
			//
			std::cout << "CALCULATING PARENTHESIS" << std::endl;
		}
		if (i == EXPONENT_ID) {
			CalculateExponents(operators, pointerToNumbers);
		}
		if (i == MULTIPLICATION_ID || i == DIVISION_ID) {
			CalculateMultiplicationAndDivision(operators, pointerToNumbers);
		}
		if (i == ADDITION_ID) {
			CalculateAdditionAndSubtraction(operators, pointerToNumbers);
		}
	}

	results = numbers.at(0);

	return results;
}


int main() {

	

	std::cout << "INPUT NUMBERS" << std::endl << std::endl;

	std::string userInput = "";
	//std::getline(std::cin, userInput);

	while (std::getline(std::cin, userInput)) {

		std::cout << "CALCULATING" << std::endl << std::endl;

		std::string truncatedString = returnTruncatedStringWithTerminator(userInput);

		std::cout << std::endl << parseString(truncatedString);

		std::cout << std::endl << std::endl << "INPUT NUMBERS" << std::endl << std::endl;
	}

	std::cout << "DONE";

	return 0;
}

