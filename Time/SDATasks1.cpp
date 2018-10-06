#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Time.hpp"

#define CARCOUNT 3

/*
	Helper method: Reads departure and arrival time from a console line
	Return type: std::pair<Time, Time> 
*/
std::pair<Time, Time> readCarTimes() {	
	std::string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);

	std::pair<Time, Time> times;
	int i = 0, temp;
	while (iss >> temp)
	{
		switch (i) {
			case 0: times.first.hours = temp; break;
			case 1: times.first.minutes = temp; break;
			case 2: times.second.hours = temp; break;
			case 3: times.second.minutes = temp; break;
		}
		i++;
	}
	return times;
}

int main()
{
	// Read arrival/departure times for all cars from Console Input
	std::pair<Time, Time>* carTimes = new std::pair<Time, Time>[CARCOUNT];
	for (int i = 0; i < CARCOUNT; i++) {
		carTimes[i] = readCarTimes();
	}

	// Calculate Time Deltas for all cars
	Time* deltaTimes = new Time[CARCOUNT];
	for (int i = 0; i < CARCOUNT; i++) {
		Time currentDeltaTime = Time::getDeltaTime(carTimes[i].first, carTimes[i].second);
		deltaTimes[i] = currentDeltaTime;
	}
	
	// Get max and min time
	Time min = deltaTimes[0], max = deltaTimes[0];
	for (int i = 1; i < CARCOUNT; i++) {
		min = Time::lesser(min, deltaTimes[i]);
		max = Time::greater(max, deltaTimes[i]);
	}
	
	// Print Result
	std::cout << min.hours << ":" << min.minutes << std::endl;
	std::cout << max.hours << ":" << max.minutes << std::endl;
	
	delete carTimes;
	delete deltaTimes;

    return 0;
}
