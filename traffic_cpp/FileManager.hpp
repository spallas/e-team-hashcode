#include<vector>
#include<string>

#include <fstream>
#include <iostream>

#include <sstream>
#include <iterator>

#include <map>

std::vector<std::string> split(const std::string text) {
	std::istringstream iss(text);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	return results;
}

std::string join(const std::vector<std::string> array) {
	std::stringstream ss;
	for (auto item : array)
		ss << item << ", ";
	return ss.str();
}

int to_int(const std::string& text) {
	return std::atoi(text.c_str());
}

struct Street {
	int intersectionStart;
	int intersectionEnd;
	std::string streetName;
	int time;
};

struct Car {
	int pathLength;
	std::vector<std::string> path;
};


struct StreetSchedule {
	std::string streetName;
	int greenDuration;
};

struct Schedule {
	int intersectionId;
	int streetsControlled;
	std::vector<StreetSchedule> schedules;
};

namespace FileManager {

	struct InputFile {
        // define custom structure here
		int Duration;
		int Intersections;
		int Streets;
		int Cars;
		int points;

		std::vector<Street> streets;
		std::vector<Car> cars;

		std::map<std::string, int> streetsUsed;
		std::map<int, std::vector<std::string>> intersectionsStreet;

		std::string toString() {
			std::stringstream ss;
			ss << "Duration:" << this->Duration << std::endl;
			ss << "Intersections:" << this->Intersections << std::endl;
			ss << "Streets:" << this->Streets << std::endl;
			ss << "Cars:" << this->Cars << std::endl;
			ss << "points:" << this->points << std::endl;

			ss << "streets: " << std::endl;
			for (auto s : this->streets) {
				ss << "\t" << "intersectionStart: " << s.intersectionStart << std::endl;
				ss << "\t" << "intersectionEnd: " << s.intersectionEnd << std::endl;
				ss << "\t" << "streetName: " << s.streetName << std::endl;
				ss << "\t" << "time: " << s.time << std::endl << std::endl;
			}

			ss << "cars: " << std::endl;
			for (auto c: this->cars) {
				ss << "\t" << "pathLength: " << c.pathLength << std::endl;
				ss << "\t" << "path: " << std::endl;
				for (auto piece : c.path) {
					ss << "\t\t" << piece << std::endl;
				}
				ss << std::endl;
			}

			ss << "streetsUsed: " << std::endl;
			for (auto it = this->streetsUsed.begin(); it != this->streetsUsed.end(); it++) {
				ss << "\t" << it->first << ", " << it->second << std::endl;
			}

			ss << "intersectionStreets: " << std::endl;
			for (auto inters : this->intersectionsStreet) {
				ss << "\t" << inters.first << ", " << join(inters.second) << std::endl;
			}

			return ss.str();
		}
	};

	struct OutputFile {
		// define custom structure here
        int numSchedules;
		std::vector<Schedule> schedules;
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
		ret.Duration = to_int(fields[0]);
		ret.Intersections = to_int(fields[1]);
		ret.Streets = to_int(fields[2]);
		ret.Cars = to_int(fields[3]);
		ret.points = to_int(fields[4]);

		for (int i = 0; i < ret.Streets; i++) {
			auto fields = split(lines[i+1]);
			Street s;
			s.intersectionStart = to_int(fields[0]);
			s.intersectionEnd = to_int(fields[1]);
			s.streetName = fields[2];
			s.time = to_int(fields[3]);

			ret.streets.push_back(s);

			ret.streetsUsed[s.streetName] = 0;

			if (ret.intersectionsStreet.count(s.intersectionEnd) == 0)
				ret.intersectionsStreet[s.intersectionEnd] = std::vector<std::string>();

			ret.intersectionsStreet[s.intersectionEnd].push_back(s.streetName);
		}

		for (int i = 0; i < ret.Cars; i++) {
			auto fields = split(lines[i + 1 + ret.Streets]);
			Car c;
			c.pathLength = to_int(fields[0]);
			for (int j = 0; j < c.pathLength; j++) {
				auto streetName = fields[j+1];
				c.path.push_back(streetName);

				ret.streetsUsed[streetName]++;
			}
			ret.cars.push_back(c);
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
		outFile << out.numSchedules << std::endl;
		for (auto sched : out.schedules) {
			outFile << sched.intersectionId << std::endl;
			outFile << sched.streetsControlled << std::endl;
			for (auto streetSched: sched.schedules) {
				outFile << streetSched.streetName << " " << streetSched.greenDuration << std::endl;
			}
		}


		outFile.close();

		return true;
	}
}
