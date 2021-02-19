#include<vector>
#include<string>

#include <fstream>
#include <iostream>

#include <sstream>
#include <iterator>

std::vector<std::string> split(const std::string& text) {
	std::istringstream iss(text);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	return results;
}

int to_int(const std::string& text) {
	return std::atoi(text.c_str());
}

struct Delivery {
	int teamSize;
	std::vector<int> pizzas;
};


struct Pizza {
	int id;
	std::vector<std::string> ingredients;
};

namespace FileManager {

	struct InputFile {
        // define custom structure here
		int numPizzas;
		std::vector<int> teams;
		std::vector<Pizza> pizzas;
	};

	struct OutputFile {
		// define custom structure here
        int numDeliveries;
		std::vector<Delivery> deliveries;
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
        ret.numPizzas = to_int(fields[0]);
		for (auto i = 1; i < fields.size(); i++)
			ret.teams.push_back(to_int(fields[i]));

		for (auto i = 1; i < lines.size(); i++) {
			auto fields = split(lines[i]);
			int num_ingr = to_int(fields[0]);

			Pizza p;
			p.id = i-1;
			p.ingredients = std::vector<std::string>(num_ingr);

			for (auto j = 0; j < num_ingr; j++) {
				p.ingredients.push_back(fields[j+1]);
			}
			ret.pizzas.push_back(p);
		}

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
		outFile << out.numDeliveries << std::endl;
		for (auto deliv: out.deliveries) {
			outFile << deliv.teamSize;
			for (auto idx : deliv.pizzas) {
				outFile << " " << idx;
			}
			outFile << std::endl;
		}

		outFile.close();

		return true;
	}
}
