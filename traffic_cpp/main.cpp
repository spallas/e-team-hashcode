#include<vector>
#include<string>
#include<iostream>
#include <map>
#include <cmath>
#include "FileManager.hpp"

void processFile(const std::string& fileName) {
	auto input = FileManager::readInput("./inputs/" + fileName + ".in");
    FileManager::OutputFile out;

	std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 2}, {"c", 7}, {"d", 7}, {"e", 3}, {"f", 7} };

    // solve

	for (auto inters : input.intersectionsStreet) {
		auto iId = inters.first;
		auto streets = inters.second;

		Schedule s;
		s.intersectionId = iId;
		s.streetsControlled = streets.size();

		// intersections with only one street --> always green
		if (streets.size() == 1) {
			StreetSchedule strS;
			strS.streetName = streets[0];
			strS.greenDuration = input.Duration == 1 ? 1 : 2;
			s.schedules.push_back(strS);
		} else {
			// > 1 streets
			auto lightDuration = std::vector<long>(streets.size());
			long maxLighDuration = -1;
			long sumLightDuration = 0;
			for (auto i = 0; i < streets.size(); i++) {
				lightDuration[i] = input.streetsUsed[streets[i]];
				if (lightDuration[i] > maxLighDuration) {
					maxLighDuration = lightDuration[i];
				}
				sumLightDuration += lightDuration[i];
			}

			if (maxLighDuration == 0) {
				continue;
			}

			double maxTime = (double)timePerFile[fileName];

			for (auto i = 0; i < streets.size(); i++) {
				double val = std::ceil(((double)(lightDuration[i]) / (double)(sumLightDuration) * maxTime));
				if (val < 1.0e-3 ) {
					val = 1;
				}
				lightDuration[i] = (long)val;
				StreetSchedule strS;
				strS.streetName = streets[i];
				strS.greenDuration = lightDuration[i];
				s.schedules.push_back(strS);
			}
		}

		out.schedules.push_back(s);
	}

	out.numSchedules = out.schedules.size();

	//std::cout << input.toString();

    std::cout << FileManager::writeOutput(out, "./outputs/" + fileName + ".out") << std::endl;
}


int main()
{
	std::vector<std::string> files = { "a", "b", "c", "d", "e", "f" };
	for (auto fName : files) {
		std::cout << "Begin " << fName << std::endl;
		processFile(fName);
		std::cout << "Done " << fName << std::endl;
	}
	std::cout << "TOTALLY DONE" << std::endl;
	getchar();
    return 0;
}
