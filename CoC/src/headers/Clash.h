#pragma once
#include "json.hpp"

#include <filesystem>
#include <iomanip>
#include <locale>
#include <sstream>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class Clash
{
private:
	uint32_t _gold, _elixer, _darkElixer;
public:
	Clash();
	~Clash();


	void PrintResources();

	void addResources(uint32_t gold, uint32_t elixer, uint32_t darkElixer);

	void loadResources();

	void saveResources();

	bool clearResources(std::string& r);

	void checkForDir();

	void getLimit();

	bool checkLimit(uint32_t const& g, uint32_t const& e, uint32_t const& d);

private:
	// Format an integer value with commas every 3 digits
	std::string FormatWithCommas(uint32_t value);

	uint32_t* GetResources();
};

