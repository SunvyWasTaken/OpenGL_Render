#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

bool ReadFile(const char* pFileName, std::string& outFile)
{
	std::filesystem::path path = std::filesystem::current_path() / "Ressources\\Shader" / pFileName;

	std::ifstream inputFile(path.c_str());
	if (!inputFile.is_open())
		return false;

	std::stringstream buffer;
	buffer << inputFile.rdbuf();

	inputFile.close();
	outFile = buffer.str();
	return true;
}