class Time
{
private:
	int hours, minutes;

public:
	Time() {
		hours = 0;
		minutes = 0;
	}

	int getHours() const {
		return hours;
	}
	
	int getMinutes() const {
		return minutes;
	}

	void setHours(const int& h) {
		hours = h;
	}

	void setMinutes(const int& m) {
		minutes = m;
	}
	
	Time getDeltaTime(const Time& to) {
		int to_hours = to.hours;
		if (this->hours > to.hours) {
			to_hours += 24;
		}

		Time difference;
		difference.hours = to_hours - (this->hours) - 1;
		difference.minutes = to.minutes + (60 - (this->minutes));
		if (difference.minutes >= 60) {
			difference.hours++;
			difference.minutes = difference.minutes - 60;
		}

		return difference;
	}

	bool operator>=(const Time& other) {
		if (this->hours < other.hours) {
			return false;
		}
		else if (this->hours > other.hours) {
			return true;
		}
		else if(this->hours == other.hours) {
			return this->minutes > other.minutes ? true : false;
		}
		else {
			return true;
		}
	}

	bool operator<=(const Time& other) {
		if (this->hours < other.hours) {
			return true;
		}
		else if (this->hours > other.hours) {
			return false;
		}
		else if (this->hours == other.hours) {
			return this->minutes > other.minutes ? false : true;
		}
		else {
			return true;
		}
	}
	
	std::string toString() {
		return std::to_string(getHours()) + ":" + std::to_string(getMinutes());
	}
};