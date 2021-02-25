#include<vector>
#include<string>
#include<iostream>

#include "FileManager.hpp"

void processFile(const std::string& fileName) {
	auto input = FileManager::readInput("./inputs/" + fileName + ".in");
    FileManager::OutputFile out;

    // solve
    out.i = input.i + 1;

    std::cout << FileManager::writeOutput(out, "./outputs/" + fileName + ".out") << std::endl;
}


int main()
{
	std::vector<std::string> files = { "prova" };
	for (auto fName : files) {
		std::cout << "Begin " << fName << std::endl;
		processFile(fName);
		std::cout << "Done " << fName << std::endl;
	}
	std::cout << "TOTALLY DONE" << std::endl;
	getchar();
    return 0;
}
