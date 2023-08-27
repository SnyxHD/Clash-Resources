#include "headers/app.h"
#include "headers/Clash.h"

app::app() {}; // Constructor // Not Needed as were not using any variables in this class but good practice

app::~app() {}; // Destructor // Not needed but good practice

// Main Menu
// Stored this in a seperate class to keep the main.cpp file clean
void app::run() 
{
	Clash c;
	int choice;

	std::string gold, elixir, de, clear;

	do
	{
		std::cout << "1. Add a resource" << std::endl;
		std::cout << "2. Print all resources" << std::endl;
		std::cout << "3. Clear Resources" << std::endl;
		std::cout << "4. Exit" << std::endl;

		if (std::cin >> choice)
		{
			switch (choice)
			{
			case 1:
				std::system("cls");

				std::cout << "Enter gold amount: ";
				std::cin >> gold;
				if (gold == "limits")
				{
					c.getLimit();
					break;
				}

				gold.erase(std::remove(gold.begin(), gold.end(), ','), gold.end());

				std::cout << "Enter elixir amount: ";
				std::cin >> elixir;
				elixir.erase(std::remove(elixir.begin(), elixir.end(), ','), elixir.end());

				std::cout << "Enter dark elixir amount: ";
				std::cin >> de;
				de.erase(std::remove(de.begin(), de.end(), ','), de.end());

				// check if input is valid and not a negative number or a string
				if (gold.find_first_not_of("0123456789") != std::string::npos || elixir.find_first_not_of("0123456789") != std::string::npos || de.find_first_not_of("0123456789") != std::string::npos)
				{
					std::cout << "Invalid input\n" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				
				std::system("cls");
				c.addResources(std::stoul(gold), std::stoul(elixir), std::stoul(de));
				break;
			case 2:
				std::system("cls");
				c.PrintResources();
				break;
			case 3:
				std::system("cls");
				std::cout << "Enter What Resource You Want To Clear [Press Enter To Clear All]...\n> ";
				// Allow Enter To Be Pressed To Clear All Resources or Enter A Resource To Clear
				std::cin.ignore();
				std::getline(std::cin, clear);


				if(!c.clearResources(clear))
				{
					std::system("cls");
					std::cout << "Resource Not Found\n" << std::endl;
					break;
				}

				std::system("cls");
				std::cout << clear << "Cleared\n" << std::endl;
				break;
			default:
				std::system("cls");
				std::cin.clear();
				break;
			}
		}
		else
		{
			std::system("cls");
			std::cout << "Invalid choice" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (choice != 4);

	std::exit(0);
}