#include<vector>
#include<string>

#include <fstream>
#include <iostream>

#include <sstream>
#include <iterator>

std::vector<std::string> split(const std::string text) {
	std::istringstream iss(text);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	return results;
}

namespace FileManager {

	struct InputFile {
        // define custom structure here
        int i;
	};

	struct OutputFile {
		// define custom structure here
        int i;
	};

	InputFile readInput(std::string path)
	{
		auto ret = InputFile();

		std::ifstream file(path);
		if (!file.is_open()) {
			std::cout << "Wait what???" << std::endl;
			return ret;
		}

		std::string line;
		std::vector<std::string> lines;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}

		auto fields = split(lines[0]);

        // parse lines
        ret.i = std::atoi(fields[0].c_str());

		file.close();

		return ret;

	}


	bool writeOutput(const OutputFile & out, const std::string& path)
	{
		std::ofstream outFile(path);
		if (!outFile.is_open()) {
			return false;
		}

        // write output
        outFile << out.i << std::endl;

		outFile.close();

		return true;
	}
}
