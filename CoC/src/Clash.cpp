#include "headers/Clash.h"

Clash::Clash() : _gold(0), _elixer(0), _darkElixer(0) { checkForDir(); loadResources(); }; // Constructor // Check For Resources Directory And Load Resources
Clash::~Clash() {}; // Destructor // Dont Really Need This But I Like To Have It

// Return starting posution of resources array
// 0 = gold, 1 = elixer, 2 = dark elixer
// Used for looping through resources
// Could use unsigned int* but uint32_t is faster to type and I myself know that it is a 32 bit unsigned int
// This Is A Private Function And Should Not Be Called Outside Of This Class
// I Know I couldve used a array / vector but I wanted to use pointers
uint32_t* Clash::GetResources()
{
	return &_gold;
}

// Print resources from class instance to console
void Clash::PrintResources()
{
	auto resources = GetResources();
	int col_width = 15;

	std::cout.imbue(std::locale("")); // Set locale to use commas

    // Define box characters
    char horizontal = '-';
    char vertical = '|';

    // Print top border
    std::cout << "+";
    for (int i = 0; i < (col_width * 3) + 6; ++i) {
        std::cout << horizontal;
    }
    std::cout << "+" << std::endl;

    // Print header
    std::cout << vertical << "  " << std::left << std::setw(col_width) << "Gold"
        << vertical << "  " << std::setw(col_width) << "Elixir"
        << vertical << "  " << std::setw(col_width) << "Dark Elixir" << "\b\b" << vertical << std::endl;

    // Print middle border
    std::cout << "+";
    for (int i = 0; i < (col_width * 3) + 6; ++i) {
        std::cout << horizontal;
    }
    std::cout << "+" << std::endl;

    // Print resource values with commas as thousands separators
    std::cout << vertical << "  " << std::setw(col_width) << FormatWithCommas(resources[0])
        << vertical << "  " << std::setw(col_width) << FormatWithCommas(resources[1])
        << vertical << "  " << std::setw(col_width) << FormatWithCommas(resources[2]) << "\b\b" << vertical << std::endl;

    // Print bottom border
    std::cout << "+";
    for (int i = 0; i < (col_width * 3) + 6; ++i) {
        std::cout << horizontal;
    }
    std::cout << "+" << std::endl;

    std::cout << "\n" << std::flush;
}

// Add resources to current class instance then call saveResources() to save to json file
void Clash::addResources(uint32_t gold, uint32_t elixer, uint32_t darkElixer)
{
    if (checkLimit(gold, elixer, darkElixer))
        return;

	_gold += gold;
	_elixer += elixer;
	_darkElixer += darkElixer;
	saveResources();
}

// Load resources from json file and store in class instance
// This function is called in the constructor
void Clash::loadResources()
{
	try 
	{
		std::fstream file("resources/resources.json", std::ios::in);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file!" << std::endl;
			return;
		}

		json j;
		file >> j;

		_gold = j["gold"];
		_elixer = j["elixer"];
		_darkElixer = j["darkElixer"];

		file.close();
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}

// Save resources to json file
// This function is called in addResources()
void Clash::saveResources()
{
    try 
    {
        std::fstream file("resources/resources.json", std::ios::out);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file!" << std::endl;
            return;
        }

        json j = {
            {"gold", _gold},
            {"elixer", _elixer},
            {"darkElixer", _darkElixer}
        };

        file << j.dump(4);
        file.close();
    }
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
}

// Clear all resources from json file and current class instance
// TODO: Make this function more efficient 
//     (i.e. Make separate functions for each resource)
bool Clash::clearResources(std::string& r)
{

    if(r == "gold" || r ==  "Gold" || r == "g" || r == "G")
    {
        _gold = 0;
        saveResources();

        r = "Gold ";
        return true;
    }
	else if(r == "elixer" || r == "Elixer" || r == "e" || r == "E")
    {
        _elixer = 0;
        saveResources();

        r = "Elixer ";
        return true;
    }
    else if (r == "dark elixer" || r == "Dark Elixer" || r == "dark Elixer" || r == "Dark elixer" || r == "de" || r == "DE" || r == "D")
    {
        _darkElixer = 0;
        saveResources();

        r = "Dark Elixer ";
        return true;
    }
    else if(r == "")
    {
        _gold = 0;
        _elixer = 0;
        _darkElixer = 0;
        saveResources();

        r = "all Resources ";
        return true;
    }
    return false;
}

// Check if the resources directory exists, if not create it
// Also Check if the resources.json file exists, if not create it and add default values
// This function is called in the constructor
// Source: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
void Clash::checkForDir()
{
    const std::wstring dirName = L"resources";

    try
    {
        if (!std::filesystem::exists(dirName))
        {
            if (std::filesystem::create_directory(dirName))
            {
                std::cout << "Directory Created" << std::endl;
                if (!std::filesystem::exists("resources/resources.json"))
                {
              
                    std::fstream file("resources/resources.json", std::ios::out);

                    json j = {
                        {"gold", 0},
                        {"elixer", 0},
                        {"darkElixer", 0}
                    };

                    file << j.dump(4);
                    file.close();
                }
            }
            else
            {
                std::cerr << "Failed to Create Directory!" << std::endl;
            }
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

// Format an integer value with commas every 3 digits
// Example: 1000000 -> 1,000,000
// Source: https://stackoverflow.com/questions/7276826/c-format-number-with-commas
std::string Clash::FormatWithCommas(uint32_t value)
{
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << value;  // Convert value to string with commas
	return ss.str();
}

// Print the max value for uint32_t
void Clash::getLimit()
{
	std::cout << std::numeric_limits<uint32_t>::max() << std::endl;
}

// Check if the resource values are at or above the max value for uint32_t
// Source: https://stackoverflow.com/questions/199333/how-to-detect-integer-overflow
bool Clash::checkLimit(uint32_t const& g, uint32_t const& e, uint32_t const& d)
{
    if (g > std::numeric_limits<uint32_t>::max() - _gold) {
        std::cout << "Warning: Gold value is at or above max value! [VALUE] - " << _gold << " [MAX LIMIT] - " << std::numeric_limits<uint32_t>::max() << std::endl;
        _elixer += e;
        _darkElixer += d;

        std::cout << "\n";
        PrintResources();
        return true;
    }

    if (e > std::numeric_limits<uint32_t>::max() - _elixer) {
        std::cout << "Warning: Elixir value is at or above max value! [VALUE] - " << _elixer << " [MAX LIMIT] - " << std::numeric_limits<uint32_t>::max() << std::endl;
         _gold += g;
		_darkElixer += d;

        std::cout << "\n";
        PrintResources();
        return true;
    }

    if (d > std::numeric_limits<uint32_t>::max() - _darkElixer) {
        std::cout << "Warning: Dark Elixir value is at or above max value! [VALUE] - " << _darkElixer << " [MAX LIMIT] - " << std::numeric_limits<uint32_t>::max() <<  std::endl;
        _gold += g;
        _elixer += e;

        std::cout << "\n";
        PrintResources();
        return true;
    }

    return false;
}