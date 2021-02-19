#include<vector>
#include<string>
#include<iostream>
#include <algorithm>
#include <numeric>
#include <set>

#include "FileManager.hpp"

void processFile(const std::string& fileName) {
	auto input = FileManager::readInput("./inputs/" + fileName + ".in");
    FileManager::OutputFile out;

    // solve

	// sort pizzas by num ingredients
	std::sort(input.pizzas.begin(), input.pizzas.end(), [](Pizza pA, Pizza pB){
		return pA.ingredients.size() > pB.ingredients.size();
	});

	std::vector<bool> usedPizzas = std::vector<bool>(input.pizzas.size(), false);
	int pizzasLeft = usedPizzas.size();

	// for every team size
	std::vector<int> teamSizes = {2, 3, 4};
	for (auto tSize: teamSizes) {

		std::cout << "Team Size: " << tSize << std::endl;

		// for every team of that size
		for (int unused = 0; unused < input.teams[tSize - 2]; unused++) {

			// if there are enough pizzas
			if (pizzasLeft < tSize)
				break;

			Delivery d;
			d.teamSize = tSize;

			// cumulate delivery ingredients here
			std::set<std::string> teamIngredients;

			while(d.pizzas.size() < d.teamSize) {

				// searh for the best pizza
				int bestPizzaIdx = -1;
				int bestPizzaScore = -1;

				// find good pizzas to use
				for (int pizzaIdx = 0; pizzaIdx < usedPizzas.size(); pizzaIdx++) {
					if (usedPizzas[pizzaIdx])
						continue;

					// compute pizza score by counting unique ingredients
					std::set<std::string> possibleIngredients(teamIngredients);
					for (auto ingr: input.pizzas[pizzaIdx].ingredients) {
						possibleIngredients.insert(ingr);
					}

					int pizzaScore = possibleIngredients.size();

					//std::cout << pizzaScore << pizzaIdx << bestPizzaScore << std::endl;

					if ( pizzaScore > teamIngredients.size()) {
						bestPizzaIdx = pizzaIdx;
						bestPizzaScore = pizzaScore;
						break;
					}
				}

				if (bestPizzaIdx == -1) {
					// could not find suboptimal, add any
					std::cout << "No pizza found" << std::endl;
					for (int pizzaIdx = 0; pizzaIdx < usedPizzas.size(); pizzaIdx++) {
						if (usedPizzas[pizzaIdx])
							continue;

						bestPizzaIdx = pizzaIdx;
						break;
					}
				}

				usedPizzas[bestPizzaIdx] = true;
				d.pizzas.push_back(input.pizzas[bestPizzaIdx].id);
				pizzasLeft--;
				for (auto ingr: input.pizzas[bestPizzaIdx].ingredients)
					teamIngredients.insert(ingr);

				// std::cout << "Added " << bestPizzaIdx << std::endl;
				// std::cout << "Delivery with pizzas " << d.pizzas.size() << ", team: " << d.teamSize << std::endl;
			}

			out.deliveries.push_back(d);

			if (out.deliveries.size() % 20 == 0)
				std::cout << ".";
		}
		std::cout << std::endl;
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
