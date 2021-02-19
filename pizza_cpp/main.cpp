#include<vector>
#include<string>
#include<iostream>
#include <algorithm>
#include <numeric>

#include "FileManager.hpp"

void processFile(const std::string& fileName) {
	auto input = FileManager::readInput("./inputs/" + fileName + ".in");
    FileManager::OutputFile out;

    // solve

	// sort pizzas by num ingredients
	std::sort(input.pizzas.begin(), input.pizzas.end(), [](std::vector<std::string> ingrA, std::vector<std::string> ingrB){
		return ingrA.size() > ingrB.size();
	});

	std::vector<bool> usedPizzas = std::vector<bool>(input.pizzas.size(), false);
	int pizzasLeft = usedPizzas.size();

	std::vector<int> teamSizes = {2, 3, 4};
	for (auto tSize: teamSizes) {
		for (int unused = 0; unused < input.teams[tSize - 2]; unused++) {
			if (pizzasLeft < tSize)
				break;

			Delivery d;
			d.teamSize = tSize;

			for (int pizzaIdx = 0; pizzaIdx < usedPizzas.size(); pizzaIdx++) {
				if (usedPizzas[pizzaIdx])
					continue;

				d.pizzas.push_back(pizzaIdx);
				usedPizzas[pizzaIdx] = true;
				pizzasLeft--;
				if (d.pizzas.size() == d.teamSize)
					break;
			}

			out.deliveries.push_back(d);
		}
	}

	out.numDeliveries = out.deliveries.size();


    std::cout << FileManager::writeOutput(out, "./outputs/" + fileName + ".out") << std::endl;
}


int main()
{
	std::vector<std::string> files = { "a_example", "b_little_bit_of_everything", "c_many_ingredients", "d_many_pizzas", "e_many_teams" };
	for (auto fName : files) {
		std::cout << "Begin " << fName << std::endl;
		processFile(fName);
		std::cout << "Done " << fName << std::endl;
	}
	std::cout << "TOTALLY DONE" << std::endl;
	getchar();
    return 0;
}
