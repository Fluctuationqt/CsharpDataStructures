#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Time.hpp"
#define CARCOUNT 3

/*
	Helper method: Reads departure and arrival time from a console line
	Return type: std::pair<Time, Time> 
**/
std::pair<Time, Time> readCarTimes() {	
	std::string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);

	std::pair<Time, Time> times;
	int wordCount = 0, temp;
	while (iss >> temp)
	{
		switch (wordCount) {
			case 0: times.first.setHours(temp); break;
			case 1: times.first.setMinutes(temp); break;
			case 2: times.second.setHours(temp); break;
			case 3: times.second.setMinutes(temp); break;
		}
		wordCount++;
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
		deltaTimes[i] = carTimes[i].first.getDeltaTime(carTimes[i].second);
	}
	
	// Get max and min time
	Time min = deltaTimes[0], max = deltaTimes[0];
	for (int i = 1; i < CARCOUNT; i++) {
		min = min <= deltaTimes[i] ? min : deltaTimes[i];
		max = max >= deltaTimes[i] ? max : deltaTimes[i];
	}
	
	// Print Result
	std::cout << min.toString() << std::endl;
	std::cout << max.toString() << std::endl;
	
	delete carTimes;
	delete deltaTimes;

    return 0;
}
