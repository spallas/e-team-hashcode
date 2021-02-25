#include<vector>
#include<string>
#include<iostream>
#include <map>
#include <cmath>
#include "FileManager.hpp"

void processFile(const std::string& fileName) {
	auto input = FileManager::readInput("./inputs/" + fileName + ".in");
    FileManager::OutputFile out;

	//std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 2.0}, {"c", 18}, {"d", 9}, {"e", 8}, {"f", 25} };
	//std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 1.7}, {"c", 15}, {"d", 8}, {"e", 7.666}, {"f", 27} };
	//std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 1.5}, {"c", 13}, {"d", 7,7}, {"e", 7}, {"f", 26} };
	//std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 1.3}, {"c", 11}, {"d", 7.78}, {"e", 7.5}, {"f", 26.6} };

	//std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 1.5}, {"c", 13}, {"d", 11}, {"e", 8}, {"f", 25} };
	std::map<std::string, float> timePerFile = { {"a", 2}, {"b", 1.5}, {"c", 13}, {"d", 11}, {"e", 8}, {"f", 25} };
	const double alpha = .3;
	const double beta = 1.0 - alpha;
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

			std::vector<double> dVec;
			std::vector<double> lVec;

			double dSum = 0;
			double lSum = 0;
			for (auto s : streets) {
				double d = input.streetsUsed[s].used;
				double l = 1.0 / (double)(input.streetsUsed[s].time);
				dSum += d;
				lSum += l;
				dVec.push_back(d);
				lVec.push_back(l);
			}

			if (dSum == 0)
				continue;

			double maxTime = (double)timePerFile[fileName];

			// ADDITIVE ALPHA BETA
			// for (int i = 0; i < streets.size(); i++) {
			// 	dVec[i] /= dSum;
			// 	lVec[i] /= lSum;
			// 	double weight = (alpha * dVec[i] + beta * lVec[i]);
			// 	double val = std::ceil(weight * maxTime);
			// 	if (val < 0.0001 ) {
			// 		val = 1;
			// 	}
			// 	StreetSchedule strS;
			// 	strS.streetName = streets[i];
			// 	strS.greenDuration = int(val);

			// 	//std::cout << " " << val << " " << maxTime << " " << strS.greenDuration << std::endl;

			// 	s.schedules.push_back(strS);
			// }

			// MULITPLICATIVE ALPHA BETA
			for (int i = 0; i < streets.size(); i++) {
				dVec[i] /= dSum;
				lVec[i] /= lSum;
				double weight = (dVec[i] * lVec[i]);
				double val = std::ceil(weight * maxTime);
				if (val < 0.0001 ) {
					val = 1;
				}
				StreetSchedule strS;
				strS.streetName = streets[i];
				strS.greenDuration = int(val);

				//std::cout << " " << val << " " << maxTime << " " << strS.greenDuration << std::endl;

				s.schedules.push_back(strS);
			}


			// ONLY ALPHA
			// auto lightDuration = std::vector<long>(streets.size());
			// long maxLighDuration = -1;
			// long sumLightDuration = 0;
			// for (auto i = 0; i < streets.size(); i++) {
			// 	lightDuration[i] = input.streetsUsed[streets[i]].used;
			// 	if (lightDuration[i] > maxLighDuration) {
			// 		maxLighDuration = lightDuration[i];
			// 	}
			// 	sumLightDuration += lightDuration[i];
			// }

			// if (maxLighDuration == 0) {
			// 	continue;
			// }

			// double maxTime = (double)timePerFile[fileName];

			// for (auto i = 0; i < streets.size(); i++) {
			// 	double val = std::ceil(((double)(lightDuration[i]) / (double)(sumLightDuration) * maxTime));
			// 	if (val < 1.0e-3 ) {
			// 		val = 1;
			// 	}
			// 	lightDuration[i] = (long)val;
			// 	StreetSchedule strS;
			// 	strS.streetName = streets[i];
			// 	strS.greenDuration = lightDuration[i];
			// 	s.schedules.push_back(strS);
			// }
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
