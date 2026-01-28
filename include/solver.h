#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

struct Time{
	int hours;
	int minutes;
	Time() {
		hours = 0;
		minutes  = 0;
	}
	Time(const int& min) {
		hours = min/60;
		minutes = min%60;
	}
	Time(const std::string& s) {
		hours = std::stoi(s.substr(0, 2));
		minutes = std::stoi(s.substr(3, 2));
	}
	int operator-(const Time& time) {
		return this->getMinutes() - time.getMinutes();
	}
	friend std::ostream& operator<<(std::ostream& os, const Time& time) {
		if (time.hours < 10) os << "0";
		os << time.hours << ":";
		if (time.minutes < 10) os << "0";
		os << time.minutes;
		return os;
	}
	int getMinutes() const{
		return hours * 60 + minutes;
	}

};
struct Table {
	std::string name;
	bool busy = false;
	int  gain = 0;
	int busyMinutes = 0;
};
class Solver {
	int computerCount = 0;
	int cost = 0;
	Time start, finish;
	std::vector<Table> tables;
	std::unordered_map<std::string, Time> clients;
	std::map<std::string, int> clientTables;
	int busyTables = 0;
	std::queue<std::string> waitings;
public:
	Solver(const std::string& fileName) {
		getData(fileName);
	}
	bool getData(const std::string& fileName) {
		std::ifstream file(fileName);
		if (file.is_open()) {
			
			file >> computerCount;
			if (computerCount <= 0) {
				std::cout << computerCount << "\n";
				return 0;
			}
			tables = std::vector<Table>(computerCount + 1);

			std::string tmpStart, tmpFinish;
			file >> tmpStart >> tmpFinish; 
			if (!timeCheck(tmpStart) || !timeCheck(tmpFinish)) {
				std::cout << tmpStart << " " << tmpFinish << "\n";
				return 0;
			}
			start=Time(tmpStart);
			finish=Time(tmpFinish);

			file >> cost;
			if (cost <= 0) {
				std::cout << cost << "\n";
				return 0;
			}

			std::string tmpTime;
			int tmpID;
			std::string tmpName;
			int tmpTable;
			std::string line;
			std::getline(file, line);
			std::cout << start << "\n";
			while (std::getline(file, line)) {
				std::cout << line << "\n";
				std::istringstream tmp(line);
				tmp >> tmpTime;
				tmp >> tmpID;
				tmp >> tmpName;
				if (tmpID == 2) tmp >> tmpTable;
				if (!timeCheck(tmpTime) || tmpID < 1 || tmpID >4 || !nameCheck(tmpName)) return 0;
				processing(Time(tmpTime), tmpID, tmpName,tmpTable);
			}
			for (auto it = clients.begin(); it != clients.end(); it++) {
				std::string name = it->first;
				leave(finish, name);
			}
			std::cout << finish << "\n";
			for (int i = 1; i < computerCount+1; i++) std::cout << i << " " << tables[i].gain << " " << Time(tables[i].busyMinutes) << "\n";	
		}
		else return 0;
		return 1;
	}
	void processing(const Time& time, const int& id, const std::string name, const int & table) {
		switch (id) {
			case 1:
				if (!clubIsWorkingNow(time)) error(time,"NotOpenYet");
				else {
					if (clients.find(name) == clients.end()) {
						clients.insert({ name, time });
					}
					else  error(time, "YouShallNotPass");
				}
				break;
			case 2:
				if(clients.find(name) == clients.end()) error(time, "ClientUnknown");
				else {
					if (tables[table].busy == 1)  error(time, "PlaceIsBusy");
					else {
						tables[table].busy = 1;
						tables[table].name = name;
						busyTables++;
						clients[name] = time;
						clientTables.insert({ name,table });
					}
				}
				break;
			case 3:
				if (busyTables < computerCount)  error(time, "ICanWaitNoLonger!");
				else { 
					if (waitings.size() > static_cast<size_t>(computerCount)) {
						leave(time, name);
						clients.erase(name);
					}
					else waitings.push(name);
				}
				break;
			case 4:
				if (clients.find(name) == clients.end())  error(time, "ClientUnknown");
				else {
					int tableIndex = clientTables.find(name)->second;
					if (!waitings.empty()) {
						std::string newName = waitings.front();
						std::cout << time << " " << 12 << " " << waitings.front() << " " << tableIndex << "\n";
						waitings.pop();
						tables[tableIndex].name = newName;
						clientTables.insert({ newName,tableIndex });
						clients[newName] = time;
					}
					else {
						busyTables--;

						tables[tableIndex].busy = 0;
						tables[tableIndex].name = "";
					}
					int busyMinutes = time.getMinutes() - clients.find(name)->second.getMinutes();
					int hours = ((busyMinutes + 59) / 60);
					tables[tableIndex].gain += hours * cost;
					tables[tableIndex].busyMinutes += busyMinutes;
					clientTables.erase(name);
					clients.erase(name);
				}
				break;
			

		}
	}
	bool timeCheck(const std::string& time) {
		if (time.size() == 5 && time[2]==':') {
			int hours = std::stoi(time.substr(0, 2));
			int minutes = std::stoi(time.substr(3, 2));
			if(hours>=0 && minutes >=0 && hours <24 && minutes < 60) return 1;
		}
		return 0;
	}
	bool nameCheck(const std::string& name) {
		for (int i = 0; i < static_cast<int>(name.size()); i++) {
			if ((name[i] >= 48 && name[i] <= 57) || (name[i] >= 97 && name[i] <= 122) || (name[i] == '_')) {
			}
			else return 0;
		}
		return 1;
	}
private:
	bool clubIsWorkingNow(const Time & t) {
		int minutes = t.getMinutes();
		int minutesStart = start.getMinutes();
		int minutesFinish = finish.getMinutes();
		if (minutes>=minutesStart && minutes <= minutesFinish) {
			return 1;
		}
		return 0;
	}
	void error(const Time& time, const std::string& message) {
		std::cout << time << " " << 13 << " " << message << "\n";
	}
	void leave(const Time& time, const std::string name) {
		std::cout << time << " " << 11 << " " << name << "\n";
		if (clientTables.find(name) != clientTables.end()) { //значит, он не просто присутствовал в клубе, но и занимал стол (только с таких берем выручку)
			int table = clientTables.find(name)->second;
			tables[table].busy = 0;
			tables[table].name = "";
			int busyMinutes = finish - clients.find(name)->second;
			tables[table].gain += ((busyMinutes + 59) / 60) * cost;
			tables[table].busyMinutes += busyMinutes;
		}
	}
};